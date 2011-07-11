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
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011
 * @class  GestureTypeEnum
 */
#ifndef GESTURETYPEENUM_H
#define GESTURETYPEENUM_H

#include "src/touchegg/util/Include.h"

/**
 * @~spanish
 * Contiene un tipo enumerado con los gestos soportados.
 *
 * @~english
 * Contains a enumeradted type with supported gestures.
 */
class GestureTypeEnum : public QObject
{

    Q_OBJECT
    Q_ENUMS(GestureType);

public:

    /**
     * @~spanish
     * Tipo enumerado con los gestos soportados.
     *
     * @~english
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
     * @~spanish
     * Convierte el tipo enumedrado a QString.
     * @return El QString
     *
     * @~english
     * Converts the enum to QString.
     * @return The QString.
     */
    static QString getValue(GestureType gtEnum);

    /**
     * @~spanish
     * Convierte el QString indicado en su equivalente tipo enumedrado.
     * @return El tipo enumerado
     *
     * @~english
     * Converts the indicated QString to the equivalent enum type.
     * @return The enum type.
     */
    static GestureType getEnum(const QString& gtString);

    /**
     * @~spanish
     * Devuelve una lista con los gestos de uTouch-GEIS equivalentes al
     * gesto indicado, si no tiene un equivalente, devuelve una lista vacía.
     * Por ejemplo, el equivalente de un gesto tap_and_hold con 2 dedos es
     * {GEIS_GESTURE_TYPE_TAP2, GEIS_GESTURE_TYPE_DRAG2}.
     * @param  gt El gesto.
     * @param  numFingers Número de dedos usados en el gesto.
     * @return Su equivalente.
     *
     * @~english
     * Returns a list with the equivalents uTouch-GEIS gestures to the
     * indicated gesture, if it doesn't have equivalent, returns an empty
     * list.
     * For example, the equivalent of a tap_and_hold gesture with 2 fingers
     * is {GEIS_GESTURE_TYPE_TAP2, GEIS_GESTURE_TYPE_DRAG2}.
     * @param  gt The gesture.
     * @param  numFingers Number of fingers used in the gesture.
     * @return The equivalent.
     */
    static QStringList getGeisEquivalent(GestureType gt, int numFingers);

};

#endif // GESTURETYPEENUM_H
