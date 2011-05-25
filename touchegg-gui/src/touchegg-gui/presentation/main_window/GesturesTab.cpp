/**
 * @file /src/touchegg-gui/presentation/main_window/GesturesTab.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GesturesTab
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "GesturesTab.h"
#include "ui_GesturesTab.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

GesturesTab::GesturesTab(QWidget *parent)
        : QFrame(parent)
        , ui(new Ui::GesturesTab) {
    ui->setupUi(this);

    // Ponemos los iconos del tema
    QIcon addIcon = QIcon::fromTheme("list-add");
    QIcon removeIcon = QIcon::fromTheme("list-remove");

    this->ui->addAppBtn->setIcon(addIcon);
    this->ui->removeAppBtn->setIcon(removeIcon);
    this->ui->addGestureBtn->setIcon(addIcon);
    this->ui->removeGestureBtn->setIcon(removeIcon);

    // Inicializamos la lista de aplicaciones con todas las usadas por Touchégg
    Facade f;
    this->ui->appCombo->addItems(f.getToucheggUsedApplications());
    // Al hacer esto se llama automáticamente a on_appCombo_currentIndexChanged
    // que añade todos los gestos a la lista
}

GesturesTab::~GesturesTab() {
    delete ui;
}


// ************************************************************************** //
// **********                   PRIVATE METHODS                    ********** //
// ************************************************************************** //

void GesturesTab::loadConfiguration(const QString& app) {
    Facade f;
    QStringList usedGestures = f.getToucheggUsedGestures(app);
    for(int n=0; n<usedGestures.length(); n++) {
        int index = this->ui->gesturesTable->rowCount();
        this->ui->gesturesTable->insertRow(index);

        QString key = usedGestures.at(n) + "." + app;
        QWidget* w = new GestureConfigWidget(app, usedGestures.at(n),
                f.toucheggRead(key + ".action"),
                f.toucheggRead(key + ".settings"));
        this->ui->gesturesTable->setCellWidget(index, 0, w);
    }
}

void GesturesTab::removeGesture(int row, bool deleteConfig) {
    GestureConfigWidget* w = (GestureConfigWidget*)
            this->ui->gesturesTable->cellWidget(row, 0);
    if(deleteConfig)
        w->deleteConfig();
    this->ui->gesturesTable->removeCellWidget(row, 0);
    delete w;
    this->ui->gesturesTable->removeRow(row);
}


// ************************************************************************** //
// **********                     PRIVATE SLOTS                    ********** //
// ************************************************************************** //

void GesturesTab::on_appCombo_currentIndexChanged(QString app) {
    this->ui->appCombo->setEditable(false);

    for(int n=0; n<this->ui->gesturesTable->rowCount(); n++)
        this->removeGesture(n, false);
    this->loadConfiguration(app);
}

//------------------------------------------------------------------------------

void GesturesTab::on_addGestureBtn_clicked() {
    int index = this->ui->gesturesTable->rowCount();
    this->ui->gesturesTable->insertRow(index);
    QWidget* w = new GestureConfigWidget(this->ui->appCombo->currentText());
    this->ui->gesturesTable->setCellWidget(index, 0, w);

    this->ui->gesturesTable->scrollToBottom();
}

void GesturesTab::on_removeGestureBtn_clicked() {
    int row = this->ui->gesturesTable->currentRow();
    if(row != -1)
        this->removeGesture(row, true);
}

//------------------------------------------------------------------------------

void GesturesTab::on_addAppBtn_clicked() {
    this->ui->appCombo->insertItem(this->ui->appCombo->count(),
            tr("Enter the application name"));
    this->ui->appCombo->setCurrentIndex(this->ui->appCombo->count() - 1);
    this->ui->appCombo->setEditable(true);
    this->ui->appCombo->setFocus();
    this->ui->appCombo->lineEdit()->selectAll();

    connect(this->ui->appCombo->lineEdit(), SIGNAL(editingFinished()),
            this, SLOT(editAppFinished()));
}

void GesturesTab::on_removeAppBtn_clicked() {
    if(this->ui->appCombo->currentText() != "ALL") {
        for(int n=0; n<this->ui->gesturesTable->rowCount(); n++)
            this->removeGesture(n, true);
        this->ui->appCombo->removeItem(this->ui->appCombo->currentIndex());
    }
}

void GesturesTab::editAppFinished() {
    this->ui->appCombo->setEditable(false);
    this->ui->appCombo->removeItem( // Un poco cutre, pero eficaz
        this->ui->appCombo->findText(tr("Enter the application name")));
}
