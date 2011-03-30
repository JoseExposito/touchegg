/**
 * @file /src/touchegg/actions/implementation/MouseMove.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MouseMove
 * @author José Expósito
 */
#ifndef MOUSEMOVE_H
#define MOUSEMOVE_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Emula el movimiento del ratón.
 *
 * @~english
 * Emulates the mouse movement.
 */
class MouseMove : public Action {

    private:

        /**
         * @~spanish
         * Velocidad del ratón. A mayor más lento.
         *
         * @~english
         * Mouse speed. More is slower.
         */
        int speed;

        /**
         * @~spanish
         * Variable auxiliar para aplicar la velocidad.
         *
         * @~english
         * Auxiliary variable to implement speed.
         */
        int speedCount;

    public:

        MouseMove(const QString& settings, Window window);

        void executeStart(const QHash<QString, QVariant>& attrs);

        void executeUpdate(const QHash<QString, QVariant>& attrs);

        void executeFinish(const QHash<QString, QVariant>& attrs);
};

#endif // MOUSEMOVE_H
