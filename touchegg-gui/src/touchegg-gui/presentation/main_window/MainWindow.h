/**
 * @file /src/touchegg-gui/presentation/main_window/MainWindow.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MainWindow
 * @author José Expósito
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/presentation/main_window/TapTab.h"
#include "src/touchegg-gui/presentation/main_window/DragTab.h"
#include "src/touchegg-gui/presentation/main_window/PinchTab.h"
#include "src/touchegg-gui/presentation/main_window/TapAndHoldTab.h"
#include "src/touchegg-gui/presentation/main_window/GeneralSettingsTab.h"

namespace Ui {
    class MainWindow;
}

/**
 * @~spanish
 * Ventana principal.
 *
 * @~english
 * Main window.
 */
class MainWindow : public QMainWindow {

    Q_OBJECT

    private:

        Ui::MainWindow *ui;

        // Tabs to configure gestures
        TapTab*        tapTab;
        DragTab*       dragTab;
        PinchTab*      pinchTab;
        TapAndHoldTab* tapAndHoldTab;
        GeneralSettingsTab* generalSettingsTab;

    public:

        /**
         * @~spanish
         * Contructor por defecto.
         *
         * @~english
         * Default constructor.
         */
        explicit MainWindow(QWidget *parent = 0);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * Destructor.
         */
        ~MainWindow();

    private slots:

        /**
         * @~spanish
         * Se llama cada vez que se pulse el botón aplicar.
         *
         * @~english
         * Is called whenever apply button is clicked.
         */
        void on_applyButton_clicked();

        /**
         * @~spanish
         * Se llama cada vez que se pulse en el menu.
         *
         * @~english
         * Is called whenever the menu is clicked.
         */
        void on_menuList_clicked(QModelIndex index);

    protected:

        /**
         * @~spanish
         * Se llama cuando se cierra la ventana.
         *
         * @~english
         * Is called whenever the window is closed.
         */
        void closeEvent(QCloseEvent* /*event*/);

};

#endif // MAINWINDOW_H
