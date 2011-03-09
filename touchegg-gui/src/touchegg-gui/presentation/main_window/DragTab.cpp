/**
 * @file /src/touchegg-gui/presentation/main_window/DragTab.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  DragTab
 * @author José Expósito
 */
#include "DragTab.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

DragTab::DragTab() {
    // Estilo del panel
    this->setFrameShape(QFrame::NoFrame);
    this->setFrameShadow(QFrame::Plain);

    // Acciones permitidas
    QStringList strList;
    strList.append("No action");
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MOUSE_WHEEL_UP));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MOUSE_WHEEL_DOWN));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MINIMIZE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MAXIMIZE_RESTORE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::CLOSE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::SHOW_DESKTOP));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::CHANGE_DESKTOP));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::RUN_COMMAND));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::SEND_KEYS));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::MOVE_WINDOW));
    strList.append(ActionTypeEnum::getValue(ActionTypeEnum::DRAG_AND_DROP));

    // Creamos los distintos widgeds para configurar los gestos
    GestureConfigWidget* twoFingersDragUp = new GestureConfigWidget(
            GestureTypeEnum::TWO_FINGERS_DRAG_UP,
            ":/images/two_fingers_drag_up.png", strList);
    GestureConfigWidget* twoFingersDragDown = new GestureConfigWidget(
            GestureTypeEnum::TWO_FINGERS_DRAG_DOWN,
            ":/images/two_fingers_drag_down.png", strList);
    GestureConfigWidget* twoFingersDragLeft = new GestureConfigWidget(
            GestureTypeEnum::TWO_FINGERS_DRAG_LEFT,
            ":/images/two_fingers_drag_left.png", strList);
    GestureConfigWidget* twoFingersDragRight = new GestureConfigWidget(
            GestureTypeEnum::TWO_FINGERS_DRAG_RIGHT,
            ":/images/two_fingers_drag_right.png", strList);

    GestureConfigWidget* threeFingersDragUp = new GestureConfigWidget(
            GestureTypeEnum::THREE_FINGERS_DRAG_UP,
            ":/images/three_fingers_drag_up.png", strList);
    GestureConfigWidget* threeFingersDragDown = new GestureConfigWidget(
            GestureTypeEnum::THREE_FINGERS_DRAG_DOWN,
            ":/images/three_fingers_drag_down.png", strList);
    GestureConfigWidget* threeFingersDragLeft = new GestureConfigWidget(
            GestureTypeEnum::THREE_FINGERS_DRAG_LEFT,
            ":/images/three_fingers_drag_left.png", strList);
    GestureConfigWidget* threeFingersDragRight = new GestureConfigWidget(
            GestureTypeEnum::THREE_FINGERS_DRAG_RIGHT,
            ":/images/three_fingers_drag_right.png", strList);

    GestureConfigWidget* fourFingersDragUp = new GestureConfigWidget(
            GestureTypeEnum::FOUR_FINGERS_DRAG_UP,
            ":/images/four_fingers_drag_up.png", strList);
    GestureConfigWidget* fourFingersDragDown = new GestureConfigWidget(
            GestureTypeEnum::FOUR_FINGERS_DRAG_DOWN,
            ":/images/four_fingers_drag_down.png", strList);
    GestureConfigWidget* fourFingersDragLeft = new GestureConfigWidget(
            GestureTypeEnum::FOUR_FINGERS_DRAG_LEFT,
            ":/images/four_fingers_drag_left.png", strList);
    GestureConfigWidget* fourFingersDragRight = new GestureConfigWidget(
            GestureTypeEnum::FOUR_FINGERS_DRAG_RIGHT,
            ":/images/four_fingers_drag_right.png", strList);

    /*GestureConfigWidget* fiveFingersDragUp = new GestureConfigWidget(
            GestureTypeEnum::FIVE_FINGERS_DRAG_UP,
            ":/images/five_fingers_drag_up.png", strList);
    GestureConfigWidget* fiveFingersDragDown = new GestureConfigWidget(
            GestureTypeEnum::FIVE_FINGERS_DRAG_DOWN,
            ":/images/five_fingers_drag_down.png", strList);
    GestureConfigWidget* fiveFingersDragLeft = new GestureConfigWidget(
            GestureTypeEnum::FIVE_FINGERS_DRAG_LEFT,
            ":/images/five_fingers_drag_left.png", strList);
    GestureConfigWidget* fiveFingersDragRight = new GestureConfigWidget(
            GestureTypeEnum::FIVE_FINGERS_DRAG_RIGHT,
            ":/images/five_fingers_drag_right.png", strList);*/

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(twoFingersDragUp);
    layout->addWidget(twoFingersDragDown);
    layout->addWidget(twoFingersDragLeft);
    layout->addWidget(twoFingersDragRight);

    layout->addWidget(threeFingersDragUp);
    layout->addWidget(threeFingersDragDown);
    layout->addWidget(threeFingersDragLeft);
    layout->addWidget(threeFingersDragRight);

    layout->addWidget(fourFingersDragUp);
    layout->addWidget(fourFingersDragDown);
    layout->addWidget(fourFingersDragLeft);
    layout->addWidget(fourFingersDragRight);

    /*layout->addWidget(fiveFingersDragUp);
    layout->addWidget(fiveFingersDragDown);
    layout->addWidget(fiveFingersDragLeft);
    layout->addWidget(fiveFingersDragRight);*/

    layout->addStretch();

    // Ponemos los componentes dentro del scroll area
    QFrame* aux = new QFrame;
    aux->setLayout(layout);
    this->setWidget(aux);
    this->setWidgetResizable(true);
}
