/**
 * @file /src/touchegg-gui/logic/type/GestureTypeEnum.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureTypeEnum
 * @author José Expósito
 */
#ifndef GESTURETYPEENUM_H
#define GESTURETYPEENUM_H

#include "src/touchegg-gui/util/Include.h"

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
            ONE_FINGER_TAP,
            TWO_FINGERS_TAP,
            THREE_FINGERS_TAP,
            FOUR_FINGERS_TAP,
            FIVE_FINGERS_TAP,

            THREE_FINGERS_PINCH,

            ONE_FINGER_DRAG,

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

            ONE_FINGER_TAP_AND_HOLD,
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

};

#endif // GESTURETYPEENUM_H
