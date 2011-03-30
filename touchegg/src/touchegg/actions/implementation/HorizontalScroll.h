/**
 * @file /src/touchegg/actions/implementation/HorizontalScroll.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  HorizontalScroll
 * @author José Expósito
 */
#ifndef HORIZONTALSCROLL_H
#define HORIZONTALSCROLL_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Emula la rueda del ratón.
 *
 * @~english
 * Emulates the mouse whell.
 */
class HorizontalScroll : public Action {

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
         * Desplazamiento acumulado al hacer scroll hacia la izquierda.
         *
         * @~english
         * Accumulated space to scrolling left.
         */
        int leftScrollSpace;

        /**
         * @~spanish
         * Desplazamiento acumulado al hacer scroll hacia derecha.
         *
         * @~english
         * Accumulated space to scrolling right.
         */
        int rightScrollSpace;

    public:

        HorizontalScroll(const QString& settings, Window window);

        void executeStart(const QHash<QString, QVariant>& attrs);

        void executeUpdate(const QHash<QString, QVariant>& attrs);

        void executeFinish(const QHash<QString, QVariant>& attrs);
};

#endif // HORIZONTALSCROLL_H
