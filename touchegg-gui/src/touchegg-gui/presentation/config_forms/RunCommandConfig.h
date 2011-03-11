/**
 * @file /src/touchegg-gui/presentation/config_forms/RunCommandConfig.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  RunCommandConfig
 * @author José Expósito
 */
#ifndef RUNCOMMANDCONFIG_H
#define RUNCOMMANDCONFIG_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/presentation/config_forms/ConfigForm.h"

/**
 * @~spanish
 * Implementación de ConfigForm para la acción RUN_COMMAND, ver la documentación
 * en dicha clase.
 *
 * @~english
 * ConfigForm implementation for RUN_COMMAND action, to see documentation check
 * that class.
 */
class RunCommandConfig : public ConfigForm {

    private:

        QLineEdit* command;

    public:

        RunCommandConfig();

        QString getSettings() const;

        void setSettings(const QString& settings);

};

#endif // RUNCOMMANDCONFIG_H
