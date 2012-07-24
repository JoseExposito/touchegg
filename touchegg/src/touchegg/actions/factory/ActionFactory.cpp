/**
 * @file /src/touchegg/actions/factory/ActionFactory.cpp
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
#include "ActionFactory.h"

// ****************************************************************************************************************** //
// **********                                 STATIC METHODS AND VARIABLES                                 ********** //
// ****************************************************************************************************************** //

ActionFactory *ActionFactory::instance = NULL;

ActionFactory *ActionFactory::getInstance()
{
    if (ActionFactory::instance == NULL)
        ActionFactory::instance = new ActionFactory();

    return ActionFactory::instance;
}


// ****************************************************************************************************************** //
// **********                                        PUBLIC METHODS                                        ********** //
// ****************************************************************************************************************** //

Action *ActionFactory::createAction(ActionTypeEnum::ActionType actionType,
        const QString &settings, Window window)
{
    switch (actionType) {
    case ActionTypeEnum::NO_ACTION:
        return NULL;

    case ActionTypeEnum::MOUSE_CLICK:
        return new MouseClick(settings, window);

    case ActionTypeEnum::SCROLL:
        return new Scroll(settings, window);

    case ActionTypeEnum::MINIMIZE_WINDOW:
        return new MinimizeWindow(settings, window);

    case ActionTypeEnum::MAXIMIZE_RESTORE_WINDOW:
        return new MaximizeRestoreWindow(settings, window);

    case ActionTypeEnum::CLOSE_WINDOW:
        return new CloseWindow(settings, window);

    case ActionTypeEnum::RESIZE_WINDOW:
        return new ResizeWindow(settings, window);

    case ActionTypeEnum::SHOW_DESKTOP:
        return new ShowDesktop(settings, window);

    case ActionTypeEnum::CHANGE_DESKTOP:
        return new ChangeDesktop(settings, window);

    case ActionTypeEnum::CHANGE_VIEWPORT:
        return new ChangeViewport(settings, window);

    case ActionTypeEnum::SEND_KEYS:
        return new SendKeys(settings, window);

    case ActionTypeEnum::MOVE_WINDOW:
        return new MoveWindow(settings, window);

    case ActionTypeEnum::RUN_COMMAND:
        return new RunCommand(settings, window);

    case ActionTypeEnum::DRAG_AND_DROP:
        return new DragAndDrop(settings, window);

    default:
        return NULL;
    }
}
