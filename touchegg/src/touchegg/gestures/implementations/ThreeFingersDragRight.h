/**
 * @file /src/touchegg/gestures/implementations/ThreeFingersDragRight.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ThreeFingersDragRight
 * @author José Expósito
 */
#ifndef THREEFINGERSDRAGRIGHT_H
#define THREEFINGERSDRAGRIGHT_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/gestures/implementations/Gesture.h"
#include "src/touchegg/actions/implementations/Action.h"


/**
 * @~spanish
 * Arrastrar tres dedos hacia abajo.
 *
 * @~english
 * Drag three fingers down.
 */
class ThreeFingersDragRight : public Gesture {

    public:

        /**
         * @~spanish
         * Crea un gesto con las propiedades indicadas.
         * @param type   Tipo del gesto.
         * @param id     ID del gesto.
         * @param attrs  Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         *
         * @~english
         * Creates a gesture with the specified properties.
         * @param type   Gesture type.
         * @param id     Gesture ID.
         * @param attrs  Gesture attributes, where the key is the name of the
         *        attribute (ie "focus x", "touches") and the value the value of
         *        the attribute.
          */
        ThreeFingersDragRight(GestureTypeEnum::GestureType type, GeisGestureId id,
                const QHash<QString, QVariant>& attrs);

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Indica si los atributos dados definen este gesto.
         * @param attrs Los atributos.
         * @return Si lo definen o no.
         *
         * @~english
         * Indicates if the given attributes defines this gesture.
         * @param attrs The attributes.
         * @return If it define the gesture or not.
         */
        static bool isThisGesture(const QHash<QString, QVariant>& attrs);

};

#endif // THREEFINGERSDRAGRIGHT_H
