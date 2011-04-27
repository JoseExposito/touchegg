/**
 * @file /src/touchegg-gui/presentation/config_forms/RunCommand.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  RunCommand
 * @author José Expósito
 */
#ifndef RUNCOMMAND_H
#define RUNCOMMAND_H

#include "src/touchegg-gui/presentation/config_forms/ConfigForm.h"
namespace Ui { class RunCommand; }


/**
 * @~spanish
 * Permite seleccionar un comando, ver la documentación en ConfigForm.
 *
 * @~english
 * Allows to select a command, see the documentation in ConfigForm.
 */
class RunCommand : public ConfigForm {

    Q_OBJECT

    private:

        Ui::RunCommand *ui;

    public:

        RunCommand();

        ~RunCommand();

        QString getSettings() const;

        void setSettings(const QString& settings);

};


#endif // RUNCOMMAND_H
