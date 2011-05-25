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
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "TransactionManager.h"


// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

const char* TransactionManager::HOME_CONFIG_FILE ="/.touchegg/touchegg.conf";
const char* TransactionManager::USR_SHARE_CONFIG_FILE =
        "/usr/share/touchegg/touchegg.conf";
const char* TransactionManager::HOME_CONFIG_DIR = ".touchegg";

//------------------------------------------------------------------------------

TransactionManager* TransactionManager::instance = NULL;

TransactionManager* TransactionManager::getInstance() {
    if(TransactionManager::instance == NULL)
        TransactionManager::instance = new TransactionManager;

    return TransactionManager::instance;
}


// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

TransactionManager::TransactionManager() {
    this->settings = new QHash<QString, QString>;

    // Comprobamos que los archivos estén en su sitio
    QFile homeFile(QDir::homePath() + HOME_CONFIG_FILE);
    QFile usrFile(USR_SHARE_CONFIG_FILE);

    if(!usrFile.exists()) {
        qFatal("%s not found, reinstall Touchégg can solve the problem\n",
               USR_SHARE_CONFIG_FILE);
    }

    if(!homeFile.exists()) {
        qDebug() << QDir::homePath() + HOME_CONFIG_FILE
                 << " not found, copying config from "
                 << USR_SHARE_CONFIG_FILE;
        QDir::home().mkdir(HOME_CONFIG_DIR);
        usrFile.copy(QDir::homePath() + HOME_CONFIG_FILE);
    }

    // Cargamos la confiuración en el QHash
    qDebug() << "Reading config from " << QDir::homePath() + HOME_CONFIG_FILE;
    this->loadConfig(homeFile);
}


// ************************************************************************** //
// **********                   PRIVATE METHODS                    ********** //
// ************************************************************************** //

void TransactionManager::loadConfig(QFile& file) {
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd()) {
        QString line(file.readLine());
        line = line.trimmed();
        int index = line.indexOf("=");

        if(line != "" && index != -1) {
            QString key   = line.left(index);
            QString value = line.mid(index+1);
            this->settings->insert(key, value);
        }
    }
    file.close();
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void TransactionManager::commit() {
    // Guardamos los cambios
    QFile file(QDir::homePath() + HOME_CONFIG_FILE);
    file.open(QIODevice::WriteOnly);
    QTextStream ts(&file);

    QHash<QString, QString>::iterator i;
    for (i = this->settings->begin(); i != this->settings->end(); ++i) {
        ts << i.key() << "=" << i.value() << "\n";
    }
    file.close();

    // Matamos el proceso de Touchégg y lo volvemos a lanzar...
    // Si, si, si, esto en un transaction manager pues como que no pega, pero en
    // algún lado había que meterlo y si, también, el método es muy cutre
    QProcess* myProcess = new QProcess();
    myProcess->start("killall -9 touchegg");
    myProcess->waitForFinished();
    myProcess->startDetached("touchegg");
}

void TransactionManager::rollback() {
    delete this->settings;
    this->settings = new QHash<QString, QString>;
    QFile homeFile(QDir::homePath() + HOME_CONFIG_FILE);
    this->loadConfig(homeFile);
}

// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QHash<QString, QString>* TransactionManager::getResource() const {
    return this->settings;
}
