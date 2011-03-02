#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Pestaña Tap
    QWidget* tapTab = this->ui->tabWidget->widget(1);
    QVBoxLayout* tapLayout = new QVBoxLayout;

    QStringList strList;
    strList.append("Accion 1");
    strList.append("La 2");
    strList.append("Antena 3");
    strList.append("Ultima");
    GestureConfigWidget* twoFingersTap = new GestureConfigWidget(
            GestureTypeEnum::TWO_FINGERS_TAP,
            ":/images/two_fingers_tap.png", strList);

    /*GestureConfigWidget* threeFingersTap = new GestureConfigWidget(
            GestureTypeEnum::THREE_FINGERS_TAP,
            ":/images/three_fingers_tap.png", strList);*/

    tapLayout->addWidget(twoFingersTap);
    //tapLayout->addWidget(threeFingersTap);
    tapLayout->addStretch();
    tapTab->setLayout(tapLayout);
}

MainWindow::~MainWindow() {
    delete this->ui;
}
