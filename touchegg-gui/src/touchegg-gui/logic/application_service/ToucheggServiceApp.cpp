/**
 * @file /src/touchegg-gui/logic/application_service/ToucheggServiceApp.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ToucheggServiceApp
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "ToucheggServiceApp.h"

// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

QString ToucheggServiceApp::read(const QString& path) const {
    TransactionManager* tm = TransactionManager::getInstance();
    ToucheggDao dao(tm->getResource());
    return dao.read(path);
}

void ToucheggServiceApp::update(const QString& path, const QString& value)
        const {
    TransactionManager* tm = TransactionManager::getInstance();
    ToucheggDao dao(tm->getResource());
    dao.update(path, value);
}

void ToucheggServiceApp::remove(const QString& path) const {
    TransactionManager* tm = TransactionManager::getInstance();
    ToucheggDao dao(tm->getResource());
    dao.remove(path);
}

QStringList ToucheggServiceApp::getUsedApplications() const {
    TransactionManager* tm = TransactionManager::getInstance();
    ToucheggDao dao(tm->getResource());
    return dao.getUsedApplications();
}

QStringList ToucheggServiceApp::getUsedGestures(const QString& app) const {
    TransactionManager* tm = TransactionManager::getInstance();
    ToucheggDao dao(tm->getResource());
    return dao.getUsedGestures(app);
}
