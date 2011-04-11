/**
 * @file /src/touchegg/actions/implementation/ChangeViewport.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ChangeDesktop
 * @author José Expósito
 */
#ifndef CHANGEVIEWPORT_H
#define CHANGEVIEWPORT_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Cambia el viewport.
 *
 * @~english
 * Change the viewport.
 */
class ChangeViewport : public Action {

    private:

        /**
         * @~spanish
         * Dirección en la que cambiar de escritorio.
         *
         * @~english
         * Direction to switch desktops.
         */
        bool next;

    public:

        ChangeViewport(const QString& settings, Window window);

        void executeStart(const QHash<QString, QVariant>& attrs);

        void executeUpdate(const QHash<QString, QVariant>& attrs);

        void executeFinish(const QHash<QString, QVariant>& attrs);
};

#endif // CHANGEVIEWPORT_H
