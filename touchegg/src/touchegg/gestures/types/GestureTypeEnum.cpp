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
