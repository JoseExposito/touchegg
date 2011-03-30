/**
 * @file /src/touchegg/actions/implementation/MoveWindow.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MoveWindow
 * @author José Expósito
 */
#include "MoveWindow.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MoveWindow::MoveWindow(const QString& settings, Window window)
        : Action(settings, window) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void MoveWindow::executeStart(const QHash<QString, QVariant>& /*attrs*/) {
    XTestFakeKeyEvent(QX11Info::display(),
            XKeysymToKeycode(QX11Info::display(), XK_Alt_L), true, 0);
    XTestFakeButtonEvent(QX11Info::display(), Button1, true, 0);
    XFlush(QX11Info::display());
}

void MoveWindow::executeUpdate(const QHash<QString, QVariant>& attrs) {
    if(!attrs.contains(GEIS_GESTURE_ATTRIBUTE_DELTA_X)
            || !attrs.contains(GEIS_GESTURE_ATTRIBUTE_DELTA_Y))
        return;

    XTestFakeRelativeMotionEvent(QX11Info::display(),
            + attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() * 3,
            + attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() * 3, 0);

    XFlush(QX11Info::display());
}

void MoveWindow::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {
    XTestFakeKeyEvent(QX11Info::display(),
            XKeysymToKeycode(QX11Info::display(), XK_Alt_L), false, 0);
    XTestFakeButtonEvent(QX11Info::display(), Button1, false, 0);
    XFlush(QX11Info::display());
}
