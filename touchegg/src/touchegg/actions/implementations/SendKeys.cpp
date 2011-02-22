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

SendKeys::SendKeys(const QString& settings) : Action(settings) {
    // TODO Read config
}


// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

void SendKeys::sendKey(KeySym key, bool pressed) const {
    // Obtenemos la ventana que tiene el foco
    Window window;
    int    revertTo;
    XGetInputFocus(QX11Info::display(), &window, &revertTo);

    //window = QX11Info::appRootWindow(QX11Info::appScreen());

    // Creamos el evento a enviar
    XKeyEvent event;
    event.display     = QX11Info::display();
    event.root        = QX11Info::appRootWindow(QX11Info::appScreen());
    event.window      = window;
    event.subwindow   = None;
    event.type        = pressed ? KeyPress : KeyRelease;
    event.time        = CurrentTime;
    /*event.x           = 0;
    event.y           = 0;
    event.x_root      = 0;
    event.y_root      = 0;*/
    event.same_screen = true;
    event.keycode     = XKeysymToKeycode(QX11Info::display(), key);
    event.state       = NULL;

    // Enviamos el evento
    XSendEvent(QX11Info::display(), window, true,
            pressed ? KeyPressMask : KeyReleaseMask, (XEvent*)&event);
    XFlush(QX11Info::display());
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void SendKeys::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void SendKeys::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void SendKeys::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {
    // XStringToKeysym !!
    this->sendKey(XK_F4, true);
    usleep(100);
    this->sendKey(XK_F4, false);
}
