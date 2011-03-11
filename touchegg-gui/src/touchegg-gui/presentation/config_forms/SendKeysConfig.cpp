#include "SendKeysConfig.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

SendKeysConfig::SendKeysConfig() {
    QLabel* holdDownLabel = new QLabel("Keys to hold down");
    QLabel* pressLabel    = new QLabel("Keys to press in between");
    this->holdDownText    = new QLineEdit;
    this->pressText       = new QLineEdit;

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(holdDownLabel, 0, 0, 1, 1);
    layout->addWidget(this->holdDownText, 0, 1, 1, 1);
    layout->addWidget(pressLabel, 1, 0, 1, 1);
    layout->addWidget(this->pressText, 1, 1, 1, 1);
    this->setLayout(layout);

    connect(this->holdDownText, SIGNAL(editingFinished()),
            this, SIGNAL(configChanged()));
    connect(this->pressText, SIGNAL(editingFinished()),
            this, SIGNAL(configChanged()));
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

QString SendKeysConfig::getSettings() const {
    return "HOLD_DOWN=" + this->holdDownText->text() +
            ":PRESS=" + this->pressText->text();
}

void SendKeysConfig::setSettings(const QString& settings) {
    if(settings.split(":").length() != 2) {
        return;
    }

    QString allHoldDown = settings.split(":").at(0);
    QString allBetween  = settings.split(":").at(1);

    if(allHoldDown.split("=").length() != 2
            || allBetween.split("=").length() != 2) {
        return;
    }

    if(allHoldDown.split("=").at(0) != "HOLD_DOWN"
            || allBetween.split("=").at(0) != "PRESS") {
        return;
    }

    this->holdDownText->setText(allHoldDown.split("=").at(1));
    this->pressText->setText(allBetween.split("=").at(1));
}
