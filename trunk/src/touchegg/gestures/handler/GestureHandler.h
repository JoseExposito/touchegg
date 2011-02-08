/**
 * @file /src/touchegg/gestures/handler/GestureHandler.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureHandler
 * @author José Expósito
 */
#ifndef GESTUREHANDLER_H
#define GESTUREHANDLER_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/config/Config.h"
#include "src/touchegg/gestures/factory/GestureFactory.h"
#include "src/touchegg/actions/factory/ActionFactory.h"

/**
 * @~spanish
 * Clase que recibe los gestos, los procesa y ejecuta la acción correspondiente.
 *
 * @~english
 * Class that receives the gestures, processes it and execute the corresponding
 * action.
 */
class GestureHandler : public QThread {

    Q_OBJECT

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
         * Timer que ejecuta los taps siempre que el gesto no resulte ser un
         * tap&hold.
         *
         * @~english
         * Timer that running the taps always that the gesture does not prove
         * to be a tap&hold.
         */
        QTimer* timerTap;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Factoría para crear los gestos.
         *
         * @~english
         * Factory to create gestures.
         */
        GestureFactory* gestureFact;

        /**
         * @~spanish
         * Factoría para crear las acciones.
         *
         * @~english
         * Factory to create gestures.
         */
        ActionFactory* actionFact;

        /**
         * @~spanish
         * Provee acceso a la configurración.
         *
         * @~english
         * Provides access to configurración.
         */
        Config* config;

    private slots:

        /**
         * @~spanish
         * Ejecuta los taps que no han resultado ser un tap&hold.
         *
         * @~english
         * Run the taps that have not proven to be a tap&hold.
         */
        void executeTap();

    public:

        /**
         * @~spanish
         * Constructor.
         *
         * @~english
         * Constructor.
         */
        GestureHandler();

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * Destructor.
         */
        virtual ~GestureHandler();

    public slots:

        /**
         * @~spanish
         * Ejecuta el gesto indicado.
         * @param type  Tipo del gesto.
         * @param id    ID del gesto.
         * @param attrs Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         *
         * @~english
         * Runs the indicated gesture.
         * @param type  Gesture type.
         * @param id    Gesture ID.
         * @param attrs Gesture attributes, where the key is the name of the
         *        attribute (ie "focus x", "touches") and the value the value of
         *        the attribute.
         */
        void executeGestureStart(GeisGestureType type, GeisGestureId id,
                const QHash<QString, QVariant>& attrs);

        /**
         * @~spanish
         * Ejecuta el gesto indicado.
         * @param type  Tipo del gesto.
         * @param id    ID del gesto.
         * @param attrs Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         *
         * @~english
         * Runs the indicated gesture.
         * @param type  Gesture type.
         * @param id    Gesture ID.
         * @param attrs Gesture attributes, where the key is the name of the
         *        attribute (ie "focus x", "touches") and the value the value of
         *        the attribute.
         */
        void executeGestureUpdate(GeisGestureType type, GeisGestureId id,
                const QHash<QString, QVariant>& attrs);

        /**
         * @~spanish
         * Ejecuta el gesto indicado.
         * @param type  Tipo del gesto.
         * @param id    ID del gesto.
         * @param attrs Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         *
         * @~english
         * Runs the indicated gesture.
         * @param type  Gesture type.
         * @param id    Gesture ID.
         * @param attrs Gesture attributes, where the key is the name of the
         *        attribute (ie "focus x", "touches") and the value the value of
         *        the attribute.
         */
        void executeGestureFinish(GeisGestureType type, GeisGestureId id,
                const QHash<QString, QVariant>& attrs);

};

#endif // GESTUREHANDLER_H
