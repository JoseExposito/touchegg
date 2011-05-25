/**
 * @file /src/touchegg-gui/presentation/config_forms/RunCommand.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  RunCommand
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "RunCommand.h"
#include "ui_RunCommand.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

RunCommand::RunCommand()
        : ui(new Ui::RunCommand) {
    ui->setupUi(this);

    connect(this->ui->buttonBox, SIGNAL(accepted()),
            this, SIGNAL(configChanged()));
    connect(this->ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(hide()));
    connect(this->ui->buttonBox, SIGNAL(rejected()),
            this, SLOT(hide()));
}

RunCommand::~RunCommand() {
    delete ui;
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QString RunCommand::getSettings() const {
    return "COMMAND=" + this->ui->lineEdit->text();
}

void RunCommand::setSettings(const QString& settings) {
    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "COMMAND")
        this->ui->lineEdit->setText(strl.at(1));
}
