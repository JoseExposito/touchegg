/**
 * @file /src/touchegg/actions/implementation/MouseClick.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MouseClick
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#ifndef LEFTBUTTONCLICK_H
#define LEFTBUTTONCLICK_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Emula un click con el ratón.
 *
 * @~english
 * Emulates a click with the mouse.
 */
class MouseClick : public Action {

    private:

        /**
         * @~spanish
         * Botón a emular.
         *
         * @~english
         * Button to emulate.
         */
        int button;

    public:

        MouseClick(const QString& settings, Window window);

        void executeStart(const QHash<QString, QVariant>& attrs);

        void executeUpdate(const QHash<QString, QVariant>& attrs);

        void executeFinish(const QHash<QString, QVariant>& attrs);

};
#endif // LEFTBUTTONCLICK_H
