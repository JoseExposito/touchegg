/**
 * @file /src/touchegg-gui/presentation/config_forms/MouseButtons.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MouseButtons
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "MouseButtons.h"
#include "ui_MouseButtons.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MouseButtons::MouseButtons()
        : ui(new Ui::MouseButtons) {
    ui->setupUi(this);

    this->ui->comboBox->addItem(tr("Left button"), "BUTTON=1");
    this->ui->comboBox->addItem(tr("Right button"), "BUTTON=3");
    this->ui->comboBox->addItem(tr("Middle button"), "BUTTON=2");
    this->ui->comboBox->addItem(tr("Go backward"), "BUTTON=8");
    this->ui->comboBox->addItem(tr("Go forward"), "BUTTON=9");

    connect(this->ui->buttonBox, SIGNAL(accepted()),
            this, SIGNAL(configChanged()));
    connect(this->ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(hide()));
    connect(this->ui->buttonBox, SIGNAL(rejected()),
            this, SLOT(hide()));
}

MouseButtons::~MouseButtons() {
    delete ui;
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QString MouseButtons::getSettings() const {
    int index = this->ui->comboBox->currentIndex();
    return this->ui->comboBox->itemData(index).toString();
}

void MouseButtons::setSettings(const QString& settings) {
    int index = this->ui->comboBox->findData(settings);
    if(index == -1)
        index = 0;
    this->ui->comboBox->setCurrentIndex(index);
}
