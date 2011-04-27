/**
 * @file /src/touchegg-gui/presentation/main_window/MainWindow.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MainWindow
 * @author José Expósito
 */
#include "MainWindow.h"
#include "ui_MainWindow.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Ponemos los distintos items del menu
    this->ui->menu->insertRow(0);
    this->ui->menu->insertRow(1);

    QWidget* gesturesItem = new MenuItem(
            QIcon(":/images/gestures-icon.png"), tr("Gestures"), this);

    QIcon generalSettingsIcon = QIcon::hasThemeIcon("configure")
            ? QIcon::fromTheme("configure")
            : QIcon::fromTheme("document-properties");
    QWidget* generalSettingsItem = new MenuItem(
            generalSettingsIcon, tr("General settings"), this);

    this->ui->menu->setCellWidget(0, 0, gesturesItem);
    this->ui->menu->setCellWidget(1, 0, generalSettingsItem);
    this->ui->menu->selectRow(0);

    // Ponemos los iconos del tema
    this->ui->acceptButton->setIcon(QIcon::fromTheme("dialog-ok"));
    this->ui->cancelButton->setIcon(QIcon::fromTheme("dialog-cancel"));
    if(QIcon::hasThemeIcon("dialog-ok-apply"))
        this->ui->applyButton->setIcon(QIcon::fromTheme("dialog-ok-apply"));
    else
        this->ui->applyButton->setIcon(QIcon::fromTheme("dialog-apply"));

    // Creamos los distintos paneles con los widgeds de configuración
    this->gesturesTab = new GesturesTab(this);
    this->generalSettingsTab = new GeneralSettingsTab(this);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(this->ui->menu, 0, 0, 2, 1);
    layout->addWidget(this->ui->buttonsFrame, 1, 1, 1, 1);
    layout->addWidget(this->gesturesTab, 0, 1, 1, 1);
    layout->addWidget(this->generalSettingsTab, 0, 1, 1, 1);
    this->ui->centralwidget->setLayout(layout);

    // Dejamos visible por defecto la primera solapa
    //this->gesturesTab->setVisible(false);
    this->generalSettingsTab->setVisible(false);
}

MainWindow::~MainWindow() {
    delete this->ui;
}


// ************************************************************************** //
// **********                     PRIVATE SLOTS                    ********** //
// ************************************************************************** //

void MainWindow::on_menu_cellClicked(int row, int /*column*/) {
    switch(row) {
    case 0:
        this->gesturesTab->setVisible(true);
        this->generalSettingsTab->setVisible(false);
        break;
    case 1:
        this->gesturesTab->setVisible(false);
        this->generalSettingsTab->setVisible(true);
        break;
    }
}

//------------------------------------------------------------------------------

void MainWindow::on_applyButton_clicked() {
    Facade f;
    f.commitData();
}

void MainWindow::on_acceptButton_clicked() {
    Facade f;
    f.commitData();
    this->close();
}

void MainWindow::on_cancelButton_clicked() {
    Facade f;
    f.rollbackData();
    this->close();
}
