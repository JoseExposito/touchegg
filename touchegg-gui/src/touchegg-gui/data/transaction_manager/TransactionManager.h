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
 * Facilita acciones como restablecer los cambios hechos en la configuración o
 * cancelar los cambios simulando las transacciones disponibles nativamente en
 * una base de datos.
 *
 * @~english
 * Facilitates actions such as reset the changes made to the configuration or
 * cancel changes, simulating transactions, available natively in a database.
 */
class TransactionManager {

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

        //----------------------------------------------------------------------

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
        void loadConfig();

        /**
         * @~spanish
         * Guarda los datos efectuados en disco.
         *
         * @~english
         * Saves the changes made in disk.
         */
        void commit();

        /**
         * @~spanish
         * Descarta los cambios efectuados y recarga la configuración desde
         * disco.
         *
         * @~english
         * Discards any changes and reloads the configuration from disk.
         */
        void rollback();

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
        QSettings* getResource();
};

#endif // TRANSACTIONMANAGER_H
