/**
 * @file src/touchegg/gestures/types/GestureTypeEnum.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureTypeEnum
 * @author José Expósito
 */
#include "GestureTypeEnum.h"


// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

QString GestureTypeEnum::getValue(GestureType gtEnum) {
    GestureTypeEnum gestureTypeEnum;
    int index = gestureTypeEnum.metaObject()->indexOfEnumerator("GestureType");
    QMetaEnum metaEnum = gestureTypeEnum.metaObject()->enumerator(index);
    return metaEnum.valueToKey(gtEnum);
}

GestureTypeEnum::GestureType GestureTypeEnum::getEnum(const QString& gtString) {
    GestureTypeEnum gestureTypeEnum;
    int index = gestureTypeEnum.metaObject()->indexOfEnumerator("GestureType");
    QMetaEnum metaEnum = gestureTypeEnum.metaObject()->enumerator(index);
    return (GestureTypeEnum::GestureType)metaEnum.keyToValue(
            gtString.toStdString().c_str());
}

QStringList GestureTypeEnum::getGeisEquivalent(GestureType gt) {
    switch(gt) {
    case TWO_FINGERS_TAP:
        return QStringList(GEIS_GESTURE_TYPE_TAP2);
    case THREE_FINGERS_TAP:
        return QStringList(GEIS_GESTURE_TYPE_TAP3);
    case FOUR_FINGERS_TAP:
        return QStringList(GEIS_GESTURE_TYPE_TAP4);
    case FIVE_FINGERS_TAP:
        return QStringList(GEIS_GESTURE_TYPE_TAP5);

    case TWO_FINGERS_PINCH:
        return QStringList(GEIS_GESTURE_TYPE_PINCH2);
    case THREE_FINGERS_PINCH:
        return QStringList(GEIS_GESTURE_TYPE_PINCH3);
    case FOUR_FINGERS_PINCH:
        return QStringList(GEIS_GESTURE_TYPE_PINCH4);
    case FIVE_FINGERS_PINCH:
        return QStringList(GEIS_GESTURE_TYPE_PINCH5);

    case TWO_FINGERS_DRAG_UP:
    case TWO_FINGERS_DRAG_DOWN:
    case TWO_FINGERS_DRAG_LEFT:
    case TWO_FINGERS_DRAG_RIGHT:
        return QStringList(GEIS_GESTURE_TYPE_DRAG2);

    case THREE_FINGERS_DRAG_UP:
    case THREE_FINGERS_DRAG_DOWN:
    case THREE_FINGERS_DRAG_LEFT:
    case THREE_FINGERS_DRAG_RIGHT:
        return QStringList(GEIS_GESTURE_TYPE_DRAG3);

    case FOUR_FINGERS_DRAG_UP:
    case FOUR_FINGERS_DRAG_DOWN:
    case FOUR_FINGERS_DRAG_LEFT:
    case FOUR_FINGERS_DRAG_RIGHT:
        return QStringList(GEIS_GESTURE_TYPE_DRAG4);

    case FIVE_FINGERS_DRAG_UP:
    case FIVE_FINGERS_DRAG_DOWN:
    case FIVE_FINGERS_DRAG_LEFT:
    case FIVE_FINGERS_DRAG_RIGHT:
        return QStringList(GEIS_GESTURE_TYPE_DRAG5);

    case TWO_FINGERS_TAP_AND_HOLD: {
        QStringList tah2(GEIS_GESTURE_TYPE_TAP2);
        tah2.append(GEIS_GESTURE_TYPE_DRAG2);
        return tah2;
    }
    case THREE_FINGERS_TAP_AND_HOLD: {
        QStringList tah3(GEIS_GESTURE_TYPE_TAP3);
        tah3.append(GEIS_GESTURE_TYPE_DRAG3);
        return tah3;
    }
    case FOUR_FINGERS_TAP_AND_HOLD: {
        QStringList tah4(GEIS_GESTURE_TYPE_TAP4);
        tah4.append(GEIS_GESTURE_TYPE_DRAG4);
        return tah4;
    }
    case FIVE_FINGERS_TAP_AND_HOLD: {
        QStringList tah5(GEIS_GESTURE_TYPE_TAP5);
        tah5.append(GEIS_GESTURE_TYPE_DRAG5);
        return tah5;
    }

    default:
        return QStringList();
    }
}
