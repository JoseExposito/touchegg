/**
 * @file /src/touchegg-gui/data/transaction_manager/TransactionManagerImp.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  TransactionManagerImp
 * @author José Expósito
 */
#include "TransactionManagerImp.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

const char* TransactionManagerImp::HOME_CONFIG_FILE ="/.touchegg/touchegg.conf";


// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

TransactionManagerImp::TransactionManagerImp() : TransactionManager() {
    this->settings = NULL;
    this->loadConfig();
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void TransactionManagerImp::loadConfig() {
    QFile configFile(QDir::homePath() + HOME_CONFIG_FILE);
    if(!configFile.exists()) {
        // TODO Notificar a la interfaz
        qFatal("Configuration file not found, Touchégg is installed?");
    }

    if(this->settings != NULL)
        delete this->settings;

    this->settings = new QSettings(QDir::homePath() + HOME_CONFIG_FILE,
            QSettings::NativeFormat);
}

void TransactionManagerImp::commit() {
    this->loadConfig();
}

void TransactionManagerImp::rollback() {
    // Nothing
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QSettings* TransactionManagerImp::getResource() const {
    return this->settings;
}
