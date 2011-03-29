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

    QString type = attrs.value(GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME).toString();

    //--------------------------------------------------------------------------

    if(type == GEIS_GESTURE_TYPE_TAP2)
        return new Gesture(GestureTypeEnum::TWO_FINGERS_TAP, id, attrs);

    if(type == GEIS_GESTURE_TYPE_TAP3)
        return new Gesture(GestureTypeEnum::THREE_FINGERS_TAP, id, attrs);

    if(type == GEIS_GESTURE_TYPE_TAP4)
        return new Gesture(GestureTypeEnum::FOUR_FINGERS_TAP, id, attrs);

    if(type == GEIS_GESTURE_TYPE_TAP5)
        return new Gesture(GestureTypeEnum::FIVE_FINGERS_TAP, id, attrs);

    //--------------------------------------------------------------------------

    if(type == GEIS_GESTURE_TYPE_PINCH2)
        return new Gesture(GestureTypeEnum::TWO_FINGERS_PINCH, id, attrs);

    if(type == GEIS_GESTURE_TYPE_PINCH3)
        return new Gesture(GestureTypeEnum::THREE_FINGERS_PINCH, id, attrs);

    if(type == GEIS_GESTURE_TYPE_PINCH4)
        return new Gesture(GestureTypeEnum::FOUR_FINGERS_PINCH, id, attrs);

    if(type == GEIS_GESTURE_TYPE_PINCH5)
        return new Gesture(GestureTypeEnum::FIVE_FINGERS_PINCH, id, attrs);

    //--------------------------------------------------------------------------

    if(type == GEIS_GESTURE_TYPE_DRAG2) {
        // TWO_FINGERS_DRAG_UP
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() < 0)
            return new Gesture(GestureTypeEnum::TWO_FINGERS_DRAG_UP,
                               id, attrs);

        // TWO_FINGERS_DRAG_DOWN
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() > 0)
            return new Gesture(GestureTypeEnum::TWO_FINGERS_DRAG_DOWN,
                               id, attrs);

        // TWO_FINGERS_DRAG_LEFT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() < 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::TWO_FINGERS_DRAG_LEFT,
                               id, attrs);

        // TWO_FINGERS_DRAG_RIGHT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() > 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::TWO_FINGERS_DRAG_RIGHT,
                               id, attrs);
    }

    if(type == GEIS_GESTURE_TYPE_DRAG3) {
        // THREE_FINGERS_DRAG_UP
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() < 0)
            return new Gesture(GestureTypeEnum::THREE_FINGERS_DRAG_UP,
                               id, attrs);

        // THREE_FINGERS_DRAG_DOWN
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() > 0)
            return new Gesture(GestureTypeEnum::THREE_FINGERS_DRAG_DOWN,
                               id, attrs);

        // THREE_FINGERS_DRAG_LEFT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() < 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::THREE_FINGERS_DRAG_LEFT,
                               id, attrs);

        // THREE_FINGERS_DRAG_RIGHT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() > 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::THREE_FINGERS_DRAG_RIGHT,
                               id, attrs);
    }

    if(type == GEIS_GESTURE_TYPE_DRAG4) {
        // FOUR_FINGERS_DRAG_UP
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() < 0)
            return new Gesture(GestureTypeEnum::FOUR_FINGERS_DRAG_UP,
                               id, attrs);

        // FOUR_FINGERS_DRAG_DOWN
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() > 0)
            return new Gesture(GestureTypeEnum::FOUR_FINGERS_DRAG_DOWN,
                               id, attrs);

        // FOUR_FINGERS_DRAG_LEFT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() < 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::FOUR_FINGERS_DRAG_LEFT,
                               id, attrs);

        // FOUR_FINGERS_DRAG_RIGHT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() > 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::FOUR_FINGERS_DRAG_RIGHT,
                               id, attrs);
    }

    if(type == GEIS_GESTURE_TYPE_DRAG5) {
        // FIVE_FINGERS_DRAG_UP
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() < 0)
            return new Gesture(GestureTypeEnum::FIVE_FINGERS_DRAG_UP,
                               id, attrs);

        // FIVE_FINGERS_DRAG_DOWN
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() > 0)
            return new Gesture(GestureTypeEnum::FIVE_FINGERS_DRAG_DOWN,
                               id, attrs);

        // FIVE_FINGERS_DRAG_LEFT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() < 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::FIVE_FINGERS_DRAG_LEFT,
                               id, attrs);

        // FIVE_FINGERS_DRAG_RIGHT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() > 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::FIVE_FINGERS_DRAG_RIGHT,
                               id, attrs);
    }

    //--------------------------------------------------------------------------

    qDebug() << "[+] Unknown gesture:";
    qDebug() << "\tName -> " << attrs.value(GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME,
                                            "Unknown name");
    return NULL;
}

Gesture* GestureFactory::createTapAndHold(GeisGestureType /*type*/,
        GeisGestureId id, QHash<QString, QVariant> attrs) {
	
	QString type = attrs.value(GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME).toString();
	
	if(type == GEIS_GESTURE_TYPE_DRAG2)
		return new Gesture(GestureTypeEnum::TWO_FINGERS_TAP_AND_HOLD,
			id, attrs);
	if(type == GEIS_GESTURE_TYPE_DRAG3)
		return new Gesture(GestureTypeEnum::THREE_FINGERS_TAP_AND_HOLD,
			id, attrs);
	if(type == GEIS_GESTURE_TYPE_DRAG4)
		return new Gesture(GestureTypeEnum::FOUR_FINGERS_TAP_AND_HOLD,
			id, attrs);
	if(type == GEIS_GESTURE_TYPE_DRAG5)
		return new Gesture(GestureTypeEnum::FIVE_FINGERS_TAP_AND_HOLD,
			id, attrs);

        return NULL;
}
