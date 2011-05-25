/**
 * @file /src/touchegg-gui/presentation/config_forms/SendKeys.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  SendKeys
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "SendKeys.h"
#include "ui_SendKeys.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

SendKeys::SendKeys()
        : ui(new Ui::SendKeys) {
    ui->setupUi(this);

    connect(this->ui->buttonBox, SIGNAL(accepted()),
            this, SIGNAL(configChanged()));
    connect(this->ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(hide()));
    connect(this->ui->buttonBox, SIGNAL(rejected()),
            this, SLOT(hide()));
}

SendKeys::~SendKeys() {
    delete ui;
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QString SendKeys::getSettings() const {
    return "HOLD_DOWN=" + this->ui->holdDownText->text() + ":"
            + "PRESS=" + this->ui->pressText->text();
}

void SendKeys::setSettings(const QString& settings) {
    QStringList parts = settings.split(":");
    if(parts.length() == 2) {
        QStringList holdDown = parts.at(0).split("=");
        QStringList press    = parts.at(1).split("=");

        if(holdDown.length() == 2 && press.length() == 2) {
            this->ui->holdDownText->setText(holdDown.at(1));
            this->ui->pressText->setText(press.at(1));
        } else {
            this->ui->holdDownText->setText("");
            this->ui->pressText->setText("");
        }
    }
}
