/**
 * @file /src/touchegg/gestures/implementations/TwoFingersTap.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  TwoFingersTap
 * @author José Expósito
 */
#include "TwoFingersTap.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

TwoFingersTap::TwoFingersTap(GestureTypeEnum::GestureType type,
        GeisGestureId id, const QHash<QString, QVariant>& attrs)
        : Gesture(type, id, attrs) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool TwoFingersTap::isThisGesture(const QHash<QString, QVariant>& attrs) {
    // GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME = "Tap"
    if(!attrs.contains(GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME))
        return false;

    if(attrs.value(GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME, "") != "Tap")
        return false;

    // touches = 2
    if(!attrs.contains("touches"))
        return false;

    if(attrs.value("touches", -1) != 2)
        return false;


    return true;
}

