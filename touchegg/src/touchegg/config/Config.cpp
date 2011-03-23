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

const char* Config::USR_SHARE_CONFIG_FILE = "/usr/share/touchegg/touchegg.conf";
const char* Config::HOME_CONFIG_FILE      = "/.touchegg/touchegg.conf";
const char* Config::HOME_CONFIG_DIR       = ".touchegg";
const char* Config::TAP_AND_HOLD_TIME     = "GENERAL_CONFIG/tap_and_hold_time";

//------------------------------------------------------------------------------

Config* Config::instance = NULL;

Config* Config::getInstance() {
    if(Config::instance == NULL)
        Config::instance = new Config();

    return Config::instance;
}

void Config::loadConfig() {
    if(instance != NULL) {
        delete instance;
        instance = NULL;
    }
    Config::getInstance();
}


// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

Config::Config() {
    QFile homeFile(QDir::homePath() + HOME_CONFIG_FILE);
    QFile usrFile(USR_SHARE_CONFIG_FILE);

    if(!usrFile.exists()) {
        qDebug() << USR_SHARE_CONFIG_FILE
                 << " not found, reinstall application can solve the problem";
        exit(-1);
    }

    if(!homeFile.exists()) {
        qDebug() << QDir::homePath() + HOME_CONFIG_FILE
                 << " not found, copying config from "
                 << USR_SHARE_CONFIG_FILE;
        QDir::home().mkdir(HOME_CONFIG_DIR);
        usrFile.copy(QDir::homePath() + HOME_CONFIG_FILE);
    }

    qDebug() << "Reading config from " << QDir::homePath() + HOME_CONFIG_FILE;
    this->settings = new QSettings(QDir::homePath() + HOME_CONFIG_FILE,
            QSettings::NativeFormat);
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QStringList Config::getUsedGestures() const {
    QStringList allGestures = this->settings->childGroups();
    QStringList usedGestures;

    for(int n=0; n<allGestures.size(); n++) {
        QString action = ActionTypeEnum::getValue(getAssociatedAction(
                GestureTypeEnum::getEnum(allGestures.at(n))));
        if(action != "" && action != "NO_ACTION")
            usedGestures.append(GestureTypeEnum::getGeisEquivalent(
                    GestureTypeEnum::getEnum(allGestures.at(n))));
    }

    usedGestures.removeDuplicates();
    return usedGestures;
}

//------------------------------------------------------------------------------

int Config::getTapAndHoldTime() const {
    return this->settings->value(TAP_AND_HOLD_TIME).toInt();
}

//------------------------------------------------------------------------------

ActionTypeEnum::ActionType Config::getAssociatedAction(
        GestureTypeEnum::GestureType gestureType) const {
    QString gesture = GestureTypeEnum::getValue(gestureType);
    QString action  = this->settings->value(gesture + "/action").toString();
    return ActionTypeEnum::getEnum(action);
}

QString Config::getAssociatedSettings(GestureTypeEnum::GestureType
        gestureType) const {
    QString gesture = GestureTypeEnum::getValue(gestureType);
    return this->settings->value(gesture + "/settings").toString();
}
