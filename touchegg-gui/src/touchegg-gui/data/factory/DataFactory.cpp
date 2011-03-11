/**
 * @file /src/touchegg-gui/data/factory/DataFactory.cpp
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
#include "DataFactory.h"
#include "src/touchegg-gui/data/factory/DataFactoryImp.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

DataFactory* DataFactory::instance = NULL;

DataFactory* DataFactory::getInstance() {
    if(DataFactory::instance == NULL)
        DataFactory::instance = new DataFactoryImp;

    return DataFactory::instance;
}
