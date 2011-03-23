/**
 * @file /src/touchegg/gestures/collector/GestureCollector.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureCollector
 * @author José Expósito
 */
#ifndef GESTURECOLLECTOR_H
#define GESTURECOLLECTOR_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/config/Config.h"

/**
 * @~spanish
 * Recoge todos los gestos haciendo uso de utouch-geis y emite señales para
 * informar de ello.
 *
 * @~snglish
 * Collect all the gestures using utouch-geis and emits signals to report it.
 */
class GestureCollector : public QThread {

    Q_OBJECT

    private:

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

    protected:

        /**
         * @~spanish
         * Función de inicio del hilo.
         *
         * @~english
         * Thread start function.
         */
        void run();

    public:

        /**
         * @~spanish
         * Función callback que se llamará cuando se añada un nuevo gesto.
         * @param cookie   Parametros extras que se pueden pasar la función.
         * @param type     Tipo del gesto.
         * @param id       Identificador único del gesto.
         * @param numAttrs Número de atributos recibidos.
         * @param attrs    Lista de atributos recibidos.
         *
         * @~english
         * Callback function that is called when a gesture is added.
         * @param cookie   Pointer to the class itself.
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
         * @param cookie   Puntero a la propia clase.
         * @param type     Tipo del gesto.
         * @param id       Identificador único del gesto.
         * @param numAttrs Número de atributos recibidos.
         * @param attrs    Lista de atributos recibidos.
         *
         * @~english
         * Callback function that is called when a gesture is removed.
         * @param cookie   Pointer to the class itself.
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
         * @param cookie   Puntero a la propia clase.
         * @param type     Tipo del gesto.
         * @param id       Identificador único del gesto.
         * @param numAttrs Número de atributos recibidos.
         * @param attrs    Lista de atributos recibidos.
         *
         * @~english
         * Callback function that is called when a gesture starts.
         * @param cookie   Pointer to the class itself.
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
         * @param cookie   Puntero a la propia clase.
         * @param type     Tipo del gesto.
         * @param id       Identificador único del gesto.
         * @param numAttrs Número de atributos recibidos.
         * @param attrs    Lista de atributos recibidos.
         *
         * @~english
         * Callback function that is called when a gesture is updated.
         * @param cookie   Pointer to the class itself.
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
         * @param cookie   Puntero a la propia clase.
         * @param type     Tipo del gesto.
         * @param id       Identificador único del gesto.
         * @param numAttrs Número de atributos recibidos.
         * @param attrs    Lista de atributos recibidos.
         *
         * @~english
         * Callback function that is called when a gesture is finished.
         * @param cookie   Pointer to the class itself.
         * @param type     Gesture type.
         * @param id       Unique gesture identifier.
         * @param numAttrs Number of attributes received.
         * @param attrs    List of attributes.
         */
        static void gestureFinish(void* cookie, GeisGestureType type,
            GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs);


    signals:

        /**
         * @~spanish
         * Señal que se emitirá cuando un gesto se inicie.
         * @param type  Tipo del gesto.
         * @param id    ID del gesto.
         * @param attrs Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         *
         * @~english
         * Signal is emitted when a gesture starts.
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
         * Señal que se emitirá cuando un gesto se actualize.
         * @param type  Tipo del gesto.
         * @param id    ID del gesto.
         * @param attrs Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         *
         * @~english
         * Signal is emitted when a gesture updates.
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
         * Señal que se emitirá cuando un gesto finaliza.
         * @param type  Tipo del gesto.
         * @param id    ID del gesto.
         * @param attrs Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         *
         * @~english
         * Signal is emitted when a gesture finish.
         * @param type  Gesture type.
         * @param id    Gesture ID.
         * @param attrs Gesture attributes, where the key is the name of the
         *        attribute (ie "focus x", "touches") and the value the value of
         *        the attribute.
         */
        void executeGestureFinish(GeisGestureType type, GeisGestureId id,
                const QHash<QString, QVariant>& attrs);

};

#endif // GESTURECOLLECTOR_H
