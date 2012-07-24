/**
 * @file /src/touchegg/gestures/implementation/Gesture.h
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
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011 - 2012
 * @class  Gesture
 */
#ifndef GESTURE_H
#define GESTURE_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/gestures/types/GestureTypeEnum.h"
#include "src/touchegg/gestures/types/GestureDirectionEnum.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * Class that should inherit all the gestures.
 */
class Gesture
{

public:

    /**
     * Creates a gesture with the specified properties.
     * @param type   Gesture type.
     * @param numFingers Number of fingers used by the gesture.
     * @param dir Direction of the gesture.
     * @param id Gesture ID.
     * @param attrs Gesture attributes, where the key is the name of the attribute (ie "focus x", "touches") and the
     *        value the value of the attribute.
     */
    Gesture(GestureTypeEnum::GestureType type, int numFingers, GestureDirectionEnum::GestureDirection dir, int id,
            const QHash<QString, QVariant>& attrs);

    /**
     * Destructor.
     */
    ~Gesture();

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Is called when the gesture is started.
     */
    void start() const;

    /**
     * Is called when the gesture is updated.
     */
    void update() const;

    /**
     * Is called when the gesture is finished.
     */
    void finish() const;

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Returns the gesture type.
     * @return The type.
     */
    GestureTypeEnum::GestureType getType() const;

    /**
     * Returns the number of fingers used by the gesture.
     * @return The number of fingers.
     */
    int getNumFingers() const;

    /**
     * Returns the direction of the gesture.
     * @return The direction.
     */
    GestureDirectionEnum::GestureDirection getDirection() const;

    /**
     * Returns the gesture ID.
     * @return The ID.
     */
    int getId() const;

    /**
     * Returns the gesture attributes.
     * @return The attributes.
     */
    const QHash<QString, QVariant>& getAttrs() const;

    /**
     * Returns the gesture action.
     * @return The action.
     */
    const Action *getAction() const;

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Sets the gesture type.
     * @param type The type.
     */
    void setType(GestureTypeEnum::GestureType type);

    /**
     * Sets the number of fingers used by the gesture.
     * @return The number of fingers.
     */
    void setNumFingers(int numFingers);

    /**
     * Sets the direction of the gesture.
     * @return The direction.
     */
    void setDirection(GestureDirectionEnum::GestureDirection dir);

    /**
     * Sets the gesture ID.
     * @param id The ID.
     */
    void setId(int id);

    /**
     * Sets the gesture attributes.
     * @param attrs The attributes.
     */
    void setAttrs(const QHash<QString, QVariant>& attrs);

    /**
     * Sets the action to be executed by gesture.
     * @param action The action.
     */
    void setAction(Action *action);

private:

    /**
     * Gesture type.
     */
    GestureTypeEnum::GestureType type;

    /**
     * Number of fingers used by the gesture.
     */
    int numFingers;

    /**
     * Direction of the gesture.
     */
    GestureDirectionEnum::GestureDirection dir;

    /**
     * Gesture ID.
     */
    int id;

    /**
     * Gesture attributes, where the key is the name of the attribute (ie
     * "focus x", "touches") and the value the value of the attribute.
     */
    QHash<QString, QVariant> attrs;

    /**
     * Action associated to the gesture.
     */
    Action *action;

};

#endif // GESTURE_H
