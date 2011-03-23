/**
 * @file /src/touchegg/actions/implementation/SendKeys.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  SendKeys
 * @author José Expósito
 */
#include "SendKeys.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

SendKeys::SendKeys(const QString& settings) : Action(settings) {
    if(settings.split(":").length() != 2) {
        qWarning() << "Error reading SEND_KEYS settings";
        return;
    }

    QString allHoldDown = settings.split(":").at(0);
    QString allBetween  = settings.split(":").at(1);

    if(allHoldDown.split("=").length() != 2
            || allBetween.split("=").length() != 2) {
        qWarning() << "Error reading SEND_KEYS settings";
        return;
    }

    if(allHoldDown.split("=").at(0) != "HOLD_DOWN"
            || allBetween.split("=").at(0) != "PRESS") {
        qWarning() << "Error reading SEND_KEYS settings";
        return;
    }

    QString holdDownStr      = allHoldDown.split("=").at(1);
    QString betweenStr       = allBetween.split("=").at(1);
    QStringList holdDownList = holdDownStr.split("|");
    QStringList betweenList  = betweenStr.split("|");

    for(int n=0; n<holdDownList.length(); n++) {
        QString keySymStr = holdDownList.at(n);
        if(keySymStr != "") {
            KeySym keySym = XStringToKeysym(keySymStr.toStdString().c_str());
            KeyCode keyCode = XKeysymToKeycode(QX11Info::display(), keySym);
            this->holdDownKeys.append(keyCode);
        }
    }

    for(int n=0; n<betweenList.length(); n++) {
        QString keySymStr = betweenList.at(n);
        if(keySymStr != "") {
            KeySym keySym = XStringToKeysym(keySymStr.toStdString().c_str());
            KeyCode keyCode = XKeysymToKeycode(QX11Info::display(), keySym);
            this->pressBetweenKeys.append(keyCode);
        }
    }
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void SendKeys::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void SendKeys::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void SendKeys::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {

    for(int n=0; n<this->holdDownKeys.length(); n++) {
        XTestFakeKeyEvent(QX11Info::display(),this->holdDownKeys.at(n),true,0);
    }

    for(int n=0; n<this->pressBetweenKeys.length(); n++) {
        XTestFakeKeyEvent(QX11Info::display(), this->pressBetweenKeys.at(n),
                true, 0);
        XTestFakeKeyEvent(QX11Info::display(), this->pressBetweenKeys.at(n),
                false, 0);
    }

    for(int n=0; n<this->holdDownKeys.length(); n++) {
        XTestFakeKeyEvent(QX11Info::display(),this->holdDownKeys.at(n),false,0);
    }
}
