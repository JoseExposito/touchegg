/**
 * @file /src/touchegg/gestures/gesturesimp/Gesture.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  Gesture
 * @author José Expósito
 */
#ifndef GESTURE_H
#define GESTURE_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/Action.h"


/**
 * @~spanish
 * Clase de la que deben heredar todos los gestos.
 *
 * @~english
 * Class that should inherit all the gestures.
 */
class Gesture {

    protected:

        /**
         * @~spanish
         * Tipo del gesto.
         *
         * @~english
         * Gesture type.
         */
        GeisGestureType type;

        /**
         * @~spanish
         * ID del gesto.
         *
         * @~english
         * Gesture ID.
         */
        GeisGestureId id;

        /**
         * @~spanish
         * Atributos del gestos, siendo la clave el nombre del atributo (por
         * ejemplo "focus x", "touches"...) y el valor el valor del propio
         * atributo.
         *
         * @~english
         * Gesture attributes, where the key is the name of the attribute (ie
         * "focus x", "touches") and the value the value of the attribute.
         */
        QHash<QString, QVariant> attrs;

        /**
         * @~spanish
         * Acción asociada al gesto.
         *
         * @~english
         * Action associated to the gesture.
         */
        Action* action;

    public:

        /**
         * @~spanish
         * Crea un gesto con las propiedades indicadas.
         * @param type   Tipo del gesto.
         * @param id     ID del gesto.
         * @param attrs  Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         * @param action Acción asociada al gesto.
         *
         * @~english
         * Creates a gesture with the specified properties.
         * @param type   Gesture type.
         * @param id     Gesture ID.
         * @param attrs  Gesture attributes, where the key is the name of the
         *        attribute (ie "focus x", "touches") and the value the value of
         *        the attribute.
         * @param action Action associated to the gesture.
         */
        Gesture(GeisGestureType type, GeisGestureId id,
                const QHash<QString, QVariant>& attrs, Action* action) {
            this->type   = type;
            this->id     = id;
            this->attrs  = attrs;
            this->action = action;
        }

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * Destructor.
         */
        virtual ~Gesture() {
            if(this->action != NULL)
                delete this->action;
        }

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Se llama cuando el gesto se inicia.
         *
         * @~english
         * Is called when the gesture is started.
         */
        virtual void start() const {
            if(this->action != NULL)
                this->action->executeStart(this->attrs);
        }

        /**
         * @~spanish
         * Se llama cuando el gesto se actualiza.
         *
         * @~english
         * Is called when the gesture is updated.
         */
        virtual void update() const {
            if(this->action != NULL)
                this->action->executeUpdate(this->attrs);
        }

        /**
         * @~spanish
         * Se llama cuando el gesto se finaliza.
         *
         * @~english
         * Is called when the gesture is finished.
         */
        virtual void finish() const  {
            if(this->action != NULL)
                this->action->executeFinish(this->attrs);
        }

        /**
         * @~spanish
         * Indica si los atributos dados definen este gesto.
         * @return Si lo definen o no.
         *
         * @~english
         * Indicates if the given attributes defines this gesture.
         * @return If it define the gesture or not.
         */
        bool isThisGesture(QHash<QString, QVariant> /*attrs*/) { return false; }

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el ID del gesto.
         * @return El ID.
         *
         * @~english
         * Returns the gesture ID.
         * @return The ID.
         */
        GeisGestureId getId() {
            return this->id;
        }

};

#endif // GESTURE_H
