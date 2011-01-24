/**
 * @file /src/touchegg/actions/ResizeWindow.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ResizeWindow
 * @author José Expósito
 */
#include "ResizeWindow.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ResizeWindow::ResizeWindow(const QString& settings)
        : Action(settings) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void ResizeWindow::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void ResizeWindow::executeUpdate(const QHash<QString, QVariant>& attrs) {
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

    // Redimensionamos la ventana
    XWindowAttributes xwa;
    XGetWindowAttributes(QX11Info::display(), window, &xwa);
    int inc = (int)attrs.value("radius delta").toFloat()*2;
    XResizeWindow(QX11Info::display(), window, xwa.width+inc, xwa.height+inc);
    XFlush(QX11Info::display());
}

void ResizeWindow::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {}
