/**
 * @file /src/touchegg/actions/implementation/ResizeWindow.cpp
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

void ResizeWindow::executeStart(const QHash<QString, QVariant>& /*attrs*/) {
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

    // Vemos si es el escritorio (para no redimensionarla)
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

void ResizeWindow::executeUpdate(const QHash<QString, QVariant>& attrs) {
    if(this->window == 0)
        return;

    // Ángulo
    if(!attrs.contains(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_X1)
            || !attrs.contains(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_X2)
            || !attrs.contains(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_Y1)
            || !attrs.contains(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_Y2))
        return;

    float co = attrs.value(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_Y2).toFloat()
            - attrs.value(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_Y1).toFloat();
    float cc = attrs.value(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_X2).toFloat()
            - attrs.value(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_X1).toFloat();

    double angle = (int)(atan(co/cc) * 100);

    double incX, incY;
    if(angle > 75) {
        incX = 0;
        incY = 1;
    } else if(angle < 20) {
        incX = 1;
        incY = 0;
    } else {
        incX = cos(angle * (3.14/180));
        incY = sin(angle * (3.14/180));
    }

    // Redimensionamos la ventana
    XWindowAttributes xwa;
    XGetWindowAttributes(QX11Info::display(), this->window, &xwa);
    int inc = (int)attrs.value("radius delta").toFloat()*3;
    XResizeWindow(QX11Info::display(), this->window,
            xwa.width  + inc * incX,
            xwa.height + inc * incY);
    XFlush(QX11Info::display());
}

void ResizeWindow::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {}
