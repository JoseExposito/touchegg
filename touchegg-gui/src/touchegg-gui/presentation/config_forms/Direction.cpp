/**
 * @file /src/touchegg-gui/presentation/config_forms/Direction.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  Direction
 * @author José Expósito
 */
#include "Direction.h"
#include "ui_Direction.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

Direction::Direction()
        : ui(new Ui::Direction) {
    ui->setupUi(this);

    this->ui->comboBox->addItem(tr("Next"), "NEXT");
    this->ui->comboBox->addItem(tr("Previous"), "PREVIOUS");

    connect(this->ui->buttonBox, SIGNAL(accepted()),
            this, SIGNAL(configChanged()));
    connect(this->ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(hide()));
    connect(this->ui->buttonBox, SIGNAL(rejected()),
            this, SLOT(hide()));
}

Direction::~Direction() {
    delete ui;
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QString Direction::getSettings() const {
    int index = this->ui->comboBox->currentIndex();
    return this->ui->comboBox->itemData(index).toString();
}

void Direction::setSettings(const QString& settings) {
    int index = this->ui->comboBox->findData(settings);
    if(index == -1)
        index = 0;
    this->ui->comboBox->setCurrentIndex(index);
}
