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
 * @author José Expósito
 */
#include "CloseWindow.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

CloseWindow::CloseWindow(const QString& settings)
        : Action(settings) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void CloseWindow::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void CloseWindow::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void CloseWindow::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {
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

    // Cerramos la ventana
    XClientMessageEvent event;
    event.window = window;
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
