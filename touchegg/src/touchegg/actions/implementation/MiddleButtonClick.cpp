/**
 * @file /src/touchegg/actions/implementation/MiddleButtonClick.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MiddleButtonClick
 * @author José Expósito
 */
#include "MiddleButtonClick.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MiddleButtonClick::MiddleButtonClick(const QString& settings)
        : Action(settings) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void MiddleButtonClick::executeStart(const QHash<QString, QVariant>&) {}

void MiddleButtonClick::executeFinish(const QHash<QString, QVariant>&) {}

void MiddleButtonClick::executeUpdate(const QHash<QString, QVariant>&) {
    XTestFakeButtonEvent(QX11Info::display(), Button2, true, 0);
    XTestFakeButtonEvent(QX11Info::display(), Button2, false, 0);
    XFlush(QX11Info::display());
}
