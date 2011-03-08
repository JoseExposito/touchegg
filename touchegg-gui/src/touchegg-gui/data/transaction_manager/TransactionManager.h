/**
 * @file /src/touchegg-gui/data/transaction_manager/TransactionManager.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  TransactionManager
 * @author José Expósito
 */
#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include "src/touchegg-gui/util/Include.h"

/**
 * @~spanish
 * Facilita el acceso a la configuración guardada en disco.
 *
 * @~english
 * Provides access to the saved settings to disk.
 */
class TransactionManager {

    protected:

        /**
         * @~spanish
         * Única instancia de la clase.
         *
         * @~english
         * Single instance of the class.
         */
        static TransactionManager* instance;

        // Hide constructors
        TransactionManager(){}
        TransactionManager(const TransactionManager&){}
        const TransactionManager& operator=(const TransactionManager& tm) {
            return tm;
        }

    public:

        /**
         * @~spanish
         * Único método para obtener una instancia de la clase.
         * @return La única instancia de la clase.
         *
         * @~english
         * Only method to get an instance of the class.
         * @return The single instance of the class.
         */
        static TransactionManager* getInstance();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * (Re)carga la configuración desde disco.
         *
         * @~english
         * (Re)loads the configuration from disk.
         */
        virtual void loadConfig() = 0;

        /**
         * @~spanish
         * Recarga Touchégg para que se apliquen los cambios.
         *
         * @~english
         * Reloads Touchégg to apply changes.
         */
        virtual void commit() = 0;

        /**
         * @~spanish
         * Devuelve la configuración utilizada, sobre la que operar, para poder
         * hacer commit y rollback.
         * @return La configuración.
         *
         * @~english
         * Return the used confiuration, on which to operate, to can make commit
         * and rollback.
         * @return The configuration.
         */
        virtual QSettings* getResource() const = 0;
};

#endif // TRANSACTIONMANAGER_H
