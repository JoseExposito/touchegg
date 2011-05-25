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
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
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

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Crea un gesto estandar con su acción.
         * @param  type  Tipo del gesto.
         * @param  id    ID del gesto.
         * @param  attrs Atributos del gestos, siendo la clave el nombre del
         *         atributo (por ejemplo "focus x", "touches"...) y el valor el
         *         valor del propio atributo.
         * @param  isTapAndHold Si es o no un gesto tap&hold.
         * @return El gesto o NULL.
         *
         * @~english
         * Create a estandar gesture with their action.
         * @param  type  Gesture type.
         * @param  id    Gesture ID.
         * @param  attrs Gesture attributes, where the key is the name of the
         *         attribute (ie "focus x", "touches") and the value the value of
         *         the attribute.
         * @param  isTapAndHold If is or not a tap&hold gesture.
         * @return The gesture or NULL.
         */
        Gesture* createGesture(GeisGestureType type, GeisGestureId id,
                const QHash<QString, QVariant>& attrs, bool isTapAndHold) const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve la ventana sobre la que se produce el gesto.
         * @param  window Ventana que nos pasa GEIS.
         * @return Dicha ventana.
         *
         * @~english
         * Returns window over the gestures is make.
         * @param  window The window that GEIS returns.
         * @return This window.
         */
        Window getGestureWindow(Window window) const;

        /**
         * @~spanish
         * Devuelve la ventana de más alto nivel de la ventana indicada.
         * @param  window La ventana.
         * @return Dicha ventana
         *
         * @~english
         * Returns the top level window of the specified window.
         * @param  window The window.
         * @return This window.
         */
        Window getTopLevelWindow(Window window) const;

        /**
         * @~spanish
         * Devuelve la clase de la ventana especificada, por ejemplo, para
         * cualquier ventana de XTerm la clase será "XTerm".
         * @param  window Dicha ventana.
         * @return La clase.
         *
         * @~english
         * Returns the class of a window, for example, "XTerm" is the class of
         * all instances of XTerm.
         * @param  window This window.
         * @return The class.
         */
        QString getAppClass(Window window) const;

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
