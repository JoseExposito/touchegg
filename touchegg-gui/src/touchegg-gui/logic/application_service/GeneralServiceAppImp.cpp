/**
 * @file /src/touchegg-gui/logic/transfer/GeneralServiceAppImp.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GeneralServiceAppImp
 * @author José Expósito
 */
#include "GeneralServiceAppImp.h"

// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

GeneralTransfer GeneralServiceAppImp::read(const QString& property) {
    TransactionManager* tm = TransactionManager::getInstance();
    DataFactory*   factory = DataFactory::getInstance();
    GeneralDao*        dao = factory->createGeneralDao(tm->getResource());
    GeneralTransfer    ret =  dao->read(property);
    delete dao;
    return ret;
}

void GeneralServiceAppImp::update(const GeneralTransfer& property) {
    TransactionManager* tm = TransactionManager::getInstance();
    DataFactory*   factory = DataFactory::getInstance();
    GeneralDao*        dao = factory->createGeneralDao(tm->getResource());
    dao->update(property);
    delete dao;
}
