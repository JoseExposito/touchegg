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

    // Ponemos los iconos del tema
    QListWidgetItem* aux = this->ui->menuList->item(4);
    QPixmap pixmap(QIcon::fromTheme("configure").pixmap(35, 50));
    aux->setIcon(QIcon(pixmap));
    this->ui->applyButton->setIcon(QIcon::fromTheme("dialog-ok-apply"));

    // creamos los distintos paneles con los widgeds de configuración
    this->tapTab        = new TapTab;
    this->dragTab       = new DragTab;
    this->pinchTab      = new PinchTab;
    this->tapAndHoldTab = new TapAndHoldTab;
    this->generalSettingsTab = new GeneralSettingsTab;

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(this->ui->menuList, 0, 0, 2, 1);

    layout->addWidget(this->tapTab, 0, 1, 1, 1);
    layout->addWidget(this->dragTab, 0, 1, 1, 1);
    layout->addWidget(this->pinchTab, 0, 1, 1, 1);
    layout->addWidget(this->tapAndHoldTab, 0, 1, 1, 1);
    layout->addWidget(this->generalSettingsTab, 0, 1, 1, 1);

    layout->addWidget(this->ui->buttonsFrame, 1, 1, 1, 1);
    this->ui->centralwidget->setLayout(layout);

    // Dejamos visible por defecto el de Tap
    //this->tapTab->setVisible(false);
    this->dragTab->setVisible(false);
    this->pinchTab->setVisible(false);
    this->tapAndHoldTab->setVisible(false);
    this->generalSettingsTab->setVisible(false);
}

MainWindow::~MainWindow() {
    delete this->ui;
    delete this->tapTab;
    delete this->dragTab;
    delete this->pinchTab;
    delete this->tapAndHoldTab;
}


// ************************************************************************** //
// **********                     PRIVATE SLOTS                    ********** //
// ************************************************************************** //

void MainWindow::on_applyButton_clicked() {
    GuiController* guiController = GuiController::getInstance();
    guiController->execute(COMMIT_DATA, NULL);
}


// ************************************************************************** //
// **********                  PROTECCTED METHODS                  ********** //
// ************************************************************************** //

void MainWindow::closeEvent(QCloseEvent* /*event*/) {
    GuiController* guiController = GuiController::getInstance();
    guiController->execute(COMMIT_DATA, NULL);
}


void MainWindow::on_menuList_clicked(QModelIndex index) {
    switch(index.row()) {
    case 0:
        this->tapTab->setVisible(true);
        this->dragTab->setVisible(false);
        this->pinchTab->setVisible(false);
        this->tapAndHoldTab->setVisible(false);
        this->generalSettingsTab->setVisible(false);
        break;
    case 1:
        this->tapTab->setVisible(false);
        this->dragTab->setVisible(true);
        this->pinchTab->setVisible(false);
        this->tapAndHoldTab->setVisible(false);
        this->generalSettingsTab->setVisible(false);
        break;
    case 2:
        this->tapTab->setVisible(false);
        this->dragTab->setVisible(false);
        this->pinchTab->setVisible(true);
        this->tapAndHoldTab->setVisible(false);
        this->generalSettingsTab->setVisible(false);
        break;
    case 3:
        this->tapTab->setVisible(false);
        this->dragTab->setVisible(false);
        this->pinchTab->setVisible(false);
        this->tapAndHoldTab->setVisible(true);
        this->generalSettingsTab->setVisible(false);
        break;
    case 4:
        this->tapTab->setVisible(false);
        this->dragTab->setVisible(false);
        this->pinchTab->setVisible(false);
        this->tapAndHoldTab->setVisible(false);
        this->generalSettingsTab->setVisible(true);
        break;
    }
}
