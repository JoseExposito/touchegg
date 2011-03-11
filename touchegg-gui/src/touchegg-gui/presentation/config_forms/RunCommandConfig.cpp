/**
 * @file /src/touchegg-gui/presentation/config_forms/RunCommandConfig.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  RunCommandConfig
 * @author José Expósito
 */
#include "RunCommandConfig.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

RunCommandConfig::RunCommandConfig() {
    QLabel* commandLabel = new QLabel("Command");
    this->command = new QLineEdit;

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(commandLabel);
    layout->addWidget(this->command);
    this->setLayout(layout);

    connect(this->command, SIGNAL(editingFinished()),
            this, SIGNAL(configChanged()));
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QString RunCommandConfig::getSettings() const {
    return "COMMAND=" + this->command->text();
}

void RunCommandConfig::setSettings(const QString& settings) {
    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "COMMAND")
        this->command->setText(strl.at(1));
    else
        this->command->setText("");
}
