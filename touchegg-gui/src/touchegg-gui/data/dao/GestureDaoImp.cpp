/**
 * @file /src/touchegg-gui/data/dao/GeneralDaoImp.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GeneralDaoImp
 * @author José Expósito
 */
#include "GeneralDaoImp.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

GeneralDaoImp::GeneralDaoImp(QSettings* settings) : GeneralDao(settings) {
    this->settings = settings;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

GeneralTransfer GeneralDaoImp::read(const QString& property) {
    QString v = this->settings->value("GENERAL_CONFIG/" + property).toString();
    GeneralTransfer ret(property, v);
    return ret;
}

void GeneralDaoImp::update(const GeneralTransfer& property) {
    this->settings->setValue("GENERAL_CONFIG/" + property.getField(),
            property.getValue());
}
