/**
 * @file /src/touchegg/actions/implementation/MinimizeWindow.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MinimizeWindow
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "MinimizeWindow.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MinimizeWindow::MinimizeWindow(const QString& settings, Window window)
        : Action(settings, window) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void MinimizeWindow::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void MinimizeWindow::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void MinimizeWindow::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {
    // Minimizamos la ventana
    XClientMessageEvent event;
    event.window = this->window;
    event.type = ClientMessage;
    event.message_type = XInternAtom(QX11Info::display(), "WM_CHANGE_STATE",
            false);
    event.format = 32;
    event.data.l[0] = IconicState;

    XSendEvent(QX11Info::display(),
            QX11Info::appRootWindow(QX11Info::appScreen()), false,
            (SubstructureNotifyMask | SubstructureRedirectMask),
            (XEvent*)&event);
    XFlush(QX11Info::display());
}
