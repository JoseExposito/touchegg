/**
 * @file /src/touchegg-gui/data/dao/ToucheggDao.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ToucheggDao
 * @author José Expósito
 */
#include "ToucheggDao.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ToucheggDao::ToucheggDao(QHash<QString, QString>* settings) {
    this->settings = settings;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

QString ToucheggDao::read(const QString& path) const {
    return this->settings->value(path, "");
}

void ToucheggDao::update(const QString& path, const QString& value) {
    this->settings->insert(path, value);
}

void ToucheggDao::remove(const QString& path) {
    this->settings->remove(path);
}

QStringList ToucheggDao::getUsedApplications() const {
    QStringList ret;
    ret.append("ALL"); // Le añadimos ALL para que siempre esté disponible

    QHash<QString, QString>::iterator i;
    for (i = this->settings->begin(); i != this->settings->end(); ++i) {
        QString key = i.key();
        QStringList aux = key.split(".");
        if(aux.length() == 3)
            ret.append(aux.at(1));
    }

    ret.removeDuplicates();
    return ret;
}

QStringList ToucheggDao::getUsedGestures(const QString& app) const {
    QStringList ret;
    QHash<QString, QString>::iterator i;
    for (i = this->settings->begin(); i != this->settings->end(); ++i) {
        QString key = i.key();
        QStringList aux = key.split(".");
        if(aux.length() == 3 && aux.at(1) == app)
            ret.append(aux.at(0));
    }

    ret.removeDuplicates();
    return ret;
}
