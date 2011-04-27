/**
 * @file /src/touchegg-gui/presentation/config_forms/SendKeys.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  SendKeys
 * @author José Expósito
 */
#ifndef SENDKEYS_H
#define SENDKEYS_H

#include "src/touchegg-gui/presentation/config_forms/ConfigForm.h"
namespace Ui { class SendKeys; }

/**
 * @~spanish
 * Permite seleccionar un atajo de teclado, ver la documentación en ConfigForm.
 *
 * @~english
 * Allows to select a shortcut, see the documentation in ConfigForm.
 */
class SendKeys : public ConfigForm {

    Q_OBJECT

    private:

        Ui::SendKeys *ui;

    public:

        SendKeys();

        ~SendKeys();

        QString getSettings() const;

        void setSettings(const QString& settings);

};

#endif // SENDKEYS_H
