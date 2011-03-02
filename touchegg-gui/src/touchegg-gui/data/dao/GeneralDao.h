/**
 * @file /src/touchegg-gui/data/dao/GeneralDao.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GeneralDao
 * @author José Expósito
 */
#ifndef GENERALDAO_H
#define GENERALDAO_H

#include "src/touchegg-gui/logic/transfer/GeneralTransfer.h"

/**
 * @~spanish
 * Data Access Object para acceder a la parte de la configuración destinada a
 * los gestos.
 *
 * @~english
 * Data Access Object to access to the configuration designed for gestures.
 */
class GeneralDao {

    public:

        /**
         * @~spanish
         * Crea un DAO que trabaja con la configuración indicada.
         *
         * @~english
         * Creates a DAO that works with the specified settings.
         */
        GeneralDao(QSettings* /*settings*/){}

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

#endif // GENERALDAO_H
