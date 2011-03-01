/**
 * @file /src/touchegg-gui/data/factory/DataFactory.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  DataFactory
 * @author José Expósito
 */
#ifndef DATAFACTORY_H
#define DATAFACTORY_H

#include "src/touchegg-gui/data/transaction_manager/TransactionManager.h"
#include "src/touchegg-gui/data/dao/GestureDao.h"
#include "src/touchegg-gui/data/dao/GeneralDao.h"

/**
 * @~spanish
 * Factoría para crear las distintas clases de la capa de datos.
 *
 * @~english
 * Factory to create different class of data tier.
 */
class DataFactory {

    protected:

        /**
         * @~spanish
         * Única instancia de la clase.
         *
         * @~english
         * Single instance of the class.
         */
        static DataFactory* instance;

        // Hide constructors
        DataFactory(){}
        DataFactory(const DataFactory&){}
        const DataFactory& operator=(const DataFactory& df) { return df; }

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
        static DataFactory* getInstance();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Crea un nuevo GestureDao, no olvidar liberar memoria.
         * @param  settings Configuración que usará el DAO.
         * @return El GestureDao.
         *
         * @~english
         * Creates a new GestureDao, don't forget free memory.
         * @param  settings Settings that will use the DAO.
         * @return The GestureDao.
         */
        virtual GestureDao* createGestureDao(QSettings* settings) const = 0;

        /**
         * @~spanish
         * Crea un nuevo GeneralDao, no olvidar liberar memoria.
         * @param  settings Configuración que usará el DAO.
         * @return El GeneralDao.
         *
         * @~english
         * Creates a new GeneralDao, don't forget free memory.
         * @param  settings Settings that will use the DAO.
         * @return The GeneralDao.
         */
        virtual GeneralDao* createGeneralDao(QSettings* settings) const = 0;

};

#endif // DATAFACTORY_H
