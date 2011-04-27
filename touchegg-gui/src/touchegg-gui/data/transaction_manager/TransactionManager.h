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

    private:

        // Constants to access to the settings
        static const char* USR_SHARE_CONFIG_FILE;
        static const char* HOME_CONFIG_FILE; // Sumarle el $HOME por delante
        static const char* HOME_CONFIG_DIR;

        /**
         * @~spanish
         * Configuración usada.
         *
         * @~english
         * Configuration used.
         */
        QHash<QString, QString>* settings;

        /**
         * @~spanish
         * Inicializa el QHash que contiene la configuración. Dicho QHash tendrá
         * como clave una cadena del tipo "TWO_FINGERS_TAP.ALL.action" y como
         * valor, en este caso, la acción correspondiente.
         * @param file Archivo desde el que leer la configuración.
         *
         * @~english
         * Initializes the QHas that contains the settings. This QHash will have
         * as key a string like "TWO_FINGERS_TAP.ALL.action" and as value, in
         * this case, the action.
         * @param file File from which to read configuration.
         */
        void loadConfig(QFile& file);

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
        TransactionManager();
        TransactionManager(const TransactionManager&);
        const TransactionManager& operator=(const TransactionManager&);

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
         * Guarda los cambios y recarga Touchégg.
         *
         * @~english
         * Saves the changes and reloads Touchégg.
         */
        void commit();

        /**
         * @~spanish
         * Descarta los cambios hechos tras el último commit.
         *
         * @~english
         * Descarta los cambios hechos tras el último commit.
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
        QHash<QString, QString>* getResource() const;

};

#endif // TRANSACTIONMANAGER_H
