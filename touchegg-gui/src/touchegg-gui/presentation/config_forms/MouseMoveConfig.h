/**
 * @file /src/touchegg-gui/presentation/config_forms/MouseMoveConfig.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MouseMoveConfig
 * @author José Expósito
 */
#ifndef MOUSEMOVECONFIG_H
#define MOUSEMOVECONFIG_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/presentation/config_forms/ConfigForm.h"

/**
 * @~spanish
 * Implementación de ConfigForm para la acción MOUSE_MOVE, ver la documentación
 * en dicha clase.
 *
 * @~english
 * ConfigForm implementation for MOUSE_MOVE action, to see documentation check
 * that class.
 */
class MouseMoveConfig : public ConfigForm {

    private:

        QSlider* slider;

    public:

        MouseMoveConfig();

        QString getSettings() const;

        void setSettings(const QString& settings);

};

#endif // MOUSEMOVECONFIG_H
