/**
 * @file src/touchegg/gestures/types/GestureDirectionEnum.cpp
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
 * @class  GestureDirectionEnum
 */
#include "GestureDirectionEnum.h"

// ****************************************************************************************************************** //
// **********                                 STATIC METHODS AND VARIABLES                                 ********** //
// ****************************************************************************************************************** //

QString GestureDirectionEnum::getValue(GestureDirection gdEnum)
{
    GestureDirectionEnum GestureDirectionEnum;
    int index = GestureDirectionEnum.metaObject()->indexOfEnumerator("GestureDirection");
    QMetaEnum metaEnum = GestureDirectionEnum.metaObject()->enumerator(index);
    return metaEnum.valueToKey(gdEnum);
}

GestureDirectionEnum::GestureDirection GestureDirectionEnum::getEnum(
    const QString &gdString)
{
    GestureDirectionEnum GestureDirectionEnum;
    int index = GestureDirectionEnum.metaObject()->indexOfEnumerator("GestureDirection");
    QMetaEnum metaEnum = GestureDirectionEnum.metaObject()->enumerator(index);
    return (GestureDirectionEnum::GestureDirection)metaEnum.keyToValue(gdString.toStdString().c_str());
}
