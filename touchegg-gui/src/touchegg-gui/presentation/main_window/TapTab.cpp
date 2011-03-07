#include "TapTab.h"

TapTab::TapTab() : QFrame() {
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
    this->setLayout(layout);
}
