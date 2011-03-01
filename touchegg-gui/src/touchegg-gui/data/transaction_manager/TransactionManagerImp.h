/**
 * @file /src/touchegg-gui/data/transaction_manager/TransactionManagerImp.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  TransactionManagerImp
 * @author José Expósito
 */
#ifndef TRANSACTIONMANAGERIMP_H
#define TRANSACTIONMANAGERIMP_H

#include "src/touchegg-gui/data/transaction_manager/TransactionManager.h"

/**
 * @~spanish
 * Implementación de TransactionManager, ver la documentación en dicha clase.
 *
 * @~english
 * GestureDao TransactionManager, to see documentation check that class.
 */
class TransactionManagerImp : public TransactionManager {

    private:

        /**
         * @~spanish
         * Ruta del archivo de configuración. Añadirle $HOME por delante.
         *
         * @~english
         * Path of the configuration file. Concatenate $HOME at beginning.
         */
        static const char* HOME_CONFIG_FILE;

        /**
         * @~spanish
         * Configuración usada.
         *
         * @~english
         * Configuration used.
         */
        QSettings* settings;

    public:

        TransactionManagerImp();

        void loadConfig();

        void commit();

        void rollback();

        QSettings* getResource() const;
};

#endif // TRANSACTIONMANAGERIMP_H
