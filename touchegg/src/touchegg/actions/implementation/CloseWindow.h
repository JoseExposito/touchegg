/**
 * @file /src/touchegg/actions/implementation/CloseWindow.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  CloseWindow
 * @author José Expósito
 */
#ifndef CLOSEWINDOW_H
#define CLOSEWINDOW_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Cierra la ventana activa.
 *
 * @~english
 * Closes the active window.
 */
class CloseWindow : public Action {

    public:

        CloseWindow(const QString& settings, Window window);

        void executeStart(const QHash<QString, QVariant>& attrs);

        void executeUpdate(const QHash<QString, QVariant>& attrs);

        void executeFinish(const QHash<QString, QVariant>& attrs);
};

#endif // CLOSEWINDOW_H
