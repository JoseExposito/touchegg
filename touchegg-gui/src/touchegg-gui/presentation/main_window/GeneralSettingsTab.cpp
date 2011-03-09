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
        : QFrame(parent), ui(new Ui::GeneralSettingsTab) {
    ui->setupUi(this);

    // Cargamos los valores por defecto
    GuiController* guiController = GuiController::getInstance();
    QString property = "tap_and_hold_time";
    GeneralTransfer* gt = (GeneralTransfer*)guiController->execute(
            READ_GENERAL_PROPERTY, &property);
    if(gt->getValue() == "0") {
        this->ui->checkBox->setChecked(false);
        this->ui->label->setEnabled(false);
        this->ui->horizontalSlider->setEnabled(false);
        this->ui->msLabel->setText("");
    } else {
        this->ui->checkBox->setChecked(true);
        this->ui->horizontalSlider->setValue(gt->getValue().toInt());
        this->ui->msLabel->setText(gt->getValue() + " ms");
    }    

    delete gt;
}

GeneralSettingsTab::~GeneralSettingsTab() {
    delete ui;
}

// ************************************************************************** //
// **********                     PRIVATE SLOTS                    ********** //
// ************************************************************************** //

void GeneralSettingsTab::on_checkBox_clicked(bool checked) {
    QString value;
    value.setNum(checked ? this->ui->horizontalSlider->value() : 0, 10);
    GeneralTransfer gt("tap_and_hold_time", value);
    GuiController* guiController = GuiController::getInstance();
    guiController->execute(UPDATE_GENERAL_PROPERTY, &gt);
}

void GeneralSettingsTab::on_horizontalSlider_valueChanged(int /*value*/) {
    QString value;
    bool checked = this->ui->checkBox->isChecked();
    value.setNum(checked ? this->ui->horizontalSlider->value() : 0, 10);
    GeneralTransfer gt("tap_and_hold_time", value);
    GuiController* guiController = GuiController::getInstance();
    guiController->execute(UPDATE_GENERAL_PROPERTY, &gt);

    this->ui->msLabel->setText(value + " ms");
}
