/**
 * @file /src/touchegg-gui/presentation/widgets/GestureConfigWidget.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureConfigWidget
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "GestureConfigWidget.h"
#include "ui_GestureConfigWidget.h"


// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

GestureConfigWidget::GestureConfigWidget(const QString& app,
        const QString& gesture, const QString& action, const QString& settings,
        QWidget* parent)
        : QFrame(parent),
          ui(new Ui::GestureConfigWidget),
          app(app),
          configForm(NULL),
          gesture(gesture) {
    ui->setupUi(this);

    // Ponemos los iconos del tema
    QIcon generalSettingsIcon = QIcon::hasThemeIcon("configure")
            ? QIcon::fromTheme("configure")
            : QIcon::fromTheme("document-properties");
    this->ui->configBtn->setIcon(generalSettingsIcon);

    // Cargamos el contenido de los combo-box
    this->loadAllGestures();
    this->loadAllActions();

    // Si hay configuración por defecto la cargamos
    if(gesture != "") {
        int index = this->ui->gestureCombo->findData(gesture);
        this->ui->gestureCombo->setCurrentIndex(index);
    }

    if(action != "") {
        int index = this->ui->actionCombo->findData(action);
        this->ui->actionCombo->setCurrentIndex(index);
    }

    // Si corresponde añadimos un formulario para configurar la acción
    ConfigFormFactory* cff = ConfigFormFactory::getInstance();
    this->configForm = cff->createConfigForm(action);
    this->ui->configBtn->setEnabled(this->configForm != NULL);
    if(settings != "" && this->configForm != NULL)
        this->configForm->setSettings(settings);

    // Conectamos signals y slots
    connect(this->ui->gestureCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(gestureChanged(int)));
    connect(this->ui->actionCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(actionChanged(int)));
    if(this->configForm != NULL)
        connect(this->configForm, SIGNAL(configChanged()),
                this, SLOT(configChanged()));
}

GestureConfigWidget::~GestureConfigWidget() {
    delete ui;
    if(this->configForm != NULL)
        delete this->configForm;
}


// ************************************************************************** //
// **********                   PRIVATE METHODS                    ********** //
// ************************************************************************** //

void GestureConfigWidget::loadAllGestures() {
    this->ui->gestureCombo->addItem(tr("Select a gesture"), "");

    this->ui->gestureCombo->addItem(tr("Tap:"), "");
    this->ui->gestureCombo->addItem(tr("    Tap with 2 fingers"), "TWO_FINGERS_TAP");
    this->ui->gestureCombo->addItem(tr("    Tap with 3 fingers"), "THREE_FINGERS_TAP");
    this->ui->gestureCombo->addItem(tr("    Tap with 4 fingers"), "FOUR_FINGERS_TAP");
    this->ui->gestureCombo->addItem(tr("    Tap with 5 fingers"), "FIVE_FINGERS_TAP");

    this->ui->gestureCombo->addItem(tr("Pinch:"), "");
    this->ui->gestureCombo->addItem(tr("    Pinch with 2 fingers"), "TWO_FINGERS_PINCH");
    this->ui->gestureCombo->addItem(tr("    Pinch with 3 fingers"), "THREE_FINGERS_PINCH");
    this->ui->gestureCombo->addItem(tr("    Pinch with 4 fingers"), "FOUR_FINGERS_PINCH");
    this->ui->gestureCombo->addItem(tr("    Pinch with 5 fingers"), "FIVE_FINGERS_PINCH");

    this->ui->gestureCombo->addItem(tr("Drag with 2 fingers:"), "");
    this->ui->gestureCombo->addItem(tr("    Drag with 2 fingers to up"), "TWO_FINGERS_DRAG_UP");
    this->ui->gestureCombo->addItem(tr("    Drag with 2 fingers to down"), "TWO_FINGERS_DRAG_DOWN");
    this->ui->gestureCombo->addItem(tr("    Drag with 2 fingers to the left"), "TWO_FINGERS_DRAG_LEFT");
    this->ui->gestureCombo->addItem(tr("    Drag with 2 fingers to the right"), "TWO_FINGERS_DRAG_RIGHT");

    this->ui->gestureCombo->addItem(tr("Drag with 3 fingers:"), "");
    this->ui->gestureCombo->addItem(tr("    Drag with 3 fingers to up"), "THREE_FINGERS_DRAG_UP");
    this->ui->gestureCombo->addItem(tr("    Drag with 3 fingers to down"), "THREE_FINGERS_DRAG_DOWN");
    this->ui->gestureCombo->addItem(tr("    Drag with 3 fingers to the left"), "THREE_FINGERS_DRAG_LEFT");
    this->ui->gestureCombo->addItem(tr("    Drag with 3 fingers to the right"), "THREE_FINGERS_DRAG_RIGHT");

    this->ui->gestureCombo->addItem(tr("Drag with 4 fingers:"), "");
    this->ui->gestureCombo->addItem(tr("    Drag with 4 fingers to up"), "FOUR_FINGERS_DRAG_UP");
    this->ui->gestureCombo->addItem(tr("    Drag with 4 fingers to down"), "FOUR_FINGERS_DRAG_DOWN");
    this->ui->gestureCombo->addItem(tr("    Drag with 4 fingers to the left"), "FOUR_FINGERS_DRAG_LEFT");
    this->ui->gestureCombo->addItem(tr("    Drag with 4 fingers to the right"), "FOUR_FINGERS_DRAG_RIGHT");

    this->ui->gestureCombo->addItem(tr("Drag with 5 fingers:"), "");
    this->ui->gestureCombo->addItem(tr("    Drag with 5 fingers to up"), "FIVE_FINGERS_DRAG_UP");
    this->ui->gestureCombo->addItem(tr("    Drag with 5 fingers to down"), "FIVE_FINGERS_DRAG_DOWN");
    this->ui->gestureCombo->addItem(tr("    Drag with 5 fingers to the left"), "FIVE_FINGERS_DRAG_LEFT");
    this->ui->gestureCombo->addItem(tr("    Drag with 5 fingers to the right"), "FIVE_FINGERS_DRAG_RIGHT");

    this->ui->gestureCombo->addItem(tr("Tap & Hold:"), "");
    this->ui->gestureCombo->addItem(tr("    Tap & Hold with 2 fingers"), "TWO_FINGERS_TAP_AND_HOLD");
    this->ui->gestureCombo->addItem(tr("    Tap & Hold with 3 fingers"), "THREE_FINGERS_TAP_AND_HOLD");
    this->ui->gestureCombo->addItem(tr("    Tap & Hold with 4 fingers"), "FOUR_FINGERS_TAP_AND_HOLD");
    this->ui->gestureCombo->addItem(tr("    Tap & Hold with 5 fingers"), "FIVE_FINGERS_TAP_AND_HOLD");
}

void GestureConfigWidget::loadAllActions() {
    this->ui->actionCombo->addItem(tr("Without an action"), "NO_ACTION");
    this->ui->actionCombo->addItem(tr("Simulate mouse clicks"), "MOUSE_CLICK");
    this->ui->actionCombo->addItem(tr("Vertical scroll"), "VERTICAL_SCROLL");
    this->ui->actionCombo->addItem(tr("Horizontal scroll"), "HORIZONTAL_SCROLL");
    this->ui->actionCombo->addItem(tr("Simulate keyboard shortcuts"), "SEND_KEYS");
    this->ui->actionCombo->addItem(tr("Execute a command"), "RUN_COMMAND");
    this->ui->actionCombo->addItem(tr("Minimize a window"), "MINIMIZE_WINDOW");
    this->ui->actionCombo->addItem(tr("Maximize or restore a window"), "MAXIMIZE_RESTORE_WINDOW");
    this->ui->actionCombo->addItem(tr("Resize a window"), "RESIZE_WINDOW");
    this->ui->actionCombo->addItem(tr("Move a window"), "MOVE_WINDOW");
    this->ui->actionCombo->addItem(tr("Close a window"), "CLOSE_WINDOW");
    this->ui->actionCombo->addItem(tr("Show the desktop"), "SHOW_DESKTOP");
    this->ui->actionCombo->addItem(tr("Change the desktop"), "CHANGE_DESKTOP");
    this->ui->actionCombo->addItem(tr("Change the desktop viewport"), "CHANGE_VIEWPORT");
    this->ui->actionCombo->addItem(tr("Simulate drag&drop"), "DRAG_AND_DROP");
}



// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void GestureConfigWidget::deleteConfig() {
    Facade f;
    if(this->gesture != "") {
        f.toucheggRemove(this->gesture + "." + this->app + ".action");
        f.toucheggRemove(this->gesture + "." + this->app + ".settings");
    }
}

// ************************************************************************** //
// **********                     PRIVATE SLOTS                    ********** //
// ************************************************************************** //

void GestureConfigWidget::gestureChanged(int /*index*/) {
    Facade f;

    // Si se cambia el gesto borramos los datos guardados anteriormente porque
    // son inválidos. Si no se borraran se empezarían a duplicar datos.
    if(this->gesture != "") {
        f.toucheggRemove(this->gesture + "." + this->app + ".action");
        f.toucheggRemove(this->gesture + "." + this->app + ".settings");
    }

    this->gesture = this->ui->gestureCombo->itemData(
            this->ui->gestureCombo->currentIndex()).toString();

    // Guardamos los cambios realizados
    if(this->gesture != "") {
        QString action = this->ui->actionCombo->itemData(
                this->ui->actionCombo->currentIndex()).toString();
        f.toucheggUpdate(this->gesture + "." + this->app + ".action", action);

        if(this->configForm != NULL) {
            QString settings = this->configForm->getSettings();
            f.toucheggUpdate(this->gesture+"."+this->app+".settings",settings);
        }
    }
}

void GestureConfigWidget::actionChanged(int /*index*/) {
    Facade f;

    // Si se cambia el gesto borramos los datos guardados anteriormente porque
    // son inválidos. Si no se borraran se empezarían a duplicar datos.
    if(this->gesture != "") {
        f.toucheggRemove(this->gesture + "." + this->app + ".action");
        f.toucheggRemove(this->gesture + "." + this->app + ".settings");
    }

    // Si la acción anterior usaba un formulario de configuración lo borramos
    if(this->configForm != NULL)
        delete this->configForm;

    // Si corresponde añadimos un formulario para configurar la acción
    QString action = this->ui->actionCombo->itemData(
            this->ui->actionCombo->currentIndex()).toString();
    ConfigFormFactory* cff = ConfigFormFactory::getInstance();
    this->configForm = cff->createConfigForm(action);
    this->ui->configBtn->setEnabled(this->configForm != NULL);
    if(this->configForm != NULL)
        connect(this->configForm, SIGNAL(configChanged()),
                this, SLOT(configChanged()));

    // Guardamos los cambios realizados
    if(this->gesture != "") {
        QString action = this->ui->actionCombo->itemData(
                this->ui->actionCombo->currentIndex()).toString();
        f.toucheggUpdate(this->gesture + "." + this->app + ".action", action);

        if(this->configForm != NULL) {
            QString settings = this->configForm->getSettings();
            f.toucheggUpdate(this->gesture+"."+this->app+".settings",settings);
        }
    }
}

void GestureConfigWidget::on_configBtn_clicked() {
    if(this->configForm != NULL) {
        this->configForm->setVisible(true);
    }
}

//------------------------------------------------------------------------------

void GestureConfigWidget::configChanged() const {
    // Guardamos los cambios realizados
    Facade f;
    if(this->gesture != "") {
        QString action = this->ui->actionCombo->itemData(
                this->ui->actionCombo->currentIndex()).toString();
        f.toucheggUpdate(this->gesture + "." + this->app + ".action", action);

        if(this->configForm != NULL) {
            QString settings = this->configForm->getSettings();
            f.toucheggUpdate(this->gesture+"."+this->app+".settings",settings);
        }
    }
}
