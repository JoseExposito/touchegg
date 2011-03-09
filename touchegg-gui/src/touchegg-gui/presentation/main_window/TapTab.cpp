/**
 * @file /src/touchegg-gui/presentation/main_window/TapTab.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  TapTab
 * @author José Expósito
 */
#include "TapTab.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

TapTab::TapTab() {
    // Estilo del panel
    this->setFrameShape(QFrame::NoFrame);
    this->setFrameShadow(QFrame::Plain);

    // Acciones permitidas
    QStringList strList;
    strList.append("No action");
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::LEFT_BUTTON_CLICK));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::RIGHT_BUTTON_CLICK));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MIDDLE_BUTTON_CLICK));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MINIMIZE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MAXIMIZE_RESTORE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::CLOSE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::SHOW_DESKTOP));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::CHANGE_DESKTOP));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::RUN_COMMAND));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::SEND_KEYS));

    // Creamos los distintos widgeds para configurar los gestos
    GestureConfigWidget* twoFingersTap = new GestureConfigWidget(
            GestureTypeEnum::TWO_FINGERS_TAP,
            ":/images/two_fingers_tap.png", strList);

    GestureConfigWidget* threeFingersTap = new GestureConfigWidget(
            GestureTypeEnum::THREE_FINGERS_TAP,
            ":/images/three_fingers_tap.png", strList);

    GestureConfigWidget* fourFingersTap = new GestureConfigWidget(
            GestureTypeEnum::FOUR_FINGERS_TAP,
            ":/images/four_fingers_tap.png", strList);

    GestureConfigWidget* fiveFingersTap = new GestureConfigWidget(
            GestureTypeEnum::FIVE_FINGERS_TAP,
            ":/images/five_fingers_tap.png", strList);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(twoFingersTap);
    layout->addWidget(threeFingersTap);
    layout->addWidget(fourFingersTap);
    layout->addWidget(fiveFingersTap);
    layout->addStretch();

    // Ponemos los componentes dentro del scroll area
    QFrame* aux = new QFrame;
    aux->setLayout(layout);
    this->setWidget(aux);
    this->setWidgetResizable(true);
}
