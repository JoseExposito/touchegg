/**
 * @file src/touchegg/gestures/types/GestureTypeEnum.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureTypeEnum
 * @author José Expósito
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
class GestureTypeEnum : public QObject {

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
            // TAP
            TWO_FINGERS_TAP,
            THREE_FINGERS_TAP,
            FOUR_FINGERS_TAP,
            FIVE_FINGERS_TAP,

            // PINCH
            TWO_FINGERS_PINCH,
            THREE_FINGERS_PINCH,
            FOUR_FINGERS_PINCH,
            FIVE_FINGERS_PINCH,

            // DRAG
            TWO_FINGERS_DRAG_UP,
            TWO_FINGERS_DRAG_DOWN,
            TWO_FINGERS_DRAG_LEFT,
            TWO_FINGERS_DRAG_RIGHT,

            THREE_FINGERS_DRAG_UP,
            THREE_FINGERS_DRAG_DOWN,
            THREE_FINGERS_DRAG_LEFT,
            THREE_FINGERS_DRAG_RIGHT,

            FOUR_FINGERS_DRAG_UP,
            FOUR_FINGERS_DRAG_DOWN,
            FOUR_FINGERS_DRAG_LEFT,
            FOUR_FINGERS_DRAG_RIGHT,

            FIVE_FINGERS_DRAG_UP,
            FIVE_FINGERS_DRAG_DOWN,
            FIVE_FINGERS_DRAG_LEFT,
            FIVE_FINGERS_DRAG_RIGHT,

            // TAP & HOLD
            TWO_FINGERS_TAP_AND_HOLD,
            THREE_FINGERS_TAP_AND_HOLD,
            FOUR_FINGERS_TAP_AND_HOLD,
            FIVE_FINGERS_TAP_AND_HOLD
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
         * gesto indicado, si no tiene devuelve una lista vacía.
         * Por ejemplo, el equivalente de TWO_FINGERS_TAP_AND_HOLD es
         * {GEIS_GESTURE_TYPE_TAP2, GEIS_GESTURE_TYPE_DRAG2}.
         * @param  gt El gesto.
         * @return Su equivalente.
         *
         * @~english
         * Returns a list with the equivalents uTouch-GEIS gestures to the
         * indicated gesture, if it doesn't have equivalent, returns an empty
         * list.
         * For example, the equivalent of TWO_FINGERS_TAP_AND_HOLD is
         * {GEIS_GESTURE_TYPE_TAP2, GEIS_GESTURE_TYPE_DRAG2}.
         * @param  gt The gesture.
         * @return The equivalent.
         */
        static QStringList getGeisEquivalent(GestureType gt);

};

#endif // GESTURETYPEENUM_H
