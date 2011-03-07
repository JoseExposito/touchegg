/**
 * @file /src/touchegg-gui/logic/factory/LogicFactoryImp.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  LogicFactoryImp
 * @author José Expósito
 */
#include "LogicFactoryImp.h"

// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

Facade* LogicFactoryImp::createFacade() const {
    return new FacadeImp;
}

GeneralServiceApp* LogicFactoryImp::createGeneralServiceApp() const {
    return new GeneralServiceAppImp;
}


GestureServiceApp* LogicFactoryImp::createGestureServiceApp() const {
    return new GestureServiceAppImp;
}
