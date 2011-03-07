/**
 * @file /src/touchegg-gui/data/dao/GestureDaoImp.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureDaoImp
 * @author José Expósito
 */
#include "GestureDaoImp.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

GestureDaoImp::GestureDaoImp(QSettings* settings) : GestureDao(settings) {
    this->settings = settings;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

GestureTransfer GestureDaoImp::read(GestureTypeEnum::GestureType type) {
    QString action = this->settings->value(GestureTypeEnum::getValue(type)
            + "/action").toString();
    QString actionSettings = this->settings->value(
            GestureTypeEnum::getValue(type) + "/settings").toString();

    GestureTransfer ret(type, ActionTypeEnum::getEnum(action), actionSettings);
    return ret;
}

void GestureDaoImp::update(const GestureTransfer& gesture) {
    this->settings->setValue(GestureTypeEnum::getValue(gesture.getGestureType())
            + "/action", ActionTypeEnum::getValue(gesture.getActionType()));
    this->settings->setValue(GestureTypeEnum::getValue(gesture.getGestureType())
            + "/settings", gesture.getSettings());
}
