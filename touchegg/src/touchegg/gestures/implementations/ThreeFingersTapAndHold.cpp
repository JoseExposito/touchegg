/**
 * @file /src/touchegg/gestures/implementations/ThreeFingersTapAndHold.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ThreeFingersTapAndHold
 * @author José Expósito
 */
#include "ThreeFingersTapAndHold.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ThreeFingersTapAndHold::ThreeFingersTapAndHold(
        GestureTypeEnum::GestureType type, GeisGestureId id,
        const QHash<QString, QVariant>& attrs)
        : Gesture(type, id, attrs) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool ThreeFingersTapAndHold::isThisGesture(
        const QHash<QString, QVariant>& attrs) {
    // GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME = "Drag"
    if(!attrs.contains(GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME))
        return false;

    if(attrs.value(GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME, "") != "Drag")
        return false;

    // touches = 3
    if(!attrs.contains("touches"))
        return false;

    if(attrs.value("touches", -1) != 3)
        return false;

    return true;
}
