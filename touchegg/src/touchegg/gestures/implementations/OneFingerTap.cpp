/**
 * @file /src/touchegg/gestures/implementations/OneFingerTap.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  OneFingerTap
 * @author José Expósito
 */
#include "OneFingerTap.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

OneFingerTap::OneFingerTap(GestureTypeEnum::GestureType type,
        GeisGestureId id, const QHash<QString, QVariant>& attrs)
        : Gesture(type, id, attrs) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool OneFingerTap::isThisGesture(const QHash<QString, QVariant>& attrs) {
    // "gesture name" = "Tap"
    if(!attrs.contains("gesture name"))
        return false;

    if(attrs.value("gesture name", "") != "Tap")
        return false;

    // touches = 1
    if(!attrs.contains("touches"))
        return false;

    if(attrs.value("touches", -1) != 1)
        return false;

    return true;
}
