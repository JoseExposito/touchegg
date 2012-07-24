/**
 * @file src/touchegg/actions/types/ActionTypeEnum.cpp
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
#include "ActionTypeEnum.h"

// ****************************************************************************************************************** //
// **********                                 STATIC METHODS AND VARIABLES                                 ********** //
// ****************************************************************************************************************** //

QString ActionTypeEnum::getValue(ActionType atEnum)
{
    ActionTypeEnum actionTypeEnum;
    int index = actionTypeEnum.metaObject()->indexOfEnumerator("ActionType");
    QMetaEnum metaEnum = actionTypeEnum.metaObject()->enumerator(index);
    return metaEnum.valueToKey(atEnum);
}

ActionTypeEnum::ActionType ActionTypeEnum::getEnum(const QString &atString)
{
    ActionTypeEnum actionTypeEnum;
    int index = actionTypeEnum.metaObject()->indexOfEnumerator("ActionType");
    QMetaEnum metaEnum = actionTypeEnum.metaObject()->enumerator(index);
    return (ActionTypeEnum::ActionType)metaEnum.keyToValue(atString.toStdString().c_str());
}
