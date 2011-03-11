/**
 * @file /src/touchegg-gui/presentation/config_forms/ConfigFormFactory.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ConfigFormFactory
 * @author José Expósito
 */
#include "ConfigFormFactory.h"
#include "src/touchegg-gui/presentation/config_forms/ConfigFormFactoryImp.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

ConfigFormFactory* ConfigFormFactory::instance = NULL;

ConfigFormFactory* ConfigFormFactory::getInstance() {
    if(ConfigFormFactory::instance == NULL)
        ConfigFormFactory::instance = new ConfigFormFactoryImp;

    return ConfigFormFactory::instance;
}

