/**
 * @file /src/touchegg-gui/presentation/main_window/GeneralSettingsTab.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GeneralSettingsTab
 * @author José Expósito
 */
#include "GeneralSettingsTab.h"
#include "ui_GeneralSettingsTab.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

GeneralSettingsTab::GeneralSettingsTab(QWidget *parent)
        : QFrame(parent)
        , ui(new Ui::GeneralSettingsTab) {
    ui->setupUi(this);

    // Cargamos los valores por defecto
    Facade f;
    QString strTime = f.toucheggRead("general_settings.tap_and_hold_time");
    bool ok;
    int time = strTime.toInt(&ok);

    // Si el tap&hold está activado
    if(ok && time > 0) {
        this->ui->checkBox->setChecked(true);
        this->ui->horizontalSlider->setValue(time);
        this->ui->msLabel->setText(strTime + " ms");

    // Si el tap&hold está desactivado o el valor es inválido
    } else {
        this->ui->horizontalSlider->setValue(135);
        this->ui->msLabel->setText("135 ms");
        this->ui->checkBox->setChecked(false);
        this->ui->label->setEnabled(false);
        this->ui->horizontalSlider->setEnabled(false);
        this->ui->msLabel->setEnabled(false);
    }
}

GeneralSettingsTab::~GeneralSettingsTab() {
    delete ui;
}

// ************************************************************************** //
// **********                     PRIVATE SLOTS                    ********** //
// ************************************************************************** //

void GeneralSettingsTab::on_checkBox_clicked(bool checked) {
    Facade f;
    QString value;
    value.setNum(checked ? this->ui->horizontalSlider->value() : 0);
    f.toucheggUpdate("general_settings.tap_and_hold_time", value);
}

void GeneralSettingsTab::on_horizontalSlider_valueChanged(int value) {
    Facade f;
    QString strValue;
    strValue.setNum(this->ui->checkBox ? value : 0);
    f.toucheggUpdate("general_settings.tap_and_hold_time", strValue);

    this->ui->msLabel->setText(strValue + " ms");
}
