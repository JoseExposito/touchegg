/**
 * @file /src/touchegg-gui/presentation/main_window/TapAndHoldTab.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  TapAndHoldTab
 * @author José Expósito
 */
#include "TapAndHoldTab.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

TapAndHoldTab::TapAndHoldTab() {
    // Estilo del panel
    this->setFrameShape(QFrame::NoFrame);
    this->setFrameShadow(QFrame::Plain);

    // Acciones permitidas
    QStringList strList;
    strList.append("No action");
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::DRAG_AND_DROP));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MOVE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::RUN_COMMAND));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::SEND_KEYS));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MINIMIZE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MAXIMIZE_RESTORE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::CLOSE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::SHOW_DESKTOP));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::CHANGE_DESKTOP));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MOUSE_MOVE));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::LEFT_BUTTON_CLICK));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::RIGHT_BUTTON_CLICK));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MIDDLE_BUTTON_CLICK));

    // Creamos los distintos widgeds para configurar los gestos
    GestureConfigWidget* twoFingersTapAndHold = new GestureConfigWidget(
            GestureTypeEnum::TWO_FINGERS_TAP_AND_HOLD,
            ":/images/two_fingers_tap_and_hold.png", strList);

    GestureConfigWidget* threeFingersTapAndHold = new GestureConfigWidget(
            GestureTypeEnum::THREE_FINGERS_TAP_AND_HOLD,
            ":/images/three_fingers_tap_and_hold.png", strList);

    GestureConfigWidget* fourFingersTapAndHold = new GestureConfigWidget(
            GestureTypeEnum::FOUR_FINGERS_TAP_AND_HOLD,
            ":/images/four_fingers_tap_and_hold.png", strList);

    GestureConfigWidget* fiveFingersTapAndHold = new GestureConfigWidget(
            GestureTypeEnum::FIVE_FINGERS_TAP_AND_HOLD,
            ":/images/five_fingers_tap_and_hold.png", strList);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(twoFingersTapAndHold);
    layout->addWidget(threeFingersTapAndHold);
    layout->addWidget(fourFingersTapAndHold);
    layout->addWidget(fiveFingersTapAndHold);
    layout->addStretch();

    // Ponemos los componentes dentro del scroll area
    QFrame* aux = new QFrame;
    aux->setLayout(layout);
    this->setWidget(aux);
    this->setWidgetResizable(true);
}
