/**
 * @file /src/touchegg/actions/implementation/CloseWindow.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  CloseWindow
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "CloseWindow.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

CloseWindow::CloseWindow(const QString& settings, Window window)
        : Action(settings, window) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void CloseWindow::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void CloseWindow::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void CloseWindow::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {
    // Cerramos la ventana
    XClientMessageEvent event;
    event.window = this->window;
    event.type = ClientMessage;
    event.message_type = XInternAtom(QX11Info::display(), "_NET_CLOSE_WINDOW",
            false);
    event.format = 32;
    event.data.l[0] = CurrentTime;
    event.data.l[1] = 2;

    XSendEvent(QX11Info::display(),
            QX11Info::appRootWindow(QX11Info::appScreen()), false,
            (SubstructureNotifyMask | SubstructureRedirectMask),
            (XEvent*)&event);

    XFlush(QX11Info::display());
}
