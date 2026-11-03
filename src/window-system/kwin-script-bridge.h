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
#ifndef WINDOW_SYSTEM_KWIN_SCRIPT_BRIDGE_H_
#define WINDOW_SYSTEM_KWIN_SCRIPT_BRIDGE_H_

#include <gio/gio.h>

#include <memory>
#include <string>

/**
 * Wayland doesn't allow clients to inspect or manage other clients' windows.
 * On KDE Plasma, KWin exposes a JavaScript scripting API that can do it, and
 * any session process can load scripts over D-Bus.
 *
 * This class runs a snippet of JavaScript inside KWin and returns the object
 * it returns. The result is sent back to us with KWin's callDBus() function,
 * serialized as a GVariant text dictionary (a{sv}).
 *
 * A round trip takes ~1ms, so it is fast enough to run on every gesture.
 */
class KWinScriptBridge {
 public:
  KWinScriptBridge();
  ~KWinScriptBridge();

  KWinScriptBridge(const KWinScriptBridge &) = delete;
  KWinScriptBridge &operator=(const KWinScriptBridge &) = delete;

  /**
   * @returns If KWin is running on the current D-Bus session.
   */
  static bool isKWinRunning();

  /**
   * Run JavaScript inside KWin and wait for its result.
   *
   * @param body The body of a JavaScript function. It can `return` an object
   * whose values are strings, numbers or booleans. The helper function
   * `findWindow(internalId)` is available.
   * @returns A GVariant dictionary (a{sv}) owned by the caller or nullptr on
   * error. Use g_variant_unref to free it.
   */
  GVariant *run(const std::string &body) const;

  /**
   * D-Bus handler for the replies sent by the KWin script.
   */
  static void onMethodCall(GDBusConnection *connection, const gchar *sender,
                           const gchar *objectPath, const gchar *interfaceName,
                           const gchar *methodName, GVariant *parameters,
                           GDBusMethodInvocation *invocation, gpointer self);

 private:
  GMainContext *context = nullptr;
  GDBusConnection *connection = nullptr;
  guint registrationId = 0;
  std::string scriptPath;
  std::string pluginName;

  mutable uint64_t nextRequestId = 1;
  mutable uint64_t pendingRequestId = 0;
  mutable GVariant *pendingResult = nullptr;
  mutable bool pendingReplied = false;

  std::string buildScript(const std::string &body, uint64_t requestId) const;
  bool callKWin(const char *objectPath, const char *interfaceName,
                const char *method, GVariant *parameters,
                const GVariantType *replyType, GVariant **reply) const;
  void unloadScript(bool wait) const;
};

/**
 * Helpers to read values from the dictionary returned by
 * KWinScriptBridge::run.
 */
namespace kwin_result {
std::string getString(GVariant *dict, const char *key,
                      const std::string &fallback = "");
double getDouble(GVariant *dict, const char *key, double fallback = 0);
bool getBool(GVariant *dict, const char *key, bool fallback = false);
}  // namespace kwin_result

#endif  // WINDOW_SYSTEM_KWIN_SCRIPT_BRIDGE_H_
