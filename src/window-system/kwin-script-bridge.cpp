/**
 * Copyright 2026 The Touchégg contributors
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 3 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 */
#include "window-system/kwin-script-bridge.h"

#include <unistd.h>

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "utils/logger.h"

namespace {
constexpr auto KWIN_SERVICE = "org.kde.KWin";
constexpr auto KWIN_SCRIPTING_PATH = "/Scripting";
constexpr auto KWIN_SCRIPTING_INTERFACE = "org.kde.kwin.Scripting";
constexpr auto KWIN_SCRIPT_INTERFACE = "org.kde.kwin.Script";

constexpr auto BRIDGE_PATH = "/io/github/joseexposito/Touchegg/KWinBridge";
constexpr auto BRIDGE_INTERFACE = "io.github.joseexposito.Touchegg.KWinBridge";
constexpr auto BRIDGE_INTROSPECTION_XML =
    "<node>"
    "  <interface name='io.github.joseexposito.Touchegg.KWinBridge'>"
    "    <method name='Reply'>"
    "      <arg name='request_id' type='s' direction='in' />"
    "      <arg name='result' type='s' direction='in' />"
    "    </method>"
    "  </interface>"
    "</node>";

constexpr int DBUS_TIMEOUT_MS = 1000;
constexpr int SCRIPT_TIMEOUT_MS = 1000;

// Serializes a flat JavaScript object as a GVariant text dictionary (a{sv}).
// JSON string escaping is compatible with the GVariant text format.
constexpr auto SCRIPT_PRELUDE = R"JS(
function touchegg_toGVariant(obj) {
  const entries = [];
  for (const key of Object.keys(obj || {})) {
    const value = obj[key];
    let serialized;
    if (typeof value === "boolean") {
      serialized = value ? "true" : "false";
    } else if (typeof value === "number") {
      serialized = "double " + (Number.isFinite(value) ? value : 0);
    } else if (value === null || value === undefined) {
      continue;
    } else {
      serialized = JSON.stringify(String(value));
    }
    entries.push(JSON.stringify(key) + ": <" + serialized + ">");
  }
  return "{" + entries.join(", ") + "}";
}

function findWindow(internalId) {
  const windows = workspace.windowList();
  for (let i = 0; i < windows.length; i++) {
    if (windows[i].internalId.toString() === internalId) {
      return windows[i];
    }
  }
  return null;
}
)JS";
}  // namespace

static const GDBusInterfaceVTable BRIDGE_VTABLE = {
    KWinScriptBridge::onMethodCall, nullptr, nullptr, {nullptr}};

bool KWinScriptBridge::isKWinRunning() {
  GError *error = nullptr;
  GDBusConnection *bus = g_bus_get_sync(G_BUS_TYPE_SESSION, nullptr, &error);
  if (bus == nullptr) {
    g_clear_error(&error);
    return false;
  }

  GVariant *reply = g_dbus_connection_call_sync(
      bus, "org.freedesktop.DBus", "/org/freedesktop/DBus",
      "org.freedesktop.DBus", "NameHasOwner",
      g_variant_new("(s)", KWIN_SERVICE), G_VARIANT_TYPE("(b)"),
      G_DBUS_CALL_FLAGS_NONE, DBUS_TIMEOUT_MS, nullptr, &error);

  bool running = false;
  if (reply != nullptr) {
    g_variant_get(reply, "(b)", &running);
    g_variant_unref(reply);
  }
  g_clear_error(&error);
  g_object_unref(bus);
  return running;
}

KWinScriptBridge::KWinScriptBridge() {
  GError *error = nullptr;
  this->connection = g_bus_get_sync(G_BUS_TYPE_SESSION, nullptr, &error);
  if (this->connection == nullptr) {
    std::string message = "Error connecting to the D-Bus session bus: ";
    message += (error != nullptr) ? error->message : "unknown error";
    g_clear_error(&error);
    throw std::runtime_error(message);
  }

  // Method calls to registered objects are dispatched in the thread-default
  // main context active when the object is registered. Use a private context
  // so we can wait for KWin's reply without dispatching unrelated events from
  // the default main loop
  this->context = g_main_context_new();
  g_main_context_push_thread_default(this->context);
  GDBusNodeInfo *nodeInfo =
      g_dbus_node_info_new_for_xml(BRIDGE_INTROSPECTION_XML, nullptr);
  this->registrationId = g_dbus_connection_register_object(
      this->connection, BRIDGE_PATH, nodeInfo->interfaces[0], &BRIDGE_VTABLE,
      this, nullptr, &error);
  g_dbus_node_info_unref(nodeInfo);
  g_main_context_pop_thread_default(this->context);

  if (this->registrationId == 0) {
    std::string message = "Error registering the KWin bridge: ";
    message += (error != nullptr) ? error->message : "unknown error";
    g_clear_error(&error);
    g_object_unref(this->connection);
    g_main_context_unref(this->context);
    throw std::runtime_error(message);
  }

  const gchar *runtimeDir = g_get_user_runtime_dir();
  std::string pid = std::to_string(getpid());
  this->scriptPath =
      std::string(runtimeDir) + "/touchegg-kwin-bridge-" + pid + ".js";
  this->pluginName = "touchegg-kwin-bridge-" + pid;

  // A script with our name might be loaded if a previous instance with the
  // same PID crashed
  this->unloadScript(true);
}

KWinScriptBridge::~KWinScriptBridge() {
  if (this->connection != nullptr) {
    this->unloadScript(true);
    if (this->registrationId != 0) {
      g_dbus_connection_unregister_object(this->connection,
                                          this->registrationId);
    }
    // Shared connection, do not close it
    g_object_unref(this->connection);
  }

  if (this->pendingResult != nullptr) {
    g_variant_unref(this->pendingResult);
  }

  if (this->context != nullptr) {
    g_main_context_unref(this->context);
  }

  if (!this->scriptPath.empty()) {
    unlink(this->scriptPath.c_str());
  }
}

GVariant *KWinScriptBridge::run(const std::string &body) const {
  uint64_t requestId = this->nextRequestId++;

  {
    std::ofstream file(this->scriptPath, std::ios::trunc);
    file << this->buildScript(body, requestId);
    if (!file) {
      tlg::error << "Error writing KWin script to " << this->scriptPath
                 << std::endl;
      return nullptr;
    }
  }

  this->pendingRequestId = requestId;
  this->pendingReplied = false;
  if (this->pendingResult != nullptr) {
    g_variant_unref(this->pendingResult);
    this->pendingResult = nullptr;
  }

  GVariant *reply = nullptr;
  bool loaded = this->callKWin(
      KWIN_SCRIPTING_PATH, KWIN_SCRIPTING_INTERFACE, "loadScript",
      g_variant_new("(ss)", this->scriptPath.c_str(), this->pluginName.c_str()),
      G_VARIANT_TYPE("(i)"), &reply);
  if (!loaded) {
    return nullptr;
  }

  gint32 scriptId = -1;
  g_variant_get(reply, "(i)", &scriptId);
  g_variant_unref(reply);

  if (scriptId < 0) {
    tlg::error << "KWin refused to load the Touchégg script" << std::endl;
    this->unloadScript(true);
    return nullptr;
  }

  std::string scriptObjectPath = "/Scripting/Script" + std::to_string(scriptId);
  bool started = this->callKWin(scriptObjectPath.c_str(), KWIN_SCRIPT_INTERFACE,
                                "run", nullptr, nullptr, nullptr);

  if (started) {
    // Wait for the script to call us back
    bool timedOut = false;
    GSource *timeout = g_timeout_source_new(SCRIPT_TIMEOUT_MS);
    g_source_set_callback(
        timeout,
        [](gpointer data) -> gboolean {
          *static_cast<bool *>(data) = true;
          return G_SOURCE_REMOVE;
        },
        &timedOut, nullptr);
    g_source_attach(timeout, this->context);

    while (!this->pendingReplied && !timedOut) {
      g_main_context_iteration(this->context, TRUE);
    }

    g_source_destroy(timeout);
    g_source_unref(timeout);

    if (!this->pendingReplied) {
      tlg::error << "Timeout waiting for KWin to run the Touchégg script"
                 << std::endl;
    }
  }

  // D-Bus messages are delivered in order, so there is no need to wait for
  // the script to be unloaded before loading the next one
  this->unloadScript(false);

  // KWin reads the file asynchronously, after "run" returns. Once the script
  // replied (or timed out) the file is no longer needed
  unlink(this->scriptPath.c_str());

  GVariant *result = this->pendingResult;
  this->pendingResult = nullptr;
  this->pendingRequestId = 0;

  if (result != nullptr) {
    std::string error = kwin_result::getString(result, "error");
    if (!error.empty()) {
      tlg::error << "Error running the Touchégg script in KWin: " << error
                 << std::endl;
      g_variant_unref(result);
      return nullptr;
    }
  }

  return result;
}

std::string KWinScriptBridge::buildScript(const std::string &body,
                                          uint64_t requestId) const {
  std::string script = SCRIPT_PRELUDE;
  script += "(function () {\n";
  script += "  let touchegg_result = {};\n";
  script += "  try {\n";
  script += "    touchegg_result = (function () {\n";
  script += body;
  script += "\n    })() || {};\n";
  script += "  } catch (e) {\n";
  script += "    touchegg_result = { error: String(e) };\n";
  script += "  }\n";
  script += "  callDBus(\"";
  script += g_dbus_connection_get_unique_name(this->connection);
  script += "\", \"";
  script += BRIDGE_PATH;
  script += "\", \"";
  script += BRIDGE_INTERFACE;
  script += "\", \"Reply\", \"";
  script += std::to_string(requestId);
  script += "\", touchegg_toGVariant(touchegg_result));\n";
  script += "})();\n";
  return script;
}

bool KWinScriptBridge::callKWin(const char *objectPath,
                                const char *interfaceName, const char *method,
                                GVariant *parameters,
                                const GVariantType *replyType,
                                GVariant **reply) const {
  GError *error = nullptr;
  GVariant *result = g_dbus_connection_call_sync(
      this->connection, KWIN_SERVICE, objectPath, interfaceName, method,
      parameters, replyType, G_DBUS_CALL_FLAGS_NONE, DBUS_TIMEOUT_MS, nullptr,
      &error);

  if (result == nullptr) {
    tlg::error << "Error calling KWin " << interfaceName << "." << method
               << ": " << ((error != nullptr) ? error->message : "unknown")
               << std::endl;
    g_clear_error(&error);
    return false;
  }

  if (reply != nullptr) {
    *reply = result;
  } else {
    g_variant_unref(result);
  }
  return true;
}

void KWinScriptBridge::unloadScript(bool wait) const {
  GVariant *parameters = g_variant_new("(s)", this->pluginName.c_str());

  if (wait) {
    GVariant *result = g_dbus_connection_call_sync(
        this->connection, KWIN_SERVICE, KWIN_SCRIPTING_PATH,
        KWIN_SCRIPTING_INTERFACE, "unloadScript", parameters, nullptr,
        G_DBUS_CALL_FLAGS_NONE, DBUS_TIMEOUT_MS, nullptr, nullptr);
    if (result != nullptr) {
      g_variant_unref(result);
    }
  } else {
    g_dbus_connection_call(this->connection, KWIN_SERVICE, KWIN_SCRIPTING_PATH,
                           KWIN_SCRIPTING_INTERFACE, "unloadScript", parameters,
                           nullptr, G_DBUS_CALL_FLAGS_NONE, DBUS_TIMEOUT_MS,
                           nullptr, nullptr, nullptr);
  }
}

void KWinScriptBridge::onMethodCall(
    GDBusConnection * /*connection*/, const gchar * /*sender*/,
    const gchar * /*objectPath*/, const gchar * /*interfaceName*/,
    const gchar *methodName, GVariant *parameters,
    GDBusMethodInvocation *invocation, gpointer self) {
  auto *bridge = static_cast<KWinScriptBridge *>(self);

  if (g_strcmp0(methodName, "Reply") != 0) {
    g_dbus_method_invocation_return_error(invocation, G_DBUS_ERROR,
                                          G_DBUS_ERROR_UNKNOWN_METHOD,
                                          "Unknown method");
    return;
  }

  const gchar *requestId = nullptr;
  const gchar *text = nullptr;
  g_variant_get(parameters, "(&s&s)", &requestId, &text);
  g_dbus_method_invocation_return_value(invocation, nullptr);

  // Ignore late replies to requests that timed out
  if (std::to_string(bridge->pendingRequestId) != requestId) {
    return;
  }

  GError *error = nullptr;
  GVariant *result =
      g_variant_parse(G_VARIANT_TYPE_VARDICT, text, nullptr, nullptr, &error);
  if (result == nullptr) {
    tlg::error << "Error parsing the reply from KWin: "
               << ((error != nullptr) ? error->message : "unknown")
               << std::endl;
    g_clear_error(&error);
  } else {
    // g_variant_parse returns a non-floating reference
    bridge->pendingResult = result;
  }

  bridge->pendingReplied = true;
}

namespace kwin_result {
std::string getString(GVariant *dict, const char *key,
                      const std::string &fallback) {
  const gchar *value = nullptr;
  if (dict != nullptr && g_variant_lookup(dict, key, "&s", &value)) {
    return value;
  }
  return fallback;
}

double getDouble(GVariant *dict, const char *key, double fallback) {
  double value = 0;
  if (dict != nullptr && g_variant_lookup(dict, key, "d", &value)) {
    return value;
  }
  return fallback;
}

bool getBool(GVariant *dict, const char *key, bool fallback) {
  gboolean value = FALSE;
  if (dict != nullptr && g_variant_lookup(dict, key, "b", &value)) {
    return value != FALSE;
  }
  return fallback;
}
}  // namespace kwin_result
