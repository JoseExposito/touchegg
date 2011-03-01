/**
 * @file /src/touchegg-gui/data/factory/DataFactoryImp.cpp
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
#include "DataFactoryImp.h"

// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

GestureDao* DataFactoryImp::createGestureDao(QSettings* settings) const {
    return new GestureDaoImp(settings);
}

GeneralDao* DataFactoryImp::createGeneralDao(QSettings* settings) const {
    return new GeneralDaoImp(settings);
}
