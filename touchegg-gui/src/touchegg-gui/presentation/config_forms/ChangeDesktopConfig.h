/**
 * @file /src/touchegg-gui/presentation/config_forms/ChangeDesktopConfig.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ChangeDesktopConfig
 * @author José Expósito
 */
#ifndef CHANGEDESKTOPCONFIG_H
#define CHANGEDESKTOPCONFIG_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/presentation/config_forms/ConfigForm.h"

/**
 * @~spanish
 * Implementación de ConfigForm para la acción CHANGE_DESKTOP, ver la
 * documentación en dicha clase.
 *
 * @~english
 * ConfigForm implementation for CHANGE_DESKTOP action, to see documentation
 * check that class.
 */
class ChangeDesktopConfig : public ConfigForm {

    private:

        QComboBox* leftRight;

    public:

        ChangeDesktopConfig();

        QString getSettings() const;

        void setSettings(const QString& settings);

};

#endif // CHANGEDESKTOPCONFIG_H
