/**
 * @file /src/touchegg/actions/implementations/ShowDesktop.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ShowDesktop
 * @author José Expósito
 */
#include "ShowDesktop.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ShowDesktop::ShowDesktop(const QString& settings)
        : Action(settings) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void ShowDesktop::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void ShowDesktop::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void ShowDesktop::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {
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

    // Mostramos el escritorio
    XClientMessageEvent event;
    event.window = window;
    event.type = ClientMessage;
    event.message_type = XInternAtom(QX11Info::display(),
        "_NET_SHOWING_DESKTOP", false);
    event.format = 32;
    event.data.l[0] = true;

    XSendEvent(QX11Info::display(),
            QX11Info::appRootWindow(QX11Info::appScreen()), false,
            (SubstructureNotifyMask | SubstructureRedirectMask),
            (XEvent*)&event);
    XFlush(QX11Info::display());
}
