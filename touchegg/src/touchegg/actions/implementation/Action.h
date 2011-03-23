/**
 * @file /src/touchegg/actions/implementation/Action.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  Action
 * @author José Expósito
 */
#ifndef ACTION_H
#define ACTION_H

#include "src/touchegg/util/Include.h"

/**
 * @~spanish
 * Clase de la que deben heredar todas las acciones. Las acciones son
 * operaciones asociadas a un gesto que se ejecutarán cuando dicho gesto se
 * capture.
 *
 * @~english
 * Class that should inherit all actions. Actions are operations associated with
 * a gesture that will be executed when this gesture is caught.
 */
class Action {

    public:

        /**
         * @~spanish
         * Constructor.
         *
         * @~english
         * Constructor.
         */
        Action(const QString& /*settings*/) {}

        /**
         * @~spanish
         * Parte de la acción que se ejecutará cuando el gesto se inicie.
         * @param attrs Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         *
         * @~english
         * Part of the action that will be executed when the gesture is started.
         * @param attrs Gesture attributes, where the key is the name of the
         *        attribute (ie "focus x", "touches") and the value the value of
         *        the attribute.
         */
        virtual void executeStart(const QHash<QString, QVariant>& attrs) = 0;

        /**
         * @~spanish
         * Parte de la acción que se ejecutará cuando el gesto se actualice.
         * @param attrs Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         *
         * @~english
         * Part of the action that will be executed when the gesture is updated.
         * @param attrs Gesture attributes, where the key is the name of the
         *        attribute (ie "focus x", "touches") and the value the value of
         *        the attribute.
         */
        virtual void executeUpdate(const QHash<QString, QVariant>& attrs) = 0;

        /**
         * @~spanish
         * Parte de la acción que se ejecutará cuando el gesto se finalice.
         * @param attrs Atributos del gestos, siendo la clave el nombre del
         *        atributo (por ejemplo "focus x", "touches"...) y el valor el
         *        valor del propio atributo.
         *
         * @~english
         * Part of the action that will be executed when the gesture finish.
         * @param attrs Gesture attributes, where the key is the name of the
         *        attribute (ie "focus x", "touches") and the value the value of
         *        the attribute.
         */
        virtual void executeFinish(const QHash<QString, QVariant>& attrs) = 0;

};

#endif // ACTION_H
