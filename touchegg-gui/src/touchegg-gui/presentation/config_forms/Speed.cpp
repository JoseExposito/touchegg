/**
 * @file /src/touchegg-gui/presentation/config_forms/Speed.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  Speed
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "Speed.h"
#include "ui_Speed.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

Speed::Speed()
        : ui(new Ui::Speed) {
    ui->setupUi(this);

    connect(this->ui->buttonBox, SIGNAL(accepted()),
            this, SIGNAL(configChanged()));
    connect(this->ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(hide()));
    connect(this->ui->buttonBox, SIGNAL(rejected()),
            this, SLOT(hide()));
}

Speed::~Speed() {
    delete ui;
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QString Speed::getSettings() const {
    return "SPEED=" + QString::number(this->ui->horizontalSlider->value());
}

void Speed::setSettings(const QString& settings) {
    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "SPEED") {
        bool ok;
        int configSpeed = QString(strl.at(1)).toInt(&ok);
        if(ok && configSpeed >= 1 && configSpeed <= 10)
            this->ui->horizontalSlider->setValue(configSpeed);
    }
}
