/**
 * @file /src/touchegg/actions/implementations/MouseWheelDown.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MouseWheelDown
 * @author José Expósito
 */
#ifndef MOUSEWHEELDOWN_H
#define MOUSEWHEELDOWN_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementations/Action.h"

/**
 * @~spanish
 * Emula la rueda del ratón.
 *
 * @~english
 * Emulates the mouse whell.
 */
class MouseWheelDown : public Action {

    private:

        /**
         * @~spanish
         * Velocidad del scroll. A mayor más lento.
         *
         * @~english
         * Scroll speed. More is slower.
         */
        int speed;

        /**
         * @~spanish
         * Variable auxiliar para aplicar la velocidad.
         *
         * @~english
         * Auxiliary variable to implement speed.
         */
        int scrollCount;

        /**
         * @~spanish
         * Emula la rueda del ratón.
         *
         * @~english
         * Emulates the mouse whell.
         */
        void scroll() const;

    public:

        /**
         * @~spanish
         * Constructor.
         * @param settings Configuración de la acción.
         *
         * @~english
         * Constructor
         * @param settings Action settings.
         */
        MouseWheelDown(const QString& settings);

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
        void executeStart(const QHash<QString, QVariant>& attrs);

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
        void executeUpdate(const QHash<QString, QVariant>& attrs);

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
        void executeFinish(const QHash<QString, QVariant>& attrs);

};

#endif // MOUSEWHEELDOWN_H
