/**
 * @file /src/touchegg/gestures/implementations/TwoFingersTapAndHold.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  TwoFingersTapAndHold
 * @author José Expósito
 */
#include "TwoFingersTapAndHold.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

TwoFingersTapAndHold::TwoFingersTapAndHold(GestureTypeEnum::GestureType type,
        GeisGestureId id, const QHash<QString, QVariant>& attrs)
        : Gesture(type, id, attrs) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool TwoFingersTapAndHold::isThisGesture(const QHash<QString, QVariant>& attrs) {
    // "gesture name" = "Drag"
    if(!attrs.contains("gesture name"))
        return false;

    if(attrs.value("gesture name", "") != "Drag")
        return false;

    // touches = 2
    if(!attrs.contains("touches"))
        return false;

    if(attrs.value("touches", -1) != 2)
        return false;

    return true;
}
