/**
 * @file src/touchegg/actions/types/ActionTypeEnum.h
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
 * @class  ActionTypeEnum
 */
#ifndef ACTIONTYPEENUM_H
#define ACTIONTYPEENUM_H

#include "src/touchegg/util/Include.h"

/**
 * Contains a enumeradted type with supported actions.
 */
class ActionTypeEnum : public QObject
{

    Q_OBJECT
    Q_ENUMS(ActionType)

public:

    /**
     * Enumerated type with supported actions.
     */
    enum ActionType {
        NO_ACTION,
        MOUSE_CLICK,
        SCROLL,
        MINIMIZE_WINDOW,
        MAXIMIZE_RESTORE_WINDOW,
        CLOSE_WINDOW,
        RESIZE_WINDOW,
        SHOW_DESKTOP,
        CHANGE_DESKTOP,
        CHANGE_VIEWPORT,
        SEND_KEYS,
        MOVE_WINDOW,
        RUN_COMMAND,
        DRAG_AND_DROP
    };

    /**
     * Converts the enum to QString.
     * @return The QString.
     */
    static QString getValue(ActionType atEnum);

    /**
     * Converts the indicated QString to the equivalent enum type.
     * @return The enum type.
     */
    static ActionType getEnum(const QString &atString);
};

#endif // ACTIONTYPEENUM_H
