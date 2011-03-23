/**
 * @file /src/touchegg/actions/implementation/DragAndDrop.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  DragAndDrop
 * @author José Expósito
 */
#ifndef DRAGANDDROP_H
#define DRAGANDDROP_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Emula drag and drop (click y arrastrar).
 *
 * @~english
 * Emulates drag and drop (click and drag).
 */
class DragAndDrop : public Action {

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
        DragAndDrop(const QString& settings);

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

#endif // DRAGANDDROP_H
