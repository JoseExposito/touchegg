/**
 * @file /src/touchegg-gui/presentation/config_forms/MouseWhellConfig.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MouseWhellConfig
 * @author José Expósito
 */
#include "MouseWhellConfig.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MouseWhellConfig::MouseWhellConfig() {
    QLabel* speed = new QLabel("Speed");
    this->slider  = new QSlider(Qt::Horizontal);
    this->slider->setMinimum(1);
    this->slider->setMaximum(10);
    this->slider->setSingleStep(1);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(speed);
    layout->addWidget(this->slider);
    this->setLayout(layout);

    connect(this->slider, SIGNAL(valueChanged(int)),
            this, SIGNAL(configChanged()));
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QString MouseWhellConfig::getSettings() const {
    QString speed;
    speed.setNum(this->slider->value());
    return "SPEED=" + speed;
}

void MouseWhellConfig::setSettings(const QString& settings) {
    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "SPEED") {
        bool ok;
        int configSpeed = QString(strl.at(1)).toInt(&ok);
        if(ok && configSpeed >= 1 && configSpeed <= 10)
            this->slider->setValue(11 - configSpeed);
        else
            this->slider->setValue(4);
    } else {
        this->slider->setValue(4);
    }
}
