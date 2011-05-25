/**
 * @file /src/touchegg/actions/implementation/Scroll.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  Scroll
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "Scroll.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

Scroll::Scroll(const QString& settings, Window window)
        : Action(settings, window) {
    this->upScrollSpace    = 0;
    this->downScrollSpace  = 0;
    this->rightScrollSpace = 0;
    this->leftScrollSpace  = 0;
    this->verticalSpeed    = 30;
    this->horizontalSpeed  = 30;
    this->buttonUp         = 4;
    this->buttonDown       = 5;
    this->buttonLeft       = 6;
    this->buttonRight      = 7;

    bool error = false;

    QStringList mainStr = settings.split(":");
    if(mainStr.length() != 2)
        error = true;

    // Speed
    QStringList mainStrSpeed = ((QString)mainStr.at(0)).split("=");
    if(!error && mainStrSpeed.length() == 2 && mainStrSpeed.at(0) == "SPEED") {
        bool ok;
        int configSpeed = QString(mainStrSpeed.at(1)).toInt(&ok);
        if(ok && configSpeed >= 1 && configSpeed <= 10) {
            this->verticalSpeed   = 40 - 2*configSpeed;
            this->horizontalSpeed = 40 - 2*configSpeed;
        } else {
            error = true;
        }
    } else {
        error = true;
    }

    // Inverted
    QStringList mainStrInv = mainStr.at(1).split("=");
    if(!error && mainStrInv.length() == 2 && mainStrInv.at(0) == "INVERTED") {
        if(mainStrInv.at(1) == "true") {
            this->buttonUp         = 5;
            this->buttonDown       = 4;
            this->buttonLeft       = 7;
            this->buttonRight      = 6;
        }
    } else {
        error = true;
    }


    if(error) {
        qWarning() << "Error reading SCROLL settings, using"
                   << "the default settings";
    }
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void Scroll::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void Scroll::executeUpdate(const QHash<QString, QVariant>& attrs) {
    float deltaX = attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat();
    float deltaY = attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat();

    // Vertical scroll
    if(deltaY > 0) {
        this->downScrollSpace += (int)deltaY;

        while(this->downScrollSpace >= this->verticalSpeed) {
            this->downScrollSpace -= this->verticalSpeed;

            XTestFakeButtonEvent(QX11Info::display(), this->buttonDown,true, 0);
            XTestFakeButtonEvent(QX11Info::display(), this->buttonDown,false,0);
            XFlush(QX11Info::display());
        }

    } else {
        this->upScrollSpace -= (int)deltaY;

        while(this->upScrollSpace >= this->verticalSpeed) {
            this->upScrollSpace -= this->verticalSpeed;

            XTestFakeButtonEvent(QX11Info::display(), this->buttonUp, true, 0);
            XTestFakeButtonEvent(QX11Info::display(), this->buttonUp, false, 0);
            XFlush(QX11Info::display());
        }
    }

    // Horizontal scroll
    if(deltaX > 0) {
        this->rightScrollSpace += (int)deltaX;

        while(this->rightScrollSpace >= this->horizontalSpeed) {
            this->rightScrollSpace -= this->horizontalSpeed;

            XTestFakeButtonEvent(QX11Info::display(),this->buttonRight,true,0);
            XTestFakeButtonEvent(QX11Info::display(),this->buttonRight,false,0);
            XFlush(QX11Info::display());
        }

    } else {
        this->leftScrollSpace -= (int)deltaX;

        while(this->leftScrollSpace >= this->horizontalSpeed) {
            this->leftScrollSpace -= this->horizontalSpeed;

            XTestFakeButtonEvent(QX11Info::display(), this->buttonLeft,true, 0);
            XTestFakeButtonEvent(QX11Info::display(), this->buttonLeft,false,0);
            XFlush(QX11Info::display());
        }
    }
}

void Scroll::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {}
