/**
 * @file /src/touchegg/actions/implementation/MouseClick.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MouseClick
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "MouseClick.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MouseClick::MouseClick(const QString& settings, Window window)
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

void MouseClick::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void MouseClick::executeFinish(const QHash<QString, QVariant>& /*attrs*/){}

void MouseClick::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {
    XTestFakeButtonEvent(QX11Info::display(), this->button, true, 0);
    XTestFakeButtonEvent(QX11Info::display(), this->button, false, 0);
    XFlush(QX11Info::display());
}
