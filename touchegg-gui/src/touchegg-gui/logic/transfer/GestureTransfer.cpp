/**
 * @file /src/touchegg-gui/logic/transfer/GestureTransfer.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureTransfer
 * @author José Expósito
 */
#include "GestureTransfer.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

GestureTransfer::GestureTransfer(GestureTypeEnum::GestureType gestureType) {
    this->gestureType = gestureType;
}

GestureTransfer::GestureTransfer(GestureTypeEnum::GestureType gestureType,
        ActionTypeEnum::ActionType actionType, const QString& settings) {
    this->gestureType = gestureType;
    this->actionType  = actionType;
    this->settings    = settings;
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

GestureTypeEnum::GestureType GestureTransfer::getGestureType() const {
    return this->gestureType;
}

ActionTypeEnum::ActionType GestureTransfer::getActionType() const {
    return this->actionType;
}

const QString& GestureTransfer::getSettings() const {
    return this->settings;
}

void GestureTransfer::setGestureType(GestureTypeEnum::GestureType gestureType) {
    this->gestureType = gestureType;
}

void GestureTransfer::setActionType(ActionTypeEnum::ActionType actionType) {
    this->actionType = actionType;
}

void GestureTransfer::setSettings(const QString& settings) {
    this->settings = settings;
}
