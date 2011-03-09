/**
 * @file /src/touchegg-gui/presentation/main_window/PinchTab.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  PinchTab
 * @author José Expósito
 */
#include "PinchTab.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

PinchTab::PinchTab() {
    // Estilo del panel
    this->setFrameShape(QFrame::NoFrame);
    this->setFrameShadow(QFrame::Plain);

    // Acciones permitidas
    QStringList strList;
    strList.append("No action");
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::RESIZE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::SEND_KEYS));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::RUN_COMMAND));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::SHOW_DESKTOP));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::CHANGE_DESKTOP));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MINIMIZE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MAXIMIZE_RESTORE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::CLOSE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::LEFT_BUTTON_CLICK));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::RIGHT_BUTTON_CLICK));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MIDDLE_BUTTON_CLICK));

    // Creamos los distintos widgeds para configurar los gestos
    GestureConfigWidget* threeFingersPinch = new GestureConfigWidget(
            GestureTypeEnum::THREE_FINGERS_PINCH,
            ":/images/three_fingers_pinch.png", strList);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(threeFingersPinch);
    layout->addStretch();

    // Ponemos los componentes dentro del scroll area
    QFrame* aux = new QFrame;
    aux->setLayout(layout);
    this->setWidget(aux);
    this->setWidgetResizable(true);
}
