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
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "Config.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

const char* Config::USR_SHARE_CONFIG_FILE = "/usr/share/touchegg/touchegg.conf";
const char* Config::HOME_CONFIG_FILE      = "/.touchegg/touchegg.conf";
const char* Config::HOME_CONFIG_DIR       = ".touchegg";

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
    // Comprobamos que los archivos estén en su sitio
    QFile homeFile(QDir::homePath() + HOME_CONFIG_FILE);
    QFile usrFile(USR_SHARE_CONFIG_FILE);

    if(!usrFile.exists()) {
        qFatal("%s not found, reinstall application can solve the problem\n",
               USR_SHARE_CONFIG_FILE);
    }

    if(!homeFile.exists()) {
        qDebug() << QDir::homePath() + HOME_CONFIG_FILE
                 << " not found, copying config from "
                 << USR_SHARE_CONFIG_FILE;
        QDir::home().mkdir(HOME_CONFIG_DIR);
        usrFile.copy(QDir::homePath() + HOME_CONFIG_FILE);
    }

    qDebug() << "Reading config from " << QDir::homePath() + HOME_CONFIG_FILE;
    this->initConfig(homeFile);
}

// ************************************************************************** //
// **********                   PRIVATE METHODS                    ********** //
// ************************************************************************** //

void Config::initConfig(QFile& file) {
    file.open(QIODevice::ReadOnly);

    while(!file.atEnd()) {
        QString line(file.readLine());
        line = line.trimmed();
        int index = line.indexOf("=");

        if(line != "" && index != -1) {
            // Guardamos el valor en el QHash
            QString key   = line.left(index);
            QString value = line.mid(index+1);
            this->settings.insert(key, value);

            // Si es un gesto y está en uso, lo añadimos a la usedGestures
            QStringList aux = key.split(".");
            if(aux.size() == 3 && aux.at(2) == "action"
                    && value != "" && value != "NO_ACTION") {
                QStringList geisEquiv = GestureTypeEnum::getGeisEquivalent(
                    GestureTypeEnum::getEnum(aux.at(0)));
                this->usedGestures.append(geisEquiv);
            }
        }
    }

    this->usedGestures.removeDuplicates();
    file.close();
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QStringList Config::getUsedGestures() const {
    return this->usedGestures;
}

//------------------------------------------------------------------------------

int Config::getTapAndHoldTime() const {
    bool ok;
    int ret = this->settings.value(
            "general_settings.tap_and_hold_time").toInt(&ok);
    return ok ? ret : 135;
}

//------------------------------------------------------------------------------

ActionTypeEnum::ActionType Config::getAssociatedAction(
        GestureTypeEnum::GestureType gestureType, QString appClass) const {
    QString gesture = GestureTypeEnum::getValue(gestureType);
    QString keyWithClass = gesture + "." + appClass + ".action";

    if(this->settings.contains(keyWithClass)) {
        return ActionTypeEnum::getEnum(this->settings.value(keyWithClass));
    } else {
        QString key = gesture + ".ALL.action";
        return ActionTypeEnum::getEnum(this->settings.value(key));
    }
}

QString Config::getAssociatedSettings(GestureTypeEnum::GestureType
        gestureType, QString appClass) const {
    QString gesture = GestureTypeEnum::getValue(gestureType);
    QString keyWithClass = gesture + "." + appClass + ".settings";

    if(this->settings.contains(keyWithClass)) {
        return this->settings.value(keyWithClass);
    } else {
        QString key = gesture + ".ALL.settings";
        return this->settings.value(key);
    }
}
