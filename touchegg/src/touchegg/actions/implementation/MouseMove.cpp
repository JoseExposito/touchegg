/**
 * @file /src/touchegg/actions/implementation/MouseMove.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MouseMove
 * @author José Expósito
 */
#include "MouseMove.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MouseMove::MouseMove(const QString& settings)
        : Action(settings) {
    this->speed = 4;

    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "SPEED") {
        bool ok;
        int configSpeed = QString(strl.at(1)).toInt(&ok);
        if(ok && configSpeed >= 1 && configSpeed <= 10)
            this->speed = 11 - configSpeed;
        else
            qWarning() << "Error reading MOUSE_MOVE settings, using the " <<
                    "default settings";
    } else
        qWarning() << "Error reading MOUSE_MOVE settings, using the " <<
                "default settings";
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void MouseMove::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void MouseMove::executeUpdate(const QHash<QString, QVariant>& attrs) {
    if(!attrs.contains(GEIS_GESTURE_ATTRIBUTE_DELTA_X)
            || !attrs.contains(GEIS_GESTURE_ATTRIBUTE_DELTA_Y))
        return;

    if(this->speedCount >= this->speed) {
        XTestFakeRelativeMotionEvent(QX11Info::display(),
                attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() * 5,
                attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() * 5,
                0);
        this->speedCount = 0;
    } else {
        this->speedCount++;
    }
}

void MouseMove::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {}
