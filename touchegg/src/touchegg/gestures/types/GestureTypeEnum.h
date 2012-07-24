/**
 * @file src/touchegg/gestures/types/GestureTypeEnum.h
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
 * @class  GestureTypeEnum
 */
#ifndef GESTURETYPEENUM_H
#define GESTURETYPEENUM_H

#include "src/touchegg/util/Include.h"

/**
 * Contains a enumeradted type with supported gestures.
 */
class GestureTypeEnum : public QObject
{

    Q_OBJECT
    Q_ENUMS(GestureType)

public:

    /**
     * Enumerated type with supported gestures.
     */
    enum GestureType {
        TAP,
        DRAG,
        PINCH,
        ROTATE,
        TAP_AND_HOLD,
        DOUBLE_TAP
    };

    /**
     * Converts the enum to QString.
     * @return The QString.
     */
    static QString getValue(GestureType gtEnum);

    /**
     * Converts the indicated QString to the equivalent enum type.
     * @return The enum type.
     */
    static GestureType getEnum(const QString &gtString);

    /**
     * Returns a list with the equivalents uTouch-GEIS gestures to the indicated gesture, if it doesn't have equivalent,
     * returns an empty list.
     * For example, the equivalent of a tap_and_hold gesture is {GEIS_GESTURE_TAP, GEIS_GESTURE_DRAG}.
     * @param  gt The gesture.
     * @return The equivalent.
     */
    static QStringList getGeisEquivalent(GestureType gt);

};

#endif // GESTURETYPEENUM_H
