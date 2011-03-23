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
 * @author José Expósito
 */
#include "DragAndDrop.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

DragAndDrop::DragAndDrop(const QString& settings)
        : Action(settings) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void DragAndDrop::executeStart(const QHash<QString, QVariant>& /*attrs*/) {
    XTestFakeButtonEvent(QX11Info::display(), Button1, true, 0);
}

void DragAndDrop::executeUpdate(const QHash<QString, QVariant>& attrs) {
    if(!attrs.contains("delta x") || !attrs.contains("delta y"))
        return;

    QCursor::setPos(QCursor::pos().x() + attrs.value("delta x").toFloat(),
            QCursor::pos().y() + attrs.value("delta y").toFloat());
}

void DragAndDrop::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {
    XTestFakeButtonEvent(QX11Info::display(), Button1, false, 0);
}
