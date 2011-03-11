/**
 * @file /src/touchegg-gui/logic/application_service/GestureServiceAppImp.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureServiceAppImp
 * @author José Expósito
 */
#include "GestureServiceAppImp.h"

// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

GestureTransfer GestureServiceAppImp::read(GestureTypeEnum::GestureType type) {
    TransactionManager* tm = TransactionManager::getInstance();
    DataFactory*   factory = DataFactory::getInstance();
    GestureDao*        dao = factory->createGestureDao(tm->getResource());
    GestureTransfer    ret = dao->read(type);
    delete dao;
    return ret;
}

void GestureServiceAppImp::update(const GestureTransfer& gesture) {
    TransactionManager* tm = TransactionManager::getInstance();
    DataFactory*   factory = DataFactory::getInstance();
    GestureDao*        dao = factory->createGestureDao(tm->getResource());
    dao->update(gesture);
    delete dao;
}
