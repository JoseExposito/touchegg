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
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011 - 2012
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
 * Factory to create the different actions.
 */
class ActionFactory
{

public:

    /**
     * Only method to get an instance of the class.
     * @return The single instance of the class.
     */
    static ActionFactory *getInstance();

    /**
     * Creates the specified action, if it not exist returns NULL.
     * IMPORTANT: Don't forget to free memory.
     * @param  actionType Action type to create.
     * @param  settings   Action settings.
     * @param  window     Window on which execute the action.
     * @return The action.
     */
    Action *createAction(ActionTypeEnum::ActionType actionType, const QString &settings, Window window);

private:

    /**
     * Single instance of the class.
     */
    static ActionFactory *instance;

    // Hide constructors
    ActionFactory() {}
    ActionFactory(const ActionFactory &);
    const ActionFactory &operator = (const ActionFactory &);
};

#endif // ACTIONFACTORY_H
