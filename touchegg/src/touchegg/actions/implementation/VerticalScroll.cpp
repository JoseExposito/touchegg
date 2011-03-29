/**
 * @file /src/touchegg/actions/implementation/VerticalScroll.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  VerticalScroll
 * @author José Expósito
 */
#include "VerticalScroll.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

VerticalScroll::VerticalScroll(const QString& settings) : Action(settings) {
    this->upScrollSpace   = 0;
    this->downScrollSpace = 0;
    this->speed           = 30;

    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "SPEED") {
        bool ok;
        int configSpeed = QString(strl.at(1)).toInt(&ok);
        if(ok && configSpeed >= 1 && configSpeed <= 10)
            this->speed = 40 - 2*configSpeed;
        else
            qWarning() << "Error reading VERTICAL_SCROLL settings, using " <<
                    "the default settings";
    } else
        qWarning() << "Error reading VERTICAL_SCROLL settings, using " <<
                "the default settings";
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void VerticalScroll::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void VerticalScroll::executeUpdate(const QHash<QString, QVariant>& attrs) {
    float deltaY = attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat();

    if(deltaY > 0) {
        this->downScrollSpace += (int)deltaY;

        while(this->downScrollSpace >= this->speed) {
            this->downScrollSpace -= this->speed;

            XTestFakeButtonEvent(QX11Info::display(), Button5, true, 0);
            XTestFakeButtonEvent(QX11Info::display(), Button5, false, 0);
            XFlush(QX11Info::display());
        }

    } else {
        this->upScrollSpace -= (int)deltaY;

        while(this->upScrollSpace >= this->speed) {
            this->upScrollSpace -= this->speed;

            XTestFakeButtonEvent(QX11Info::display(), Button4, true, 0);
            XTestFakeButtonEvent(QX11Info::display(), Button4, false, 0);
            XFlush(QX11Info::display());
        }
    }
}

void VerticalScroll::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {}
