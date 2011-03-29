/**
 * @file /src/touchegg/actions/implementation/HorizontalScroll.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  HorizontalScroll
 * @author José Expósito
 */
#include "HorizontalScroll.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

HorizontalScroll::HorizontalScroll(const QString& settings) : Action(settings) {
    this->leftScrollSpace   = 0;
    this->rightScrollSpace = 0;
    this->speed           = 30;

    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "SPEED") {
        bool ok;
        int configSpeed = QString(strl.at(1)).toInt(&ok);
        if(ok && configSpeed >= 1 && configSpeed <= 10)
            this->speed = 40 - 2*configSpeed;
        else
            qWarning() << "Error reading HORIZONTAL_SCROLL settings, using " <<
                    "the default settings";
    } else
        qWarning() << "Error reading HORIZONTAL_SCROLL settings, using " <<
                "the default settings";
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void HorizontalScroll::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void HorizontalScroll::executeUpdate(const QHash<QString, QVariant>& attrs) {
    float deltaX = attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat();

    if(deltaX > 0) {
        this->rightScrollSpace += (int)deltaX;

        while(this->rightScrollSpace >= this->speed) {
            this->rightScrollSpace -= this->speed;

            XTestFakeButtonEvent(QX11Info::display(), 7, true, 0);
            XTestFakeButtonEvent(QX11Info::display(), 7, false, 0);
            XFlush(QX11Info::display());
        }

    } else {
        this->leftScrollSpace -= (int)deltaX;

        while(this->leftScrollSpace >= this->speed) {
            this->leftScrollSpace -= this->speed;

            XTestFakeButtonEvent(QX11Info::display(), 6, true, 0);
            XTestFakeButtonEvent(QX11Info::display(), 6, false, 0);
            XFlush(QX11Info::display());
        }
    }
}

void HorizontalScroll::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {}
