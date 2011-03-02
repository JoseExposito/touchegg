/**
 * @file /src/touchegg-gui/logic/facade/FacadeImp.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  FacadeImp
 * @author José Expósito
 */
#include "FacadeImp.h"

// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

GeneralTransfer FacadeImp::readGeneralProperty(const QString& property) const {
    LogicFactory*  factory = LogicFactory::getInstance();
    GeneralServiceApp* aux = factory->createGeneralServiceApp();
    GeneralTransfer ret = aux->read(property);
    delete aux;
    return ret;
}

void FacadeImp::updateGeneralProperty(const GeneralTransfer& property) const {
    LogicFactory*  factory = LogicFactory::getInstance();
    GeneralServiceApp* aux = factory->createGeneralServiceApp();
    aux->update(property);
    delete aux;
}

GestureTransfer FacadeImp::readGesture(GestureTypeEnum::GestureType type) const{
    LogicFactory*  factory = LogicFactory::getInstance();
    GestureServiceApp* aux = factory->createGestureServiceApp();
    GestureTransfer ret = aux->read(type);
    delete aux;
    return ret;
}

void FacadeImp::updateGesture(const GestureTransfer& gesture) const {
    LogicFactory*  factory = LogicFactory::getInstance();
    GestureServiceApp* aux = factory->createGestureServiceApp();
    aux->update(gesture);
    delete aux;
}

void FacadeImp::commitData() const {
    TransactionManager* tm = TransactionManager::getInstance();
    tm->commit();
}
