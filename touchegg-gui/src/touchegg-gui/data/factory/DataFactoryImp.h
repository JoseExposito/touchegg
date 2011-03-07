/**
 * @file /src/touchegg-gui/data/factory/DataFactoryImp.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  DataFactoryImp
 * @author José Expósito
 */
#ifndef DATAFACTORYIMP_H
#define DATAFACTORYIMP_H

#include "src/touchegg-gui/data/factory/DataFactory.h"
#include "src/touchegg-gui/data/dao/GestureDaoImp.h"
#include "src/touchegg-gui/data/dao/GeneralDaoImp.h"

/**
 * @~spanish
 * Implementación de DataFactory, ver la documentación en dicha clase.
 *
 * @~english
 * DataFactory implementation, to see documentation check that class.
 */
class DataFactoryImp : public DataFactory {

    public:

        GestureDao* createGestureDao(QSettings* settings) const;

        GeneralDao* createGeneralDao(QSettings* settings) const;
};

#endif // DATAFACTORYIMP_H
