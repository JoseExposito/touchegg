/**
 * @file /src/touchegg/gestures/implementations/ThreeFingersDragUp.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ThreeFingersDragUp
 * @author José Expósito
 */
#include "ThreeFingersDragUp.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ThreeFingersDragUp::ThreeFingersDragUp(GestureTypeEnum::GestureType type,
        GeisGestureId id, const QHash<QString, QVariant>& attrs)
        : Gesture(type, id, attrs) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool ThreeFingersDragUp::isThisGesture(const QHash<QString, QVariant>& attrs) {
    // "gesture name" = "Drag"
    if(!attrs.contains("gesture name"))
        return false;

    if(attrs.value("gesture name", "") != "Drag")
        return false;

    // touches = 3
    if(!attrs.contains("touches"))
        return false;

    if(attrs.value("touches", -1) != 3)
        return false;

    // delta x = 0 && delta y < 0
    if(!attrs.contains("delta y") || !attrs.contains("delta x"))
        return false;

    return attrs.value("delta x").toFloat() == 0
        && attrs.value("delta y").toFloat() < 0;
}
