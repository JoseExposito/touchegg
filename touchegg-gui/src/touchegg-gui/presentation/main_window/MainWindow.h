#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/presentation/main_window/TapTab.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

    private:

        Ui::MainWindow *ui;

    public:

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();


};

#endif // MAINWINDOW_H
