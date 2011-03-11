/**
 * @file /src/touchegg-gui/presentation/config_forms/ConfigFormFactoryImp.h
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
#ifndef CONFIGFORMFACTORYIMP_H
#define CONFIGFORMFACTORYIMP_H

#include "src/touchegg-gui/presentation/config_forms/ConfigFormFactory.h"

/**
 * @~spanish
 * Implementación de ConfigFormFactory, ver la documentación en dicha clase.
 *
 * @~english
 * ConfigFormFactory implementation, to see documentation check that class.
 */
class ConfigFormFactoryImp : public ConfigFormFactory {

    public:

        ConfigForm* createConfigForm(ActionTypeEnum::ActionType type) const;

};

#endif // CONFIGFORMFACTORYIMP_H
