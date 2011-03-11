/**
 * @file /src/touchegg-gui/presentation/config_forms/MouseWhellConfig.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MouseWhellConfig
 * @author José Expósito
 */
#ifndef MOUSEWHELLCONFIG_H
#define MOUSEWHELLCONFIG_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/presentation/config_forms/ConfigForm.h"

/**
 * @~spanish
 * Implementación de ConfigForm para la acción MOUSE_WHELL, ver la documentación
 * en dicha clase.
 *
 * @~english
 * ConfigForm implementation for MOUSE_WHELL action, to see documentation check
 * that class.
 */
class MouseWhellConfig : public ConfigForm {

    private:

        QSlider* slider;

    public:

        MouseWhellConfig();

        QString getSettings() const;

        void setSettings(const QString& settings);

};

#endif // MOUSEWHELLCONFIG_H
