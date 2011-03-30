/**
 * @file /src/touchegg/actions/implementation/MaximizeRestoreWindow.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MaximizeRestoreWindow
 * @author José Expósito
 */
#ifndef MAXIMIZERESTOREWINDOW_H
#define MAXIMIZERESTOREWINDOW_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Maximiza la ventana activa.
 *
 * @~english
 * Maximizes active window.
 */
class MaximizeRestoreWindow : public Action {

    public:

        MaximizeRestoreWindow(const QString& settings, Window window);

        void executeStart(const QHash<QString, QVariant>& attrs);

        void executeUpdate(const QHash<QString, QVariant>& attrs);

        void executeFinish(const QHash<QString, QVariant>& attrs);
};

#endif // MAXIMIZERESTOREWINDOW_H
