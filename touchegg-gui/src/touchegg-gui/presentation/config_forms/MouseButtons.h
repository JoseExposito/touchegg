/**
 * @file /src/touchegg-gui/presentation/config_forms/MouseButtons.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MouseButtons
 * @author José Expósito
 */
#ifndef MOUSEBUTTONS_H
#define MOUSEBUTTONS_H

#include "src/touchegg-gui/presentation/config_forms/ConfigForm.h"
namespace Ui { class MouseButtons; }

/**
 * @~spanish
 * Permite seleccionar un botón del ratón, ver la documentación en ConfigForm.
 *
 * @~english
 * Allows to select a mouse button, see the documentation in ConfigForm.
 */
class MouseButtons : public ConfigForm {

    Q_OBJECT

    private:

        Ui::MouseButtons *ui;

    public:

        MouseButtons();

        ~MouseButtons();

        QString getSettings() const;

        void setSettings(const QString& settings);

};

#endif // MOUSEBUTTONS_H
