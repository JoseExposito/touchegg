/**
 * @file /src/touchegg/actions/implementation/DragAndDrop.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  DragAndDrop
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "DragAndDrop.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

DragAndDrop::DragAndDrop(const QString& settings, Window window)
        : Action(settings, window) {
    this->button = 1;

    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "BUTTON") {
        bool ok = false;
        int aux = strl.at(1).toInt(&ok);

        if(ok && aux>=1 && aux<=9)
            this->button = aux;
        else
            qWarning() << "Error reading MOUSE_CLICK settings, using " <<
                    "the default settings";
    } else
        qWarning() << "Error reading MOUSE_CLICK settings, using " <<
                "the default settings";
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void DragAndDrop::executeStart(const QHash<QString, QVariant>& /*attrs*/) {
    XTestFakeButtonEvent(QX11Info::display(), this->button, true, 0);
}

void DragAndDrop::executeUpdate(const QHash<QString, QVariant>& attrs) {
    if(!attrs.contains(GEIS_GESTURE_ATTRIBUTE_DELTA_X)
            || !attrs.contains(GEIS_GESTURE_ATTRIBUTE_DELTA_Y))
        return;

    QCursor::setPos(QCursor::pos().x()
            + attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat(),
            QCursor::pos().y()
            + attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat());
}

void DragAndDrop::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {
    XTestFakeButtonEvent(QX11Info::display(), this->button, false, 0);
}
