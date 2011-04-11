/**
 * @file /src/touchegg/actions/implementation/ChangeViewport.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ChangeViewport
 * @author José Expósito
 */
#include "ChangeViewport.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ChangeViewport::ChangeViewport(const QString& settings, Window window)
        : Action(settings, window) {
    this->next = true;

    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "DIRECTION") {
        QString configDir = strl.at(1);
        if(configDir == "PREVIOUS")
            this->next = false;
        else if(configDir == "NEXT")
            this->next = true;
        else
            qWarning() << "Error reading CHANGE_VIEWPORT settings, using " <<
                    "the default settings";
    } else
        qWarning() << "Error reading CHANGE_VIEWPORT settings, using " <<
                "the default settings";
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void ChangeViewport::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void ChangeViewport::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void ChangeViewport::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {
    // Obtenemos el tamaño total de todos los viewports juntos
    Atom atomRet;
    int size;
    unsigned long numItems, bytesAfterReturn;
    unsigned char* propRet;

    int widthViews, heightViews;
    if(XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(),
            XInternAtom(QX11Info::display(), "_NET_DESKTOP_GEOMETRY", false),
            0, 100, false, XA_CARDINAL, &atomRet, &size, &numItems,
            &bytesAfterReturn, &propRet) == Success && numItems == 2) {
        int* aux = (int*)propRet;
        widthViews  = aux[0];
        heightViews = aux[1];
        XFree(propRet);
    } else {
        return;
    }

    // Obtenemos las coordenadas del viewport actual
    int currentX, currentY;
    if(XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(),
            XInternAtom(QX11Info::display(), "_NET_DESKTOP_VIEWPORT", false),
            0, 100, false, XA_CARDINAL, &atomRet, &size, &numItems,
            &bytesAfterReturn, &propRet) == Success && numItems == 2) {
        int* aux = (int*)propRet;
        currentX = aux[0];
        currentY = aux[1];
        XFree(propRet);
    } else {
        return;
    }

    // Obtenemos las coordenadas del viewport anterior/siguiente
    int nextX, nextY;
    if(this->next) {
        nextX = (currentX + QApplication::desktop()->width()) % widthViews;
        nextY = nextX == 0
                ? (currentY + QApplication::desktop()->height()) % heightViews
                : currentY;
    } else {
        nextX = (currentX - QApplication::desktop()->width()) % widthViews;
        if(nextX < 0) {
            nextY = (currentY-QApplication::desktop()->height()) % heightViews;
            nextX *= -1;
            nextY *= -1;
        } else {
            nextY = currentY;
        }
    }

    // Cambiamos de viewport
    XClientMessageEvent event;
    event.window = QX11Info::appRootWindow(QX11Info::appScreen());
    event.type = ClientMessage;
    event.message_type = XInternAtom(QX11Info::display(),
            "_NET_DESKTOP_VIEWPORT", false);
    event.format = 32;
    event.data.l[0] = nextX;
    event.data.l[1] = nextY;

    XSendEvent(QX11Info::display(),
            QX11Info::appRootWindow(QX11Info::appScreen()), false,
            (SubstructureNotifyMask | SubstructureRedirectMask),
            (XEvent*)&event);
    XFlush(QX11Info::display());
}
