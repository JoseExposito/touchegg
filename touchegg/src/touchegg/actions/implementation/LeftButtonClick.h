/**
 * @file /src/touchegg/actions/implementation/LeftButtonClick.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  LeftButtonClick
 * @author José Expósito
 */
#ifndef LEFTBUTTONCLICK_H
#define LEFTBUTTONCLICK_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Emula un click con el botón izquierdo del ratón.
 *
 * @~english
 * Emulates a click with the left mouse button.
 */
class LeftButtonClick : public Action {

    public:

        LeftButtonClick(const QString& settings, Window window);

        void executeStart(const QHash<QString, QVariant>& attrs);

        void executeUpdate(const QHash<QString, QVariant>& attrs);

        void executeFinish(const QHash<QString, QVariant>& attrs);
};
#endif // LEFTBUTTONCLICK_H
