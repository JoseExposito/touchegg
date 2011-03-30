/**
 * @file /src/touchegg/actions/implementation/VerticalScroll.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  VerticalScroll
 * @author José Expósito
 */
#ifndef VERTICALSCROLL_H
#define VERTICALSCROLL_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Emula la rueda del ratón.
 *
 * @~english
 * Emulates the mouse whell.
 */
class VerticalScroll : public Action {

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
         * Desplazamiento acumulado al hacer scroll hacia arriba.
         *
         * @~english
         * Accumulated space to scrolling up.
         */
        int upScrollSpace;

        /**
         * @~spanish
         * Desplazamiento acumulado al hacer scroll hacia abajo.
         *
         * @~english
         * Accumulated space to scrolling down.
         */
        int downScrollSpace;

    public:

        VerticalScroll(const QString& settings, Window window);

        void executeStart(const QHash<QString, QVariant>& attrs);

        void executeUpdate(const QHash<QString, QVariant>& attrs);

        void executeFinish(const QHash<QString, QVariant>& attrs);
};

#endif // VERTICALSCROLL_H
