/**
 * @file /src/touchegg-gui/presentation/main_window/GeneralSettingsTab.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GeneralSettingsTab
 * @author José Expósito
 */
#ifndef GENERALSETTINGSTAB_H
#define GENERALSETTINGSTAB_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/presentation/gui_controller/GuiController.h"
#include "src/touchegg-gui/logic/transfer/GeneralTransfer.h"

namespace Ui {
    class GeneralSettingsTab;
}

/**
 * @~spanish
 * Pestaña para configurar las preferencias generales.
 *
 * @~english
 * Tab to configure general settigs.
 */
class GeneralSettingsTab : public QFrame {

    Q_OBJECT

    private:

        Ui::GeneralSettingsTab *ui;

    public:

        /**
         * @~spanish
         * Constructor.
         *
         * @~english
         * Constructor.
         */
        explicit GeneralSettingsTab(QWidget *parent = 0);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * Destructor.
         */
        ~GeneralSettingsTab();

    private slots:

        /**
         * @~spanish
         * Se llama cuando se cambia el valor del slider.
         *
         * @~english
         * Is called whenever slider value changed.
         */
        void on_horizontalSlider_valueChanged(int value);

        /**
         * @~spanish
         * Se llama cuando se pulsa el checkbox.
         *
         * @~english
         * Is called whenever the checkbox is pressed.
         */
        void on_checkBox_clicked(bool checked);

};

#endif // GENERALSETTINGSTAB_H
