/**
 * @file /src/touchegg/gestures/implementations/TwoFingersDragLeft.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  TwoFingersDragLeft
 * @author José Expósito
 */
#include "TwoFingersDragLeft.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

TwoFingersDragLeft::TwoFingersDragLeft(GestureTypeEnum::GestureType type,
        GeisGestureId id, const QHash<QString, QVariant>& attrs)
        : Gesture(type, id, attrs) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool TwoFingersDragLeft::isThisGesture(const QHash<QString, QVariant>& attrs) {
    // GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME = "Drag"
    if(!attrs.contains(GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME))
        return false;

    if(attrs.value(GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME, "") != "Drag")
        return false;

    // touches = 2
    if(!attrs.contains("touches"))
        return false;

    if(attrs.value("touches", -1) != 2)
        return false;

    // delta x < 0 && delta y = 0
    if(!attrs.contains("delta y") || !attrs.contains("delta x"))
        return false;

    return attrs.value("delta x").toFloat() < 0
        && attrs.value("delta y").toFloat() == 0;

}
