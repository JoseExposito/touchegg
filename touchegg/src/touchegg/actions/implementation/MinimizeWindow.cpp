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
 * @author José Expósito
 */
#include "MinimizeWindow.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MinimizeWindow::MinimizeWindow(const QString& settings)
        : Action(settings) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void MinimizeWindow::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void MinimizeWindow::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void MinimizeWindow::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {
    // Obtenemos la ventana activa
    Atom atomRet;
    int size;
    unsigned long numItems, bytesAfterReturn;
    unsigned char* propRet;

    XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(),
            XInternAtom(QX11Info::display(), "_NET_ACTIVE_WINDOW", false),
            0, 1, false, XA_WINDOW, &atomRet, &size, &numItems,
            &bytesAfterReturn, &propRet);
    Window window = *((Window *) propRet);
    XFree(propRet);

    // Minimizamos la ventana
    XClientMessageEvent event;
    event.window = window;
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
