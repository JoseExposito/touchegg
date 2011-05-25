/**
 * @file /src/touchegg/actions/implementation/SendKeys.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  SendKeys
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#ifndef SENDKEYS_H
#define SENDKEYS_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Envía las teclas indicadas en la configuración a la ventana activa.
 *
 * @~english
 * Envía las teclas indicadas en la configuración a la ventana activa.
 */
class SendKeys : public Action {

    private:

        /**
         * @~spanish
         * Teclas a mantener pulsadas mientras se envían el resto de teclas.
         *
         * @~english
         * Keys to hold down while sending the rest of keys.
         */
        QList<KeyCode> holdDownKeys;

        /**
         * @~spanish
         * Teclas a enviar mientras se mantienen pulsadas las holdDownKeys.
         *
         * @~english
         * Keys to send while holdDownKeys are sending.
         */
        QList<KeyCode> pressBetweenKeys;

    public:

        SendKeys(const QString& settings, Window window);

        void executeStart(const QHash<QString, QVariant>& attrs);

        void executeUpdate(const QHash<QString, QVariant>& attrs);

        void executeFinish(const QHash<QString, QVariant>& attrs);
};

#endif // SENDKEYS_H
