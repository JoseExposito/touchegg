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
#include "src/touchegg/gestures/gesturesimp/Gesture.h"
#include "src/touchegg/gestures/executor/GestureExecutor.h"


/**
 * @~spanish
 * Clase que recibe los gestos y con ayuda de la GestureFactory los procesa y
 * ejecuta la acción correspondiente.
 *
 * @~english
 * Class that receives the gestures and with the help of the GestureFactory
 * processes it and execute the corresponding action.
 */
class GestureHandler : public QObject {

    Q_OBJECT

    private:

        /**
         * @~spanish
         * Para ejecutar los gestos.
         *
         * @~english
         * To execute gestures.
         */
        static GestureExecutor gestureExecutor;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve un QHash con todos los atributos de un gesto, siendo la
         * clave el nombre del atributo (por ejemplo "focus x", "touches"...) y
         * el valor el valor del propio atributo.
         * @param numAttrs Número de atributos recibidos.
         * @param attrs    Lista de atributos recibidos.
         * @return El QHash
         *
         * @~english
         * Returns a Hash with all attributes of a gesture, where the key is the
         * name of the attribute (ie "focus x", "touches") and the value the
         * value of the attribute.
         * @param numAttrs Number of attributes received.
         * @param attrs    List of attributes.
         * @return The hash.
         */
        static QHash<QString, QVariant> getGestureAttrs(GeisSize numAttrs,
            GeisGestureAttr* attrs);

    public:

        /**
         * @~spanish
         * Función callback que se llamará cuando se añada un nuevo gesto.
         * @param cookie   Parametros extras que se pueden pasar  la función.
         * @param type     Tipo del gesto.
         * @param id       Identificador único del gesto.
         * @param numAttrs Número de atributos recibidos.
         * @param attrs    Lista de atributos recibidos.
         *
         * @~english
         * Callback function that is called when a gesture is added.
         * @param cookie   Extra parameters to be passed to the function.
         * @param type     Gesture type.
         * @param id       Unique gesture identifier.
         * @param numAttrs Number of attributes received.
         * @param attrs    List of attributes.
         */
        static void gestureAdded(void* cookie, GeisGestureType type,
            GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs);

        /**
         * @~spanish
         * Función callback que se llamará cuando se elimine gesto.
         * @param cookie   Parametros extras que se pueden pasar  la función.
         * @param type     Tipo del gesto.
         * @param id       Identificador único del gesto.
         * @param numAttrs Número de atributos recibidos.
         * @param attrs    Lista de atributos recibidos.
         *
         * @~english
         * Callback function that is called when a gesture is removed.
         * @param cookie   Extra parameters to be passed to the function.
         * @param type     Gesture type.
         * @param id       Unique gesture identifier.
         * @param numAttrs Number of attributes received.
         * @param attrs    List of attributes.
         */
        static void gestureRemoved(void* cookie, GeisGestureType type,
            GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs);

        /**
         * @~spanish
         * Función callback que se llamará cuando se inicie un gesto.
         * @param cookie   Parametros extras que se pueden pasar  la función.
         * @param type     Tipo del gesto.
         * @param id       Identificador único del gesto.
         * @param numAttrs Número de atributos recibidos.
         * @param attrs    Lista de atributos recibidos.
         *
         * @~english
         * Callback function that is called when a gesture starts.
         * @param cookie   Extra parameters to be passed to the function.
         * @param type     Gesture type.
         * @param id       Unique gesture identifier.
         * @param numAttrs Number of attributes received.
         * @param attrs    List of attributes.
         */
        static void gestureStart(void* cookie, GeisGestureType type,
            GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs);

        /**
         * @~spanish
         * Función callback que se llamará cuando se actualice un gesto.
         * @param cookie   Parametros extras que se pueden pasar  la función.
         * @param type     Tipo del gesto.
         * @param id       Identificador único del gesto.
         * @param numAttrs Número de atributos recibidos.
         * @param attrs    Lista de atributos recibidos.
         *
         * @~english
         * Callback function that is called when a gesture is updated.
         * @param cookie   Extra parameters to be passed to the function.
         * @param type     Gesture type.
         * @param id       Unique gesture identifier.
         * @param numAttrs Number of attributes received.
         * @param attrs    List of attributes.
         */
        static void gestureUpdate(void* cookie, GeisGestureType type,
            GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs);

        /**
         * @~spanish
         * Función callback que se llamará cuando un gesto finalice.
         * @param cookie   Parametros extras que se pueden pasar  la función.
         * @param type     Tipo del gesto.
         * @param id       Identificador único del gesto.
         * @param numAttrs Número de atributos recibidos.
         * @param attrs    Lista de atributos recibidos.
         *
         * @~english
         * Callback function that is called when a gesture is finished.
         * @param cookie   Extra parameters to be passed to the function.
         * @param type     Gesture type.
         * @param id       Unique gesture identifier.
         * @param numAttrs Number of attributes received.
         * @param attrs    List of attributes.
         */
        static void gestureFinish(void* cookie, GeisGestureType type,
            GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs);

    public slots:

        /**
         * @~spanish
         * Inicializa la aplicación y lee los gestos que se producen.
         *
         * @~english
         * Initializes the application and reads the gestures that are produced.
         */
        void run();
};

#endif // GESTUREHANDLER_H
