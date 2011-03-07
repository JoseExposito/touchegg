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
    //this->configButton->setIcon(QIcon::fromTheme("document-properties"));
    this->configButton->setIcon(QIcon::fromTheme("configure"));

    // Colocamos los componentes en el formulario
    QHBoxLayout*layout = new QHBoxLayout;
    layout->addWidget(this->gestureLabel);
    layout->addWidget(this->allowedActionsCombo);
    layout->addWidget(this->configButton);

    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);
    this->setLayout(layout);
}

GestureConfigWidget::~GestureConfigWidget() {
    delete this->gestureLabel;
    delete this->allowedActionsCombo;
    delete this->configButton;
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

GestureTypeEnum::GestureType GestureConfigWidget::getGestureType() const {
    return this->gestureType;
}

ActionTypeEnum::ActionType GestureConfigWidget::getAsociatedAction() const {
    return this->asociatedAction;
}

QString GestureConfigWidget::getActionSettings() const {
    return this->actionSettings;
}
