/**
 * @file /src/touchegg/config/Config.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  Config
 * @author José Expósito
 */
#include "Config.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

const char* Config::USR_SHARE_CONFIG_FILE    =
        "/usr/share/touchegg/touchegg.conf";
const char* Config::HOME_CONFIG_FILE         = "/.touchegg/touchegg.conf";

const char* Config::TWO_FINGERS_TAP          = "TWO_FINGERS_TAP";
const char* Config::THREE_FINGERS_TAP        = "THREE_FINGERS_TAP";
const char* Config::FOUR_FINGERS_TAP         = "FOUR_FINGERS_TAP";
const char* Config::FIVE_FINGERS_TAP         = "FIVE_FINGERS_TAP";

const char* Config::THREE_FINGERS_PINCH      = "THREE_FINGERS_PINCH";

const char* Config::TWO_FINGERS_DRAG_UP      = "TWO_FINGERS_DRAG_UP";
const char* Config::TWO_FINGERS_DRAG_DOWN    = "TWO_FINGERS_DRAG_DOWN";
const char* Config::TWO_FINGERS_DRAG_LEFT    = "TWO_FINGERS_DRAG_LEFT";
const char* Config::TWO_FINGERS_DRAG_RIGHT   = "TWO_FINGERS_DRAG_RIGHT";
const char* Config::THREE_FINGERS_DRAG_UP    = "THREE_FINGERS_DRAG_UP";
const char* Config::THREE_FINGERS_DRAG_DOWN  = "THREE_FINGERS_DRAG_DOWN";
const char* Config::THREE_FINGERS_DRAG_LEFT  = "THREE_FINGERS_DRAG_LEFT";
const char* Config::THREE_FINGERS_DRAG_RIGHT = "THREE_FINGERS_DRAG_RIGHT";
const char* Config::FOUR_FINGERS_DRAG_UP     = "FOUR_FINGERS_DRAG_UP";
const char* Config::FOUR_FINGERS_DRAG_DOWN   = "FOUR_FINGERS_DRAG_DOWN";
const char* Config::FOUR_FINGERS_DRAG_LEFT   = "FOUR_FINGERS_DRAG_LEFT";
const char* Config::FOUR_FINGERS_DRAG_RIGHT  = "FOUR_FINGERS_DRAG_RIGHT";

const char* Config::RIGHT_BUTTON_CLICK       = "RIGHT_BUTTON_CLICK";
const char* Config::MIDDLE_BUTTON_CLICK      = "MIDDLE_BUTTON_CLICK";
const char* Config::MOUSE_WHELL_UP           = "MOUSE_WHEEL_UP";
const char* Config::MOUSE_WHELL_DOWN         = "MOUSE_WHEEL_DOWN";
const char* Config::MINIMIZE_WINDOW          = "MINIMIZE_WINDOW";
const char* Config::MAXIMIZE_RESTORE_WINDOW  = "MAXIMIZE_RESTORE_WINDOW";
const char* Config::CLOSE_WINDOW             = "CLOSE_WINDOW";
const char* Config::RESIZE_WINDOW            = "RESIZE_WINDOW";
const char* Config::SHOW_DESKTOP             = "SHOW_DESKTOP";
const char* Config::CHANGE_DESKTOP           = "CHANGE_DESKTOP";
const char* Config::SEND_KEYS                = "SEND_KEYS";

//------------------------------------------------------------------------------

Config* Config::instance = NULL;

Config* Config::getInstance() {
    if(Config::instance == NULL)
        Config::instance = new Config();

    return Config::instance;
}


Config::Config() {
    // Intentamos leer la configuración del home
    QString homePath = getenv("HOME");

    QFile homeFile(homePath+HOME_CONFIG_FILE);
    QFile usrFile(USR_SHARE_CONFIG_FILE);

    if(homeFile.exists()) {
        qDebug() << "Reading config from " << homePath + HOME_CONFIG_FILE;
        this->settings = new QSettings(homePath + HOME_CONFIG_FILE,
            QSettings::NativeFormat);
    } else if(usrFile.exists()) {
        qDebug() << "Reading config from " << USR_SHARE_CONFIG_FILE;
        this->settings = new QSettings(USR_SHARE_CONFIG_FILE,
            QSettings::NativeFormat);
    } else {
        qFatal("ERROR: Could not read configuration");
    }
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

Action* Config::getAssociatedAction(const char* gesture) const {
    QString action    = this->settings->value(
            QString(gesture)+"/action").toString();
    QString actionCfg = this->settings->value(
            QString(gesture)+"/settings").toString();

    if(action == RIGHT_BUTTON_CLICK)
        return new RightButtonClick(actionCfg);

    else if(action == MIDDLE_BUTTON_CLICK)
        return new MiddleButtonClick(actionCfg);

    else if(action == MOUSE_WHELL_UP)
        return new MouseWheelUp(actionCfg);

    else if(action == MOUSE_WHELL_DOWN)
        return new MouseWheelDown(actionCfg);

    else if(action == MINIMIZE_WINDOW)
        return new MinimizeWindow(actionCfg);

    else if(action == MAXIMIZE_RESTORE_WINDOW)
        return new MaximizeRestoreWindow(actionCfg);

    else if(action == CLOSE_WINDOW)
        return new CloseWindow(actionCfg);

    else if(action == RESIZE_WINDOW)
        return new ResizeWindow(actionCfg);

    else if(action == SHOW_DESKTOP)
        return new ShowDesktop(actionCfg);

    else if(action == CHANGE_DESKTOP)
        return new ChangeDesktop(actionCfg);

    else if(action == SEND_KEYS)
        return new SendKeys(actionCfg);

    else
        return NULL;
}
