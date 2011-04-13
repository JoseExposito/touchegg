/**
 * @file /src/touchegg/actions/implementation/DragAndDrop.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  DragAndDrop
 * @author José Expósito
 */
#ifndef DRAGANDDROP_H
#define DRAGANDDROP_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Emula drag and drop (click y arrastrar).
 *
 * @~english
 * Emulates drag and drop (click and drag).
 */
class DragAndDrop : public Action {

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

        DragAndDrop(const QString& settings, Window window);

        void executeStart(const QHash<QString, QVariant>& attrs);

        void executeUpdate(const QHash<QString, QVariant>& attrs);

        void executeFinish(const QHash<QString, QVariant>& attrs);
};

#endif // DRAGANDDROP_H
