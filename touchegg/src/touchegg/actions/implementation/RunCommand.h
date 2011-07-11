/**
 * @file /src/touchegg/actions/implementation/RunCommand.h
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 3 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 *
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011
 * @class  RunCommand
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
class RunCommand : public Action
{

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
