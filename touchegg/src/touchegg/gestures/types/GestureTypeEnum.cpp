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
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011
 * @class  GestureTypeEnum
 */
#include "GestureTypeEnum.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

QString GestureTypeEnum::getValue(GestureType gtEnum)
{
    GestureTypeEnum gestureTypeEnum;
    int index = gestureTypeEnum.metaObject()->indexOfEnumerator("GestureType");
    QMetaEnum metaEnum = gestureTypeEnum.metaObject()->enumerator(index);
    return metaEnum.valueToKey(gtEnum);
}

GestureTypeEnum::GestureType GestureTypeEnum::getEnum(const QString& gtString)
{
    GestureTypeEnum gestureTypeEnum;
    int index = gestureTypeEnum.metaObject()->indexOfEnumerator("GestureType");
    QMetaEnum metaEnum = gestureTypeEnum.metaObject()->enumerator(index);
    return (GestureTypeEnum::GestureType)metaEnum.keyToValue(
            gtString.toStdString().c_str());
}

QStringList GestureTypeEnum::getGeisEquivalent(GestureType gt, int numFingers)
{
    switch(gt) {

    case TAP: {
        switch (numFingers) {
        case 2:
            return QStringList(GEIS_GESTURE_TYPE_TAP2);
        case 3:
            return QStringList(GEIS_GESTURE_TYPE_TAP3);
        case 4:
            return QStringList(GEIS_GESTURE_TYPE_TAP4);
        case 5:
            return QStringList(GEIS_GESTURE_TYPE_TAP5);
        default:
            return QStringList();
        }
    }

    case DRAG: {
        switch (numFingers) {
        case 2:
            return QStringList(GEIS_GESTURE_TYPE_DRAG2);
        case 3:
            return QStringList(GEIS_GESTURE_TYPE_DRAG3);
        case 4:
            return QStringList(GEIS_GESTURE_TYPE_DRAG4);
        case 5:
            return QStringList(GEIS_GESTURE_TYPE_DRAG5);
        default:
            return QStringList();
        }
    }

    case PINCH: {
        switch (numFingers) {
        case 2:
            return QStringList(GEIS_GESTURE_TYPE_PINCH2);
        case 3:
            return QStringList(GEIS_GESTURE_TYPE_PINCH3);
        case 4:
            return QStringList(GEIS_GESTURE_TYPE_PINCH4);
        case 5:
            return QStringList(GEIS_GESTURE_TYPE_PINCH5);
        default:
            return QStringList();
        }
    }

    case ROTATE: {
        switch (numFingers) {
        case 2:
            return QStringList(GEIS_GESTURE_TYPE_ROTATE2);
        case 3:
            return QStringList(GEIS_GESTURE_TYPE_ROTATE3);
        case 4:
            return QStringList(GEIS_GESTURE_TYPE_ROTATE4);
        case 5:
            return QStringList(GEIS_GESTURE_TYPE_ROTATE5);
        default:
            return QStringList();
        }
    }

    case TAP_AND_HOLD: {
        switch (numFingers) {
        case 2:
            return QStringList() << GEIS_GESTURE_TYPE_TAP2
                                 << GEIS_GESTURE_TYPE_DRAG2;
        case 3:
            return QStringList() << GEIS_GESTURE_TYPE_TAP3
                                 << GEIS_GESTURE_TYPE_DRAG3;
        case 4:
            return QStringList() << GEIS_GESTURE_TYPE_TAP4
                                 << GEIS_GESTURE_TYPE_DRAG4;
        case 5:
            return QStringList() << GEIS_GESTURE_TYPE_TAP5
                                 << GEIS_GESTURE_TYPE_DRAG5;
        default:
            return QStringList();
        }
    }

    case DOUBLE_TAP: {
        switch (numFingers) {
        case 2:
            return QStringList(GEIS_GESTURE_TYPE_TAP2);
        case 3:
            return QStringList(GEIS_GESTURE_TYPE_TAP3);
        case 4:
            return QStringList(GEIS_GESTURE_TYPE_TAP4);
        case 5:
            return QStringList(GEIS_GESTURE_TYPE_TAP5);
        default:
            return QStringList();
        }
    }

    default:
        return QStringList();
    }
}
