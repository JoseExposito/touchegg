/**
 * @file /src/touchegg/actions/implementation/RunCommand.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  RunCommand
 * @author José Expósito
 */
#include "RunCommand.h"


// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

RunCommand::RunCommand(const QString& settings) : Action(settings) {
    this->command = "";

    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "COMMAND")
        this->command = strl.at(1);
    else
        qWarning() << "Error reading RUN_COMMAND settings";
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void RunCommand::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void RunCommand::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void RunCommand::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {
    if(this->command != "") {
        QProcess* myProcess = new QProcess();
        myProcess->startDetached(this->command);
    }
}
