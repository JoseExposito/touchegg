/**
 * @file src/touchegg/gestures/types/GestureTypeEnum.cpp
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
 * @class  GestureTypeEnum
 */
#include "GestureTypeEnum.h"

// ****************************************************************************************************************** //
// **********                                 STATIC METHODS AND VARIABLES                                 ********** //
// ****************************************************************************************************************** //

QString GestureTypeEnum::getValue(GestureType gtEnum)
{
    GestureTypeEnum gestureTypeEnum;
    int index = gestureTypeEnum.metaObject()->indexOfEnumerator("GestureType");
    QMetaEnum metaEnum = gestureTypeEnum.metaObject()->enumerator(index);
    return metaEnum.valueToKey(gtEnum);
}

GestureTypeEnum::GestureType GestureTypeEnum::getEnum(const QString &gtString)
{
    GestureTypeEnum gestureTypeEnum;
    int index = gestureTypeEnum.metaObject()->indexOfEnumerator("GestureType");
    QMetaEnum metaEnum = gestureTypeEnum.metaObject()->enumerator(index);
    return (GestureTypeEnum::GestureType)metaEnum.keyToValue(gtString.toStdString().c_str());
}

QStringList GestureTypeEnum::getGeisEquivalent(GestureType gt)
{
    switch (gt) {

    case TAP:
        return QStringList(GEIS_GESTURE_TAP);

    case DRAG:
        return QStringList(GEIS_GESTURE_DRAG);

    case PINCH:
        return QStringList(GEIS_GESTURE_PINCH);

    case ROTATE:
        return QStringList(GEIS_GESTURE_ROTATE);

    case TAP_AND_HOLD:
        return QStringList() << GEIS_GESTURE_TAP << GEIS_GESTURE_DRAG;

    case DOUBLE_TAP:
        return QStringList(GEIS_GESTURE_TAP);

    default:
        return QStringList();
    }
}
