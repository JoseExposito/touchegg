/**
 * @file /src/touchegg/gestures/implementations/FourFingersTapAndHold.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  FourFingersTapAndHold
 * @author José Expósito
 */
#include "FourFingersTapAndHold.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

FourFingersTapAndHold::FourFingersTapAndHold(GestureTypeEnum::GestureType type,
        GeisGestureId id, const QHash<QString, QVariant>& attrs)
        : Gesture(type, id, attrs) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool FourFingersTapAndHold::isThisGesture(
        const QHash<QString, QVariant>& attrs) {
    // GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME = "Drag"
    if(!attrs.contains(GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME))
        return false;

    if(attrs.value(GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME, "") != "Drag")
        return false;

    // touches = 4
    if(!attrs.contains("touches"))
        return false;

    if(attrs.value("touches", -1) != 4)
        return false;

    return true;
}
