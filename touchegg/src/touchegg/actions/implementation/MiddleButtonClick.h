/**
 * @file /src/touchegg/actions/implementation/MiddleButtonClick.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MiddleButtonClick
 * @author José Expósito
 */
#ifndef MIDDLEBUTTONCLICK_H
#define MIDDLEBUTTONCLICK_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Emula un click con el botón central del ratón.
 *
 * @~english
 * Emulates a click with the middle mouse button.
 */
class MiddleButtonClick : public Action {

    public:

        MiddleButtonClick(const QString& settings, Window window);

        void executeStart(const QHash<QString, QVariant>& attrs);

        void executeUpdate(const QHash<QString, QVariant>& attrs);

        void executeFinish(const QHash<QString, QVariant>& attrs);
};


#endif // MIDDLEBUTTONCLICK_H
