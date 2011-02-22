/**
 * @file /src/touchegg-gui/data/transaction_manager/TransactionManager.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  TransactionManager
 * @author José Expósito
 */
#include "TransactionManager.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

const char* TransactionManager::HOME_CONFIG_FILE = "/.touchegg/touchegg.conf";
TransactionManager* TransactionManager::instance = NULL;

TransactionManager* TransactionManager::getInstance() {
    if(TransactionManager::instance == NULL) {
        TransactionManager::instance = new TransactionManager();
        instance->loadConfig();
    }

    return TransactionManager::instance;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void TransactionManager::loadConfig() {
    QFile configFile(QDir::homePath() + HOME_CONFIG_FILE);
    if(!configFile.exists()) {
        // TODO Notificar a la interfaz
        qFatal("Configuration file not found, Touchégg is installed?");
    }

    this->settings = new QSettings(QDir::homePath() + HOME_CONFIG_FILE,
            QSettings::NativeFormat);
}

void TransactionManager::commit() {
    this->settings->
}

void TransactionManager::rollback() {

}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QSettings* TransactionManager::getResource() {
    return this->settings;
}
