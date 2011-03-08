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
    // Guardamos los atributos
    this->gestureType = gestureType;

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
    this->configButton->setIcon(QIcon::fromTheme("configure"));

    // Colocamos los componentes en el formulario
    QHBoxLayout*layout = new QHBoxLayout;
    layout->addWidget(this->gestureLabel);
    layout->addWidget(this->allowedActionsCombo);
    layout->addWidget(this->configButton);

    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);
    this->setLayout(layout);

    // Conectamos signals y slots
    connect(this->allowedActionsCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(actionChanged(int)));

    // Cargamos el valor por defecto
    GuiController* guiController = GuiController::getInstance();
    GestureTransfer* transfer = (GestureTransfer*)guiController->execute(
            READ_GESTURE, &gestureType);
    int index = this->allowedActionsCombo->findText(ActionTypeEnum::getValue(
            transfer->getActionType()));
    delete transfer;
    index = (index == -1) ? 0 : index;
    this->allowedActionsCombo->setCurrentIndex(index);
    this->actionChanged(index);
}

GestureConfigWidget::~GestureConfigWidget() {
    delete this->gestureLabel;
    delete this->allowedActionsCombo;
    delete this->configButton;
}


// ************************************************************************** //
// **********                     PRIVATE SLOTS                    ********** //
// ************************************************************************** //

void GestureConfigWidget::actionChanged(int newAction) const {
    // Construimos el transfer con los nuevos datos
    QString actionText = this->allowedActionsCombo->itemText(newAction);
    ActionTypeEnum::ActionType action = (newAction == 0)
            ? ActionTypeEnum::NO_ACTION
            : ActionTypeEnum::getEnum(actionText);
    GestureTransfer transfer(this->gestureType, action, ""); // TODO this->configForm.getSettings();

    // Actualizamos la configuración del gesto
    GuiController* guiController = GuiController::getInstance();
    guiController->execute(UPDATE_GESTURE, &transfer);
}
