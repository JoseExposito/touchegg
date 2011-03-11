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
    if(this->settings != NULL)
        delete this->settings;

    this->settings = new QSettings(QDir::homePath() + HOME_CONFIG_FILE,
            QSettings::NativeFormat);
}

void TransactionManagerImp::commit() {
    // Matamos el proceso de Touchégg y lo volvemos a lanzar...
    // Si, si, si, esto en un transaction manager pues como que no pega, pero en
    // algún lado había que meterlo y si, también, el método es muy cutre
    QProcess* myProcess = new QProcess();
    myProcess->start("killall -9 touchegg");
    myProcess->waitForFinished();
    myProcess->startDetached("touchegg");
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QSettings* TransactionManagerImp::getResource() const {
    return this->settings;
}
