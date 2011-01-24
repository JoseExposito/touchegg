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

Gesture* GestureFactory::createGesture(GeisGestureType type, GeisGestureId id,
        QHash<QString, QVariant> attrs) {

    //Para ver las propiedades:
    /*QHashIterator<QString, QVariant> i(attrs);
    while (i.hasNext()) {
        i.next();
        qDebug() << i.key() << i.value();
    }*/

    Config* cfg = Config::getInstance();

    if(TwoFingersTap::isThisGesture(attrs)) {
        qDebug() << "TwoFingersTap";
        return new TwoFingersTap(type, id, attrs,
            cfg->getAssociatedAction(Config::TWO_FINGERS_TAP));

    } else if(ThreeFingersTap::isThisGesture(attrs)) {
        qDebug() << "ThreeFingersTap";
        return new ThreeFingersTap(type, id, attrs,
            cfg->getAssociatedAction(Config::THREE_FINGERS_TAP));

    } else if(FourFingersTap::isThisGesture(attrs)) {
        qDebug() << "FourFingersTap";
        return new FourFingersTap(type, id, attrs,
            cfg->getAssociatedAction(Config::FOUR_FINGERS_TAP));

    } else if(FiveFingersTap::isThisGesture(attrs)) {
        qDebug() << "FiveFingersTap";
        return new FiveFingersTap(type, id, attrs,
            cfg->getAssociatedAction(Config::FIVE_FINGERS_TAP));

    //--------------------------------------------------------------------------

    } else if(ThreeFingersPinch::isThisGesture(attrs)) {
        qDebug() << "ThreeFingersPinch";
        return new ThreeFingersPinch(type, id, attrs,
            cfg->getAssociatedAction(Config::THREE_FINGERS_PINCH));

    //--------------------------------------------------------------------------

    } else if(TwoFingersDragUp::isThisGesture(attrs)) {
        qDebug() << "TwoFingersDragUp";
        return new TwoFingersDragUp(type, id, attrs,
            cfg->getAssociatedAction(Config::TWO_FINGERS_DRAG_UP));

    } else if(TwoFingersDragDown::isThisGesture(attrs)) {
        qDebug() << "TwoFingersDragDown";
        return new TwoFingersDragDown(type, id, attrs,
            cfg->getAssociatedAction(Config::TWO_FINGERS_DRAG_DOWN));

    } else if(TwoFingersDragLeft::isThisGesture(attrs)) {
        qDebug() << "TwoFingersDragLeft";
        return new TwoFingersDragLeft(type, id, attrs,
            cfg->getAssociatedAction(Config::TWO_FINGERS_DRAG_LEFT));

    } else if(TwoFingersDragRight::isThisGesture(attrs)) {
        qDebug() << "TwoFingersDragRight";
        return new TwoFingersDragRight(type, id, attrs,
            cfg->getAssociatedAction(Config::TWO_FINGERS_DRAG_RIGHT));

    //--------------------------------------------------------------------------

    } else if(ThreeFingersDragUp::isThisGesture(attrs)) {
        qDebug() << "ThreeFingersDragUp";
        return new ThreeFingersDragUp(type, id, attrs,
            cfg->getAssociatedAction(Config::THREE_FINGERS_DRAG_UP));

    } else if(ThreeFingersDragDown::isThisGesture(attrs)) {
        qDebug() << "ThreeFingersDragDown";
        return new ThreeFingersDragDown(type, id, attrs,
            cfg->getAssociatedAction(Config::THREE_FINGERS_DRAG_DOWN));

    } else if(ThreeFingersDragLeft::isThisGesture(attrs)) {
        qDebug() << "ThreeFingersDragLeft";
        return new ThreeFingersDragLeft(type, id, attrs,
            cfg->getAssociatedAction(Config::THREE_FINGERS_DRAG_LEFT));

    } else if(ThreeFingersDragRight::isThisGesture(attrs)) {
        qDebug() << "ThreeFingersDragRight";
        return new ThreeFingersDragRight(type, id, attrs,
            cfg->getAssociatedAction(Config::THREE_FINGERS_DRAG_RIGHT));

    //--------------------------------------------------------------------------

    } else if(FourFingersDragUp::isThisGesture(attrs)) {
        qDebug() << "FourFingersDragUp";
        return new FourFingersDragUp(type, id, attrs,
            cfg->getAssociatedAction(Config::FOUR_FINGERS_DRAG_UP));

    } else if(FourFingersDragDown::isThisGesture(attrs)) {
        qDebug() << "FourFingersDragDown";
        return new FourFingersDragDown(type, id, attrs,
            cfg->getAssociatedAction(Config::FOUR_FINGERS_DRAG_DOWN));

    } else if(FourFingersDragLeft::isThisGesture(attrs)) {
        qDebug() << "FourFingersDragLeft";
        return new FourFingersDragLeft(type, id, attrs,
            cfg->getAssociatedAction(Config::FOUR_FINGERS_DRAG_LEFT));

    } else if(FourFingersDragRight::isThisGesture(attrs)) {
        qDebug() << "FourFingersDragRight";
        return new FourFingersDragRight(type, id, attrs,
            cfg->getAssociatedAction(Config::FOUR_FINGERS_DRAG_RIGHT));


    } else {
        //qDebug() << attrs.value("gesture name", "Nombre desconocido");
        //qDebug() << attrs.value("touches", "Nº dedos desconocido");
    }


    return NULL;
}
