/**
 * @file /src/touchegg-gui/logic/transfer/GeneralTransfer.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GeneralTransfer
 * @author José Expósito
 */
#include "GeneralTransfer.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

GeneralTransfer::GeneralTransfer(const QString& field, const QString& value) {
    this->field = field;
    this->value = value;
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

const QString& GeneralTransfer::getField() const {
    return this->field;
}

const QString& GeneralTransfer::getValue() const {
    return this->value;
}

void GeneralTransfer::setField(const QString& field) {
    this->field = field;
}

void GeneralTransfer::setValue(const QString& value) {
    this->value = value;
}
