/**
 * @file /src/touchegg-gui/presentation/config_forms/SendKeysConfig.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  SendKeysConfig
 * @author José Expósito
 */
#ifndef SENDKEYSCONFIG_H
#define SENDKEYSCONFIG_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/presentation/config_forms/ConfigForm.h"

/**
 * @~spanish
 * Implementación de ConfigForm para la acción SEND_KEYS, ver la documentación
 * en dicha clase.
 *
 * @~english
 * ConfigForm implementation for SEND_KEYS action, to see documentation check
 * that class.
 */
class SendKeysConfig : public ConfigForm {

    private:

        QLineEdit* holdDownText;
        QLineEdit* pressText;

    public:

        SendKeysConfig();

        QString getSettings() const;

        void setSettings(const QString& settings);

};

#endif // SENDKEYSCONFIG_H
