/**
 * @file /src/touchegg-gui/logic/factory/LogicFactory.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  LogicFactory
 * @author José Expósito
 */
#include "LogicFactory.h"
#include "src/touchegg-gui/logic/factory/LogicFactoryImp.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

LogicFactory* LogicFactory::instance = NULL;

LogicFactory* LogicFactory::getInstance() {
    if(LogicFactory::instance == NULL)
        LogicFactory::instance = new LogicFactoryImp;

    return LogicFactory::instance;
}

