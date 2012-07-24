/**
 * @file /src/touchegg/gestures/factory/GestureFactory.h
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
 * @class  GestureFactory
 */
#ifndef GESTUREFACTORY_H
#define GESTUREFACTORY_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/gestures/types/GestureTypeEnum.h"
#include "src/touchegg/gestures/implementation/Gesture.h"

/**
 * Factory to create the different gestures.
 */
class GestureFactory
{

public:

    /**
     * Only method to get an instance of the class.
     * @return The single instance of the class.
     */
    static GestureFactory *getInstance();

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Creates a no-composed gesture with the specified properties.
     * IMPORTANT: Don't forget to free memory.
     * @param type  Gesture type.
     * @param id    Gesture ID.
     * @param attrs Gesture attributes, where the key is the name of the
     *        attribute (ie "focus x", "touches") and the value the value of
     *        the attribute.
     * @return The gesture.
     */
    Gesture *createSimpleGesture(const QString &type, int id, QHash<QString, QVariant> attrs);

    /**
     * Creates a composed gesture (tap&hold, double tap...) with the specified properties.
     * IMPORTANT: Don't forget to free memory.
     * @param type  Gesture type.
     * @param id    Gesture ID.
     * @param attrs Gesture attributes, where the key is the name of the attribute (ie "focus x", "touches") and the
     *        value the value of the attribute.
     * @return The gesture.
     */
    Gesture *createComposedGesture(const QString &type, int id, QHash<QString, QVariant> attrs);

private:

    /**
     * Single instance of the class.
     */
    static GestureFactory *instance;

    // Hide constructors
    GestureFactory() {}
    GestureFactory(const GestureFactory &);
    const GestureFactory &operator = (const GestureFactory &);

};

#endif // GESTUREFACTORY_H
