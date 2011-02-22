/**
 * @file /src/touchegg/gestures/implementations/ThreeFingersPinch.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ThreeFingersPinch
 * @author José Expósito
 */
#include "ThreeFingersPinch.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ThreeFingersPinch::ThreeFingersPinch(GestureTypeEnum::GestureType type,
        GeisGestureId id, const QHash<QString, QVariant>& attrs)
        : Gesture(type, id, attrs) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool ThreeFingersPinch::isThisGesture(const QHash<QString, QVariant>& attrs) {
    // "gesture name" = "Pinch"
    if(!attrs.contains("gesture name"))
        return false;

    if(attrs.value("gesture name", "") != "Pinch")
        return false;

    // touches = 3
    if(!attrs.contains("touches"))
        return false;

    if(attrs.value("touches", -1) != 3)
        return false;

    return true;
}
