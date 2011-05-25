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
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/presentation/widgets/MenuItem.h"
#include "src/touchegg-gui/presentation/main_window/GesturesTab.h"
#include "src/touchegg-gui/presentation/main_window/GeneralSettingsTab.h"
namespace Ui { class MainWindow; }

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

        // Tabs to configure Touchégg
        GesturesTab* gesturesTab;
        GeneralSettingsTab* generalSettingsTab;

    public:

        /**
         * @~spanish
         * Contructor por defecto.
         *
         * @~english
         * Default constructor.
         */
        MainWindow(QWidget *parent = 0);

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
         * Se llama cada vez que se pulse en el menu.
         * @param row Fila.
         * @param column Columna.
         *
         * @~english
         * Is called whenever the menu is clicked.
         * @param row Row
         * @param column Column.
         */
        void on_menu_cellClicked(int row, int column);

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Se llama cada vez que se pulse el botón aplicar.
         *
         * @~english
         * Is called whenever the apply button is clicked.
         */
        void on_applyButton_clicked();

        /**
         * @~spanish
         * Se llama cada vez que se pulse el botón aceptar.
         *
         * @~english
         * Is called whenever the accept button is clicked.
         */
        void on_acceptButton_clicked();

        /**
         * @~spanish
         * Se llama cada vez que se pulse el botón cancelar.
         *
         * @~english
         * Is called whenever the cancel button is clicked.
         */
        void on_cancelButton_clicked();

};

#endif // MAINWINDOW_H
