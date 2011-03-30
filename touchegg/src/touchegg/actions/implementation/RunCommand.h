/**
 * @file /src/touchegg/actions/implementation/RunCommand.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  RunCommand
 * @author José Expósito
 */

#ifndef RUNCOMMAND_H
#define RUNCOMMAND_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Ejecuta el comando indicado en la configuración.
 *
 * @~english
 * Runs the command specified in the configuration.
 */
class RunCommand : public Action {

    private:

        /**
         * @~spanish
         * Comando a ejecutar.
         *
         * @~english
         * Command to execute.
         */
        QString command;

    public:

        RunCommand(const QString& settings, Window window);

        void executeStart(const QHash<QString, QVariant>& attrs);

        void executeUpdate(const QHash<QString, QVariant>& attrs);

        void executeFinish(const QHash<QString, QVariant>& attrs);
};

#endif // RUNCOMMAND_H
