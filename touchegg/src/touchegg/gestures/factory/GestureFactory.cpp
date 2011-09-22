/**
 * @file /src/touchegg/gestures/factory/GestureFactory.cpp
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 3 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 *
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011
 * @class  GestureFactory
 */
#include "GestureFactory.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

GestureFactory *GestureFactory::instance = NULL;

GestureFactory *GestureFactory::getInstance()
{
    if (GestureFactory::instance == NULL)
        GestureFactory::instance = new GestureFactory();

    return GestureFactory::instance;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

Gesture *GestureFactory::createSimpleGesture(const QString &type, int id,
        QHash<QString, QVariant> attrs)
{
    int numFingers = attrs.value(GEIS_GESTURE_ATTRIBUTE_TOUCHES).toInt();

    // TAP
    if (type == GEIS_GESTURE_TYPE_TAP1
            || type == GEIS_GESTURE_TYPE_TAP2
            || type == GEIS_GESTURE_TYPE_TAP3
            || type == GEIS_GESTURE_TYPE_TAP4
            || type == GEIS_GESTURE_TYPE_TAP5) {
        return new Gesture(GestureTypeEnum::TAP, numFingers,
                GestureDirectionEnum::NO_DIRECTION, id, attrs);

        // DRAG
    } else if (type == GEIS_GESTURE_TYPE_DRAG1
            || type == GEIS_GESTURE_TYPE_DRAG2
            || type == GEIS_GESTURE_TYPE_DRAG3
            || type == GEIS_GESTURE_TYPE_DRAG4
            || type == GEIS_GESTURE_TYPE_DRAG5) {
        // UP
        if (attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() < 0)
            return new Gesture(GestureTypeEnum::DRAG, numFingers,
                    GestureDirectionEnum::UP, id, attrs);

        // DOWN
        if (attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() > 0)
            return new Gesture(GestureTypeEnum::DRAG, numFingers,
                    GestureDirectionEnum::DOWN, id, attrs);

        // LEFT
        if (attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() < 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::DRAG, numFingers,
                    GestureDirectionEnum::LEFT, id, attrs);

        // RIGHT
        if (attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() > 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::DRAG, numFingers,
                    GestureDirectionEnum::RIGHT, id, attrs);

        // PINCH
    } else if (type == GEIS_GESTURE_TYPE_PINCH1
            || type == GEIS_GESTURE_TYPE_PINCH2
            || type == GEIS_GESTURE_TYPE_PINCH3
            || type == GEIS_GESTURE_TYPE_PINCH4
            || type == GEIS_GESTURE_TYPE_PINCH5) {
        // IN
        if (attrs.value(GEIS_GESTURE_ATTRIBUTE_RADIUS_DELTA).toFloat() < 0)
            return new Gesture(GestureTypeEnum::PINCH, numFingers,
                    GestureDirectionEnum::IN, id, attrs);

        // OUT
        if (attrs.value(GEIS_GESTURE_ATTRIBUTE_RADIUS_DELTA).toFloat() > 0)
            return new Gesture(GestureTypeEnum::PINCH, numFingers,
                    GestureDirectionEnum::OUT, id, attrs);

        // ROTATE
    } else if (type == GEIS_GESTURE_TYPE_ROTATE1
            || type == GEIS_GESTURE_TYPE_ROTATE2
            || type == GEIS_GESTURE_TYPE_ROTATE3
            || type == GEIS_GESTURE_TYPE_ROTATE4
            || type == GEIS_GESTURE_TYPE_ROTATE5) {
        // LEFT
        if (attrs.value(GEIS_GESTURE_ATTRIBUTE_ANGLE_DELTA).toFloat() < 0)
            return new Gesture(GestureTypeEnum::ROTATE, numFingers,
                    GestureDirectionEnum::LEFT, id, attrs);

        // RIGHT
        if (attrs.value(GEIS_GESTURE_ATTRIBUTE_ANGLE_DELTA).toFloat() > 0)
            return new Gesture(GestureTypeEnum::ROTATE, numFingers,
                    GestureDirectionEnum::RIGHT, id, attrs);

        // UNKNOWN GESTURE
    } else {
        qDebug() << "[+] Unknown gesture:";
        qDebug() << "\tName -> " << attrs.value(
                GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME).toString();
        qDebug() << "\tNumber of fingers-> " << attrs.value(
                GEIS_GESTURE_ATTRIBUTE_TOUCHES).toInt();
    }

    return NULL;
}

Gesture *GestureFactory::createComposedGesture(const QString &type, int id,
        QHash<QString, QVariant> attrs)
{
    int numFingers = attrs.value(GEIS_GESTURE_ATTRIBUTE_TOUCHES).toInt();

    // TAP & HOLD
    if (type == GEIS_GESTURE_TYPE_DRAG1
            || type == GEIS_GESTURE_TYPE_DRAG2
            || type == GEIS_GESTURE_TYPE_DRAG3
            || type == GEIS_GESTURE_TYPE_DRAG4
            || type == GEIS_GESTURE_TYPE_DRAG5) {

        // UP
        if (attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() < 0)
            return new Gesture(GestureTypeEnum::TAP_AND_HOLD, numFingers,
                    GestureDirectionEnum::UP, id, attrs);

        // DOWN
        if (attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() > 0)
            return new Gesture(GestureTypeEnum::TAP_AND_HOLD, numFingers,
                    GestureDirectionEnum::DOWN, id, attrs);

        // LEFT
        if (attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() < 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::TAP_AND_HOLD, numFingers,
                    GestureDirectionEnum::LEFT, id, attrs);

        // RIGHT
        if (attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() > 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::TAP_AND_HOLD, numFingers,
                    GestureDirectionEnum::RIGHT, id, attrs);

        // DOUBLE TAP
    } else if (type == GEIS_GESTURE_TYPE_TAP1
            || type == GEIS_GESTURE_TYPE_TAP2
            || type == GEIS_GESTURE_TYPE_TAP3
            || type == GEIS_GESTURE_TYPE_TAP4
            || type == GEIS_GESTURE_TYPE_TAP5) {
        return new Gesture(GestureTypeEnum::DOUBLE_TAP, numFingers,
                GestureDirectionEnum::NO_DIRECTION, id, attrs);

        // UNKNOWN GESTURE
    } else {
        qDebug() << "[+] Unknown gesture:";
        qDebug() << "\tName -> " << attrs.value(
                GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME).toString();
        qDebug() << "\tNumber of fingers-> " << attrs.value(
                GEIS_GESTURE_ATTRIBUTE_TOUCHES).toInt();
    }

    return NULL;
}
