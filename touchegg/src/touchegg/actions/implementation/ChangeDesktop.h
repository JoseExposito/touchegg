/**
 * @file /src/touchegg/actions/implementation/ChangeDesktop.h
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
#ifndef CHANGEDESKTOP_H
#define CHANGEDESKTOP_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Minimiza la ventana activa.
 *
 * @~english
 * Minimizes active window.
 */
class ChangeDesktop : public Action {

    private:

        /**
         * @~spanish
         * Dirección en la que cambiar de escritorio.
         *
         * @~english
         * Direction to switch desktops.
         */
        bool toRight;

    public:

        ChangeDesktop(const QString& settings, Window window);

        void executeStart(const QHash<QString, QVariant>& attrs);

        void executeUpdate(const QHash<QString, QVariant>& attrs);

        void executeFinish(const QHash<QString, QVariant>& attrs);
};

#endif // CHANGEDESKTOP_H
