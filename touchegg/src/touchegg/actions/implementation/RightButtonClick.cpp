/**
 * @file /src/touchegg/actions/implementation/RightButtonClick.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  RightButtonClick
 * @author José Expósito
 */
#include "RightButtonClick.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

RightButtonClick::RightButtonClick(const QString& settings)
        : Action(settings) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void RightButtonClick::executeStart(const QHash<QString, QVariant>&) {}

void RightButtonClick::executeFinish(const QHash<QString, QVariant>&) {}

void RightButtonClick::executeUpdate(const QHash<QString, QVariant>&) {
    XTestFakeButtonEvent(QX11Info::display(), Button3, true, 0);
    XTestFakeButtonEvent(QX11Info::display(), Button3, false, 0);
}
