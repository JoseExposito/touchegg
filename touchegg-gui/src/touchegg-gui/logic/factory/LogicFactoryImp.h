/**
 * @file /src/touchegg-gui/logic/factory/LogicFactoryImp.h
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
#ifndef LOGICFACTORYIMP_H
#define LOGICFACTORYIMP_H

#include "src/touchegg-gui/logic/factory/LogicFactory.h"
#include "src/touchegg-gui/logic/facade/FacadeImp.h"
#include "src/touchegg-gui/logic/application_service/GeneralServiceAppImp.h"
#include "src/touchegg-gui/logic/application_service/GestureServiceAppImp.h"

/**
 * @~spanish
 * Implementación de LogicFactory, ver la documentación en dicha clase.
 *
 * @~english
 * LogicFactory implementation, to see documentation check that class.
 */
class LogicFactoryImp : public LogicFactory {

    public:

        Facade* createFacade() const;

        GeneralServiceApp* createGeneralServiceApp() const;

        GestureServiceApp* createGestureServiceApp() const;                

};

#endif // LOGICFACTORYIMP_H
