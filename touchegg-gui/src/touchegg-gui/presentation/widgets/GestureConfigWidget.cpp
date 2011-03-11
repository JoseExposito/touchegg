/**
 * @file /src/touchegg-gui/presentation/widgets/GestureConfig.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureConfig
 * @author José Expósito
 */
#include "GestureConfigWidget.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

GestureConfigWidget::GestureConfigWidget(
        GestureTypeEnum::GestureType gestureType, const QString& gestureImage,
        const QStringList& allowedActions) : QFrame() {
    // Inicializamos los atributos
    this->gestureType = gestureType;
    this->configForm  = NULL;
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);

    // Label con la imagen del gesto
    this->gestureLabel = new QLabel();
    this->gestureLabel->setMaximumSize(60, 60);
    this->gestureLabel->setMinimumSize(60, 60);
    this->gestureLabel->setPixmap(QPixmap(gestureImage));

    // ComboBox con las acciones permitidas
    this->allowedActionsCombo = new QComboBox();
    this->allowedActionsCombo->addItems(allowedActions);

    // Botón para editar la acción seleccionada
    this->configButton = new QPushButton();
    this->configButton->setMaximumWidth(32);
    this->configButton->setMinimumWidth(32);
    this->configButton->setCheckable(true);
    this->configButton->setIcon(QIcon::fromTheme("configure"));

    // Cargamos la acción y la configuración inicial desde disco
    GuiController* guiController = GuiController::getInstance();
    GestureTransfer* transfer = (GestureTransfer*)guiController->execute(
            READ_GESTURE, &gestureType);
    int index = this->allowedActionsCombo->findText(ActionTypeEnum::getValue(
            transfer->getActionType()));
    index = (index == -1) ? 0 : index;
    this->allowedActionsCombo->setCurrentIndex(index);

    ConfigFormFactory* factory = ConfigFormFactory::getInstance();
    this->configForm = factory->createConfigForm(transfer->getActionType());
    this->configButton->setEnabled(this->configForm != NULL);
    if(this->configForm != NULL) {
        this->configForm->setSettings(transfer->getSettings());
        this->configForm->setVisible(false);
    }

    delete transfer;

    // Colocamos los componentes en el formulario
    this->layout = new QGridLayout;
    this->layout->addWidget(this->gestureLabel, 0, 0, 1, 1);
    this->layout->addWidget(this->allowedActionsCombo, 0, 1, 1, 1);
    this->layout->addWidget(this->configButton, 0, 2, 1, 1);
    if(this->configForm != NULL)
        this->layout->addWidget(this->configForm, 1, 0, 1, 3);
    this->setLayout(this->layout);

    // Conectamos signals y slots
    connect(this->allowedActionsCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(actionChanged(int)));
    connect(this->configButton, SIGNAL(toggled(bool)),
            this, SLOT(showConfigForm(bool)));
    if(this->configForm != NULL) {
        connect(this->configForm, SIGNAL(configChanged()),
                this, SLOT(configChanged()));
    }

}

GestureConfigWidget::~GestureConfigWidget() {
    delete this->gestureLabel;
    delete this->allowedActionsCombo;
    delete this->configButton;
    if(this->configForm != NULL)
        delete this->configForm;
}


// ************************************************************************** //
// **********                     PRIVATE SLOTS                    ********** //
// ************************************************************************** //

void GestureConfigWidget::actionChanged(int newAction) {
    // Si la acción anterior usaba un formulario de configuración lo borramos
    if(this->configForm != NULL) {
        this->configButton->setChecked(false);
        this->layout->removeWidget(this->configForm);
        disconnect(this->configForm, SIGNAL(configChanged()),
                this, SLOT(configChanged()));
        delete this->configForm;
    }

    // Vemos que acción está seleccionada
    QString actionText = this->allowedActionsCombo->itemText(newAction);
    ActionTypeEnum::ActionType action = (newAction == 0)
            ? ActionTypeEnum::NO_ACTION
            : ActionTypeEnum::getEnum(actionText);

    // Si corresponde añadimos un formulario para configurar la acción
    ConfigFormFactory* factory = ConfigFormFactory::getInstance();
    this->configForm = factory->createConfigForm(action);
    this->configButton->setEnabled(this->configForm != NULL);

    QString settings = "";
    if(this->configForm != NULL) {
        // Cargamos la configuración por defecto desde disco
        GuiController* guiController = GuiController::getInstance();
        GestureTransfer* transfer = (GestureTransfer*)guiController->execute(
                READ_GESTURE, &gestureType);
        this->configForm->setSettings(transfer->getSettings());
        settings = this->configForm->getSettings();
        delete transfer;

        // Colocamos los componentes en el formulario
        this->configForm->setVisible(false);
        this->layout->addWidget(this->configForm, 1, 0, 1, 3);

        connect(this->configForm, SIGNAL(configChanged()),
                this, SLOT(configChanged()));
    }

    // Actualizamos la configuración del gesto
    GestureTransfer transfer(this->gestureType, action, settings);
    GuiController* guiController = GuiController::getInstance();
    guiController->execute(UPDATE_GESTURE, &transfer);
}

void GestureConfigWidget::showConfigForm(bool checked) const {
    if(this->configForm != NULL && checked) {
        this->configForm->setVisible(true);
    } else if(this->configForm != NULL && !checked) {
        this->configForm->setVisible(false);
    }
}

void GestureConfigWidget::configChanged() const {
    // Guardamos los cambios en disco
    QString actionText = this->allowedActionsCombo->currentText();
    ActionTypeEnum::ActionType action =
            (this->allowedActionsCombo->currentIndex() == 0)
            ? ActionTypeEnum::NO_ACTION
            : ActionTypeEnum::getEnum(actionText);

    QString settings = "";
    if(this->configForm != NULL) {
        settings = this->configForm->getSettings();
    }

    GestureTransfer transfer(this->gestureType, action, settings);
    GuiController* guiController = GuiController::getInstance();
    guiController->execute(UPDATE_GESTURE, &transfer);
}
