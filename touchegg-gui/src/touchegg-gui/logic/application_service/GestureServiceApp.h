/**
 * @file /src/touchegg-gui/logic/transfer/GestureServiceApp.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureServiceApp
 * @author José Expósito
 */
#ifndef GESTURESERVICEAPP_H
#define GESTURESERVICEAPP_H

#include "src/touchegg-gui/data/factory/DataFactory.h"
#include "src/touchegg-gui/data/transaction_manager/TransactionManager.h"
#include "src/touchegg-gui/data/dao/GestureDao.h"

/**
 * @~spanish
 * Servicio de aplicación para facilitar la configuración de los gestos.
 *
 * @~english
 * Application service to facilitate gesture configuration.
 */
class GestureServiceApp {

    public:

        /**
         * @~spanish
         * Devuelve los datos del gestos indicado.
         * @param  type Tipo del gesto a actualizar.
         * @return Dichos datos o NULL si no se ha podido acceder.
         *
         * @~english
         * Returns data for the indicated gesture.
         * @param type Type of the gesture to update.
         * @return Such data or NULL if not able to access.
         */
        virtual GestureTransfer read(GestureTypeEnum::GestureType type) = 0;

        /**
         * @~spanish
         * Actualiza la configuración del gesto indicado.
         * @param  gesture Transfer con los datos del gesto a actualizar.
         *
         * @~english
         * Updates the configuration of the specific gesture.
         * @param  gesture Transfer with the data of the gesture to update.
         */
        virtual void update(const GestureTransfer& gesture) = 0;
};

#endif // GESTURESERVICEAPP_H
