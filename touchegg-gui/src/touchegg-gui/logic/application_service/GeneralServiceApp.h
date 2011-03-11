/**
 * @file /src/touchegg-gui/logic/application_service/GeneralServiceApp.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GeneralServiceApp
 * @author José Expósito
 */
#ifndef GENERALSERVICEAPP_H
#define GENERALSERVICEAPP_H

#include "src/touchegg-gui/data/factory/DataFactory.h"
#include "src/touchegg-gui/data/transaction_manager/TransactionManager.h"
#include "src/touchegg-gui/data/dao/GeneralDao.h"

/**
 * @~spanish
 * Servicio de aplicación para facilitar la configuración de los gestos.
 *
 * @~english
 * Application service to facilitate gesture configuration.
 */
class GeneralServiceApp {

    public:

        /**
         * @~spanish
         * Devuelve los datos de la propiedad indicada.
         * @param  property La propiedad.
         * @return Dichos datos o NULL si no se ha podido acceder.
         *
         * @~english
         * Returns data for the indicated property.
         * @param  property The property.
         * @return Such data or NULL if not able to access.
         */
        virtual GeneralTransfer read(const QString& property) = 0;

        /**
         * @~spanish
         * Actualiza la propiedad indicada.
         * @param property La propiedad.
         *
         * @~english
         * Updates the configuration of the specific gesture.
         * @param property The property.
         */
        virtual void update(const GeneralTransfer& property) = 0;
};

#endif // GENERALSERVICEAPP_H
