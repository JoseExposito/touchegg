/**
 * @file /src/touchegg/actions/implementations/MoveWindow.cpp
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

MoveWindow::MoveWindow(const QString& settings) : Action(settings) {
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
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void MoveWindow::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void MoveWindow::executeUpdate(const QHash<QString, QVariant>& attrs) {
    if(!attrs.contains("delta x") || !attrs.contains("delta y"))
        return;

    QCursor::setPos(QCursor::pos().x() + attrs.value("delta x").toFloat(),
            QCursor::pos().y() + attrs.value("delta y").toFloat());

    XWindowAttributes xwa;
    XGetWindowAttributes(QX11Info::display(), window, &xwa);

    XMoveWindow(QX11Info::display(), this->window,
                QCursor::pos().x() - xwa.width/2,
                QCursor::pos().y() - xwa.height/2);

    XFlush(QX11Info::display());
}

void MoveWindow::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {}
