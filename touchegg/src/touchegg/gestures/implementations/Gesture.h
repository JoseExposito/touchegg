/**
 * @file /src/touchegg/gestures/implementations/Gesture.h
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
#include "src/touchegg/gestures/types/GestureTypeEnum.h"
#include "src/touchegg/actions/implementation/Action.h"


/**
 * @~spanish
 * Clase de la que deben heredar todos los gestos.
 *
 * @~english
 * Class that should inherit all the gestures.
 */
class Gesture {

    private:

        /**
         * @~spanish
         * Tipo del gesto.
         *
         * @~english
         * Gesture type.
         */
        GestureTypeEnum::GestureType type;

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
         *
         * @~english
         * Creates a gesture with the specified properties.
         * @param type   Gesture type.
         * @param id     Gesture ID.
         * @param attrs  Gesture attributes, where the key is the name of the
         *        attribute (ie "focus x", "touches") and the value the value of
         *        the attribute.
          */
        Gesture(GestureTypeEnum::GestureType type, GeisGestureId id,
                const QHash<QString, QVariant>& attrs);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * Destructor.
         */
        virtual ~Gesture();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Se llama cuando el gesto se inicia.
         *
         * @~english
         * Is called when the gesture is started.
         */
        virtual void start() const;

        /**
         * @~spanish
         * Se llama cuando el gesto se actualiza.
         *
         * @~english
         * Is called when the gesture is updated.
         */
        virtual void update() const;

        /**
         * @~spanish
         * Se llama cuando el gesto se finaliza.
         *
         * @~english
         * Is called when the gesture is finished.
         */
        virtual void finish() const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el tipo del gesto.
         * @return El tipo.
         *
         * @~english
         * Returns the gesture type.
         * @return The type.
         */
        GestureTypeEnum::GestureType getType() const;

        /**
         * @~spanish
         * Devuelve el ID del gesto.
         * @return El ID.
         *
         * @~english
         * Returns the gesture ID.
         * @return The ID.
         */
        GeisGestureId getId() const;

        /**
         * @~spanish
         * Devuelve los atributos del gesto.
         * @return Los atributos.
         *
         * @~english
         * Returns the gesture attributes.
         * @return The attributes.
         */
        const QHash<QString, QVariant>& getAttrs() const;

        /**
         * @~spanish
         * Devuelve la acción asociada al gesto.
         * @return La acción.
         *
         * @~english
         * Returns the gesture action.
         * @return The action.
         */
        const Action* getAction() const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Establece el tipo del gesto.
         * @param type El tipo.
         *
         * @~english
         * Sets the gesture type.
         * @param type The type.
         */
        void setType(GestureTypeEnum::GestureType type);

        /**
         * @~spanish
         * Establece el ID del gesto.
         * @param id El ID.
         *
         * @~english
         * Sets the gesture ID.
         * @param id The ID.
         */
        void setId(GeisGestureId id);

        /**
         * @~spanish
         * Establece los atributos del gesto.
         * @param attrs Los atributos.
         *
         * @~english
         * Sets the gesture attributes.
         * @param attrs The attributes.
         */
        void setAttrs(const QHash<QString, QVariant>& attrs);

        /**
         * @~spanish
         * Establece la acción a ejecutar por el gesto.
         * @param action La acción.
         *
         * @~english
         * Sets the action to be executed by gesture.
         * @param action The action.
         */
        void setAction(Action* action);
};

#endif // GESTURE_H
