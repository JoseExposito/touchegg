/**
 * @file /src/touchegg/gestures/implementations/OneFingerTapAndHold.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  OneFingerTapAndHold
 * @author José Expósito
 */
#include "OneFingerTapAndHold.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

OneFingerTapAndHold::OneFingerTapAndHold(GestureTypeEnum::GestureType type,
        GeisGestureId id, const QHash<QString, QVariant>& attrs)
        : Gesture(type, id, attrs) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool OneFingerTapAndHold::isThisGesture(
        const QHash<QString, QVariant>& attrs) {
    // "gesture name" = "Drag"
    if(!attrs.contains("gesture name"))
        return false;

    if(attrs.value("gesture name", "") != "Drag")
        return false;

    // touches = 1
    if(!attrs.contains("touches"))
        return false;

    if(attrs.value("touches", -1) != 1)
        return false;

    return true;
}
