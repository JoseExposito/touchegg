/**
 * @file /src/touchegg-gui/presentation/config_forms/ChangeDesktopConfig.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ChangeDesktopConfig
 * @author José Expósito
 */
#include "ChangeDesktopConfig.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ChangeDesktopConfig::ChangeDesktopConfig() {
    QLabel* direction = new QLabel("Direction");
    this->leftRight = new QComboBox;
    this->leftRight->addItem("LEFT");
    this->leftRight->addItem("RIGHT");

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(direction);
    layout->addWidget(this->leftRight);
    this->setLayout(layout);

    connect(this->leftRight, SIGNAL(currentIndexChanged(int)),
            this, SIGNAL(configChanged()));
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QString ChangeDesktopConfig::getSettings() const {
    return "DIRECTION=" + this->leftRight->currentText();
}

void ChangeDesktopConfig::setSettings(const QString& settings) {
    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "DIRECTION") {
        QString configDir = strl.at(1);
        if(configDir == "LEFT")
            this->leftRight->setCurrentIndex(0);
        else if(configDir == "RIGHT")
            this->leftRight->setCurrentIndex(1);
    } else {
        this->leftRight->setCurrentIndex(1);
    }
}
