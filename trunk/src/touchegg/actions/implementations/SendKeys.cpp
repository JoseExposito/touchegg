/**
 * @file /src/touchegg/actions/implementations/SendKeys.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  SendKeys
 * @author José Expósito
 */
#include "SendKeys.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

SendKeys::SendKeys(const QString& settings)
        : Action(settings) {
    // TODO Implementar
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void SendKeys::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void SendKeys::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void SendKeys::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {}
