/**
 * @file /src/touchegg/actions/factory/ActionFactory.h
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
 * @class  ActionFactory
 */
#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "src/touchegg/actions/types/ActionTypeEnum.h"
#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/types/ActionTypeEnum.h"
#include "src/touchegg/actions/implementation/Action.h"
#include "src/touchegg/actions/implementation/MouseClick.h"
#include "src/touchegg/actions/implementation/Scroll.h"
#include "src/touchegg/actions/implementation/MinimizeWindow.h"
#include "src/touchegg/actions/implementation/MaximizeRestoreWindow.h"
#include "src/touchegg/actions/implementation/CloseWindow.h"
#include "src/touchegg/actions/implementation/ResizeWindow.h"
#include "src/touchegg/actions/implementation/ShowDesktop.h"
#include "src/touchegg/actions/implementation/ChangeDesktop.h"
#include "src/touchegg/actions/implementation/ChangeViewport.h"
#include "src/touchegg/actions/implementation/SendKeys.h"
#include "src/touchegg/actions/implementation/MoveWindow.h"
#include "src/touchegg/actions/implementation/RunCommand.h"
#include "src/touchegg/actions/implementation/DragAndDrop.h"

/**
 * @~spanish
 * Factoría para crear las distintas acciones.
 *
 * @~english
 * Factory to create the different actions.
 */
class ActionFactory
{

private:

    /**
     * @~spanish
     * Única instancia de la clase.
     *
     * @~english
     * Single instance of the class.
     */
    static ActionFactory* instance;

    // Hide constructors
    ActionFactory(){}
    ActionFactory(const ActionFactory&);
    const ActionFactory& operator = (const ActionFactory&);

public:

    /**
     * @~spanish
     * Único método para obtener una instancia de la clase.
     * @return La única instancia de la clase.
     *
     * @~english
     * Only method to get an instance of the class.
     * @return The single instance of the class.
     */
    static ActionFactory* getInstance();

    /**
     * @~spanish
     * Crea la acción indicada, si no existe devuelve NULL.
     * IMPORTANTE: No olvidar liberar memoria.
     * @param  actionType Tipo de acción a crear.
     * @param  settings   Configuración de la acción.
     * @param  window     Ventana sobre la que ejecutar la acción.
     * @return La acción.
     *
     * @~english
     * Creates the specified action, if it not exist returns NULL.
     * IMPORTANT: Don't forget to free memory.
     * @param  actionType Action type to create.
     * @param  settings   Action settings.
     * @param  window     Window on which execute the action.
     * @return The action.
     */
    Action* createAction(ActionTypeEnum::ActionType actionType,
        const QString& settings, Window window);

};

#endif // ACTIONFACTORY_H
