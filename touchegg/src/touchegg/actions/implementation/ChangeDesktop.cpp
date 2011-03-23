/**
 * @file /src/touchegg/actions/implementation/ChangeDesktop.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ChangeDesktop
 * @author José Expósito
 */
#include "ChangeDesktop.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ChangeDesktop::ChangeDesktop(const QString& settings) : Action(settings) {
    this->toRight = true;

    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "DIRECTION") {
        QString configDir = strl.at(1);
        if(configDir == "LEFT")
            this->toRight = false;
        else if(configDir == "RIGHT")
            this->toRight = true;
        else
            qWarning() << "Error reading CHANGE_DESKTOP settings, using " <<
                    "the default settings";
    } else
        qWarning() << "Error reading CHANGE_DESKTOP settings, using " <<
                "the default settings";
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void ChangeDesktop::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void ChangeDesktop::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void ChangeDesktop::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {
    // Obtenemos el número total de escritorios
    Atom atomRet;
    int size;
    unsigned long numItems, bytesAfterReturn;
    unsigned char* propRet;

    XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(),
            XInternAtom(QX11Info::display(), "_NET_NUMBER_OF_DESKTOPS", false),
            0, 1, false, XA_CARDINAL, &atomRet, &size, &numItems,
            &bytesAfterReturn, &propRet);
    int numDesktops = (int)*propRet;
    XFree(propRet);

    // Obtenemos el escritorio actual
    XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(),
            XInternAtom(QX11Info::display(), "_NET_CURRENT_DESKTOP", false),
            0, 1, false, XA_CARDINAL, &atomRet, &size, &numItems,
            &bytesAfterReturn, &propRet);
    int currentDesktop = (int)*propRet;
    XFree(propRet);

    // Cambiamos al escritorio siguiente o anterior
    int nextDesktop = this->toRight
            ? (currentDesktop + 1) % numDesktops
            : (currentDesktop - 1 + numDesktops) % numDesktops;

    XClientMessageEvent event;
    event.window = QX11Info::appRootWindow(QX11Info::appScreen());
    event.type = ClientMessage;
    event.message_type = XInternAtom(QX11Info::display(),
            "_NET_CURRENT_DESKTOP", false);
    event.format = 32;
    event.data.l[0] = nextDesktop;

    XSendEvent(QX11Info::display(),
            QX11Info::appRootWindow(QX11Info::appScreen()), false,
            (SubstructureNotifyMask | SubstructureRedirectMask),
            (XEvent*)&event);
    XFlush(QX11Info::display());
}
