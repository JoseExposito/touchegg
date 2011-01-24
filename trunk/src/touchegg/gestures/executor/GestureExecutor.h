/**
 * @file /src/touchegg/gestures/executor/GestureExecutor.h
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
#ifndef GESTUREEXECUTOR_H
#define GESTUREEXECUTOR_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/gestures/factory/GestureFactory.h"

/**
 * @~spanish
 * Clase encargada de ejecutar los gestos. Se encarga de que solo haya un único
 * gesto ejecutándose (por ejemplo para que no se haga a la vez un drag y un
 * pinch). Para crear los gestos se sirve de GestureFactory.
 *
 * @~english
 * Responsible of executing gestures. Ensures that there is only running a
 * single gesture (for example to not do both a drag and a pinch). To create
 * gestures uses GestureFactory.
 */
class GestureExecutor {

    private:

        /**
         * @~spanish
         * Gesto que se está ejecutando.
         *
         * @~english
         * Gesture that is running.
         */
        Gesture* currentGesture;

        /**
         * @~spanish
         * Timestamp del último gesto recibido. Es un hack para esquivar un bug
         * de utouch-geis.
         *
         * @~english
         * Timestamp of the last gesture received. It is a hack to avoid a
         * utouch-geis bug.
         */
        int lastTimestamp;

    public:

        /**
         * @~spanish
         * Constructor.
         *
         * @~english
         * Constructor.
         */
        GestureExecutor();

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * Destructor.
         */
        ~GestureExecutor();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Ejecuta el gesto que corresponda a los atributos pasados, ayudándose
         * de GestureFactory para crearlo.
         * @param type  Tipo del gesto.
         * @param id    ID del gesto.
         * @param attrs Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         *
         * @~english
         * Executes the gesture corresponding to attributes passed, aided by
         * GestureFactory to create it.
         * @param type  Gesture type.
         * @param id    Gesture ID.
         * @param attrs Gesture attributes, where the key is the name of the
         *        attribute (ie "focus x", "touches") and the value the value of
         *        the attribute.
         */
        void executeGestureStart(GeisGestureType type, GeisGestureId id,
            QHash<QString, QVariant> attrs);

        /**
         * @~spanish
         * Ejecuta el gesto que corresponda a los atributos pasados, ayudándose
         * de GestureFactory para crearlo.
         * @param type  Tipo del gesto.
         * @param id    ID del gesto.
         * @param attrs Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         *
         * @~english
         * Executes the gesture corresponding to attributes passed, aided by
         * GestureFactory to create it.
         * @param type  Gesture type.
         * @param id    Gesture ID.
         * @param attrs Gesture attributes, where the key is the name of the
         *        attribute (ie "focus x", "touches") and the value the value of
         *        the attribute.
         */
        void executeGestureUpdate(GeisGestureType type, GeisGestureId id,
            QHash<QString, QVariant> attrs);

        /**
         * @~spanish
         * Ejecuta el gesto que corresponda a los atributos pasados, ayudándose
         * de GestureFactory para crearlo.
         * @param type  Tipo del gesto.
         * @param id    ID del gesto.
         * @param attrs Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         *
         * @~english
         * Executes the gesture corresponding to attributes passed, aided by
         * GestureFactory to create it.
         * @param type  Gesture type.
         * @param id    Gesture ID.
         * @param attrs Gesture attributes, where the key is the name of the
         *        attribute (ie "focus x", "touches") and the value the value of
         *        the attribute.
         */
        void executeGestureFinish(GeisGestureType type, GeisGestureId id,
            QHash<QString, QVariant> attrs);

};

#endif // GESTUREEXECUTOR_H
