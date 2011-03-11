/**
 * @file /src/touchegg-gui/presentation/config_forms/ConfigFormFactoryImp.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ConfigFormFactoryImp
 * @author José Expósito
 */
#include "ConfigFormFactoryImp.h"

// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

ConfigForm* ConfigFormFactoryImp::createConfigForm(
        ActionTypeEnum::ActionType type) const {
    switch (type) {
    case ActionTypeEnum::CHANGE_DESKTOP:
        return new ChangeDesktopConfig;

    case ActionTypeEnum::MOUSE_MOVE:
        return new MouseMoveConfig;

    case ActionTypeEnum::MOUSE_WHEEL_UP:
    case ActionTypeEnum::MOUSE_WHEEL_DOWN:
        return new MouseWhellConfig;

    case ActionTypeEnum::RUN_COMMAND:
        return new RunCommandConfig;

    case ActionTypeEnum::SEND_KEYS:
        return new SendKeysConfig;

    default:
        return NULL;
    }
}
