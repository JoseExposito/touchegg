#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Ponemos los iconos del tema
    QListWidgetItem* aux = this->ui->menuList->item(4);
    QPixmap pixmap(QIcon::fromTheme("configure").pixmap(35, 50));
    aux->setIcon(QIcon(pixmap));
    this->ui->applyButton->setIcon(QIcon::fromTheme("dialog-ok-apply"));

    // creamos los distintos paneles con los widgeds de configuración
    TapTab* tapTab = new TapTab;

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(this->ui->menuList, 0, 0, 2, 1);
    layout->addWidget(tapTab, 0, 1, 1, 1);
    layout->addWidget(this->ui->buttonsFrame, 1, 1, 1, 1);
    this->ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow() {
    delete this->ui;
}




void MainWindow::on_applyButton_clicked() {
    GuiController* guiController = GuiController::getInstance();
    guiController->execute(COMMIT_DATA, NULL);
}

void MainWindow::closeEvent(QCloseEvent* /*event*/) {
    GuiController* guiController = GuiController::getInstance();
    guiController->execute(COMMIT_DATA, NULL);
}
