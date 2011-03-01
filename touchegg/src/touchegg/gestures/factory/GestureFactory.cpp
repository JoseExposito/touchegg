/**
 * @file /src/touchegg/gestures/factory/GestureFactory.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureFactory
 * @author José Expósito
 */
#include "GestureFactory.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

GestureFactory* GestureFactory::instance = NULL;

GestureFactory* GestureFactory::getInstance() {
    if(GestureFactory::instance == NULL)
        GestureFactory::instance = new GestureFactory();

    return GestureFactory::instance;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

Gesture* GestureFactory::createGesture(GeisGestureType /*type*/,
        GeisGestureId id, QHash<QString, QVariant> attrs) {

    //Para ver las propiedades:
    /*QHashIterator<QString, QVariant> i(attrs);
    while (i.hasNext()) {
        i.next();
        qDebug() << i.key() << i.value();
    }*/


    if(OneFingerDrag::isThisGesture(attrs)) {
        return new OneFingerDrag(GestureTypeEnum::ONE_FINGER_DRAG, id, attrs);

    //--------------------------------------------------------------------------

    } else if(OneFingerTap::isThisGesture(attrs)) {
        return new OneFingerTap(GestureTypeEnum::ONE_FINGER_TAP, id, attrs);

    } else if(TwoFingersTap::isThisGesture(attrs)) {
        return new TwoFingersTap(GestureTypeEnum::TWO_FINGERS_TAP, id, attrs);

    } else if(ThreeFingersTap::isThisGesture(attrs)) {
        return new ThreeFingersTap(GestureTypeEnum::THREE_FINGERS_TAP, id,
                attrs);

    } else if(FourFingersTap::isThisGesture(attrs)) {
        return new FourFingersTap(GestureTypeEnum::FOUR_FINGERS_TAP, id, attrs);

    } else if(FiveFingersTap::isThisGesture(attrs)) {
        return new FiveFingersTap(GestureTypeEnum::FIVE_FINGERS_TAP, id, attrs);

    //--------------------------------------------------------------------------

    } else if(ThreeFingersPinch::isThisGesture(attrs)) {
        return new ThreeFingersPinch(GestureTypeEnum::THREE_FINGERS_PINCH, id,
                attrs);

    //--------------------------------------------------------------------------

    } else if(TwoFingersDragUp::isThisGesture(attrs)) {
        return new TwoFingersDragUp(GestureTypeEnum::TWO_FINGERS_DRAG_UP, id,
                attrs);

    } else if(TwoFingersDragDown::isThisGesture(attrs)) {
        return new TwoFingersDragDown(GestureTypeEnum::TWO_FINGERS_DRAG_DOWN,
                id, attrs);

    } else if(TwoFingersDragLeft::isThisGesture(attrs)) {
        return new TwoFingersDragLeft(GestureTypeEnum::TWO_FINGERS_DRAG_LEFT,
                id, attrs);

    } else if(TwoFingersDragRight::isThisGesture(attrs)) {
        return new TwoFingersDragRight(GestureTypeEnum::TWO_FINGERS_DRAG_RIGHT,
                id, attrs);

    //--------------------------------------------------------------------------

    } else if(ThreeFingersDragUp::isThisGesture(attrs)) {
        return new ThreeFingersDragUp(GestureTypeEnum::THREE_FINGERS_DRAG_UP,
                id, attrs);

    } else if(ThreeFingersDragDown::isThisGesture(attrs)) {
        return new ThreeFingersDragDown(
                GestureTypeEnum::THREE_FINGERS_DRAG_DOWN, id, attrs);

    } else if(ThreeFingersDragLeft::isThisGesture(attrs)) {
        return new ThreeFingersDragLeft(
                GestureTypeEnum::THREE_FINGERS_DRAG_LEFT, id, attrs);

    } else if(ThreeFingersDragRight::isThisGesture(attrs)) {
        return new ThreeFingersDragRight(
                GestureTypeEnum::THREE_FINGERS_DRAG_RIGHT, id, attrs);

    //--------------------------------------------------------------------------

    } else if(FourFingersDragUp::isThisGesture(attrs)) {
        return new FourFingersDragUp(GestureTypeEnum::FOUR_FINGERS_DRAG_UP, id,
                attrs);

    } else if(FourFingersDragDown::isThisGesture(attrs)) {
        return new FourFingersDragDown(GestureTypeEnum::FOUR_FINGERS_DRAG_DOWN,
                id, attrs);

    } else if(FourFingersDragLeft::isThisGesture(attrs)) {
        return new FourFingersDragLeft(GestureTypeEnum::FOUR_FINGERS_DRAG_LEFT,
                id, attrs);

    } else if(FourFingersDragRight::isThisGesture(attrs)) {
        return new FourFingersDragRight(
                GestureTypeEnum::FOUR_FINGERS_DRAG_RIGHT, id, attrs);


    } else {
        qDebug() << attrs.value("gesture name", "Nombre desconocido");
        qDebug() << attrs.value("touches", "Nº dedos desconocido");
        return NULL;
    }
}

Gesture* GestureFactory::createTapAndHold(GeisGestureType /*type*/,
        GeisGestureId id, QHash<QString, QVariant> attrs) {
    if(OneFingerTapAndHold::isThisGesture(attrs)) {
        return new OneFingerTapAndHold(
                GestureTypeEnum::ONE_FINGER_TAP_AND_HOLD, id, attrs);

    } else if(TwoFingersTapAndHold::isThisGesture(attrs)) {
        return new TwoFingersTapAndHold(
                GestureTypeEnum::TWO_FINGERS_TAP_AND_HOLD, id, attrs);

    } else if(ThreeFingersTapAndHold::isThisGesture(attrs)) {
        return new ThreeFingersTapAndHold(
                GestureTypeEnum::THREE_FINGERS_TAP_AND_HOLD, id, attrs);

    } else if(FourFingersTapAndHold::isThisGesture(attrs)) {
        return new FourFingersTapAndHold(
                GestureTypeEnum::FOUR_FINGERS_TAP_AND_HOLD, id, attrs);

    } else if(FiveFingersTapAndHold::isThisGesture(attrs)) {
        return new FiveFingersTapAndHold(
                GestureTypeEnum::FIVE_FINGERS_TAP_AND_HOLD, id,attrs);
    } else {
        return NULL;
    }
}
