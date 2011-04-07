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

    // Cargamos en memoria la configuración
    QDomDocument document;
    QFile cfgFile(QDir::homePath() + HOME_CONFIG_FILE);
    if (!cfgFile.open(QIODevice::ReadOnly))
        qFatal("Can't open file for read");
    if (!document.setContent(&cfgFile)) {
        cfgFile.close();
        qFatal("Error reading configuration, please, review the format");
    }
    cfgFile.close();

    QDomElement root = document.documentElement();
    this->initConfig(root.firstChild(), root.toElement().tagName());
}

// ************************************************************************** //
// **********                   PRIVATE METHODS                    ********** //
// ************************************************************************** //

void Config::initConfig(QDomNode node, const QString& keyString) {
    while(!node.isNull()) {
        if(!node.toElement().isNull()) {
            QString newKey = keyString +"/"+ node.toElement().attribute("type");
            if(!node.hasChildNodes()
                    || (node.hasChildNodes() && node.firstChild().isText())) {
                // Guardamos el valor en el QHash
                QString text = node.toElement().text();
                this->settings.insert(newKey, text);

                // Si es un gesto y está en uso, lo añadimos a la lista de
                // gestos usados
                QStringList aux = newKey.split("/");
                if(aux.size() == 4 && aux.at(3) == "action"
                        && text != "" && text != "NO_ACTION") {
                    QStringList geisEquiv = GestureTypeEnum::getGeisEquivalent(
                            GestureTypeEnum::getEnum(aux.at(1)));
                    this->usedGestures.append(geisEquiv);
                }
            } else {
                this->initConfig(node.firstChild(), newKey);
            }
        }
        node = node.nextSibling();
    }
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
            "touchegg/general_settings/tap_and_hold_time").toInt(&ok);
    return ok ? ret : 135;
}

//------------------------------------------------------------------------------

ActionTypeEnum::ActionType Config::getAssociatedAction(
        GestureTypeEnum::GestureType gestureType, QString appClass) const {
    QString gesture = GestureTypeEnum::getValue(gestureType);
    QString keyWithClass = "touchegg/" + gesture + "/" + appClass + "/action";

    if(this->settings.contains(keyWithClass)) {
        return ActionTypeEnum::getEnum(this->settings.value(keyWithClass));
    } else {
        QString keyWithClass = "touchegg/" + gesture + "/ALL/action";
        return ActionTypeEnum::getEnum(this->settings.value(keyWithClass));
    }
}

QString Config::getAssociatedSettings(GestureTypeEnum::GestureType
        gestureType) const {
    QString gesture = GestureTypeEnum::getValue(gestureType);
    QString key = "touchegg/" + gesture + "/ALL/settings";
    return this->settings.value(key);
}
