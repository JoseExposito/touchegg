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

MoveWindow::MoveWindow(const QString& settings) : Action(settings) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void MoveWindow::executeStart(const QHash<QString, QVariant>& /*attrs*/) {
    // Obtenemos la ventana activa, ventana a mover
    Atom atomRet;
    int size;
    unsigned long numItems, bytesAfterReturn;
    unsigned char* propRet;

    XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(),
            XInternAtom(QX11Info::display(), "_NET_ACTIVE_WINDOW", false),
            0, 1, false, XA_WINDOW, &atomRet, &size, &numItems,
            &bytesAfterReturn, &propRet);
    this->window = *((Window *) propRet);
    XFree(propRet);

    // Vemos si es el escritorio (para no moverla)
    if(XGetWindowProperty(QX11Info::display(), this->window,
            XInternAtom(QX11Info::display(), "_NET_WM_WINDOW_TYPE", false),
            0, 100, false, XA_ATOM, &atomRet, &size, &numItems,
            &bytesAfterReturn, &propRet) == Success) {
        Atom* types = (Atom*)propRet;
        Atom type = types[0]; // Solo miramos el primer tipo especificado

        if(type == XInternAtom(QX11Info::display(),
                "_NET_WM_WINDOW_TYPE_DESKTOP", false)) {
            this->window = 0;
        }
        XFree(propRet);
    }
}

void MoveWindow::executeUpdate(const QHash<QString, QVariant>& attrs) {
    if(this->window == 0)
        return;

    if(!attrs.contains(GEIS_GESTURE_ATTRIBUTE_DELTA_X)
            || !attrs.contains(GEIS_GESTURE_ATTRIBUTE_DELTA_Y))
        return;

    QCursor::setPos(QCursor::pos().x()
            + attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat(),
            QCursor::pos().y()
            + attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat());

    XWindowAttributes xwa;
    XGetWindowAttributes(QX11Info::display(), window, &xwa);

    XMoveWindow(QX11Info::display(), this->window,
                QCursor::pos().x() - xwa.width/2,
                QCursor::pos().y() - xwa.height/2);

    XFlush(QX11Info::display());
}

void MoveWindow::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {}
