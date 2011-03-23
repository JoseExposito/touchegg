/**
 * @file /src/touchegg/actions/implementation/LeftButtonClick.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  LeftButtonClick
 * @author José Expósito
 */
#include "LeftButtonClick.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

LeftButtonClick::LeftButtonClick(const QString& settings)
        : Action(settings) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void LeftButtonClick::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void LeftButtonClick::executeFinish(const QHash<QString, QVariant>& /*attrs*/){}

void LeftButtonClick::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {
    XTestFakeButtonEvent(QX11Info::display(), Button1, true, 0);
    XTestFakeButtonEvent(QX11Info::display(), Button1, false, 0);
    XFlush(QX11Info::display());
}
