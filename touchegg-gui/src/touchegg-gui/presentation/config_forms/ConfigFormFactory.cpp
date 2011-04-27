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


// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

ConfigFormFactory* ConfigFormFactory::instance = NULL;

ConfigFormFactory* ConfigFormFactory::getInstance() {
    if(ConfigFormFactory::instance == NULL)
        ConfigFormFactory::instance = new ConfigFormFactory;

    return ConfigFormFactory::instance;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

ConfigForm* ConfigFormFactory::createConfigForm(
        const QString& actionType) const {

    if(actionType == "MOUSE_CLICK" || actionType == "DRAG_AND_DROP")
        return new MouseButtons;

    else if(actionType == "CHANGE_DESKTOP" || actionType == "CHANGE_VIEWPORT")
        return new Direction;

    else if(actionType == "VERTICAL_SCROLL" || actionType== "HORIZONTAL_SCROLL")
        return new Speed;

    else if(actionType == "RUN_COMMAND")
        return new RunCommand;

    else if(actionType == "SEND_KEYS")
        return new SendKeys;

    else
        return NULL;
}
