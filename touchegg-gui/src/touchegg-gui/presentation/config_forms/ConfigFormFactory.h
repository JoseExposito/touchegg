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
#ifndef CONFIGFORMFACTORY_H
#define CONFIGFORMFACTORY_H

#include "src/touchegg-gui/logic/type/ActionTypeEnum.h"
#include "src/touchegg-gui/presentation/config_forms/ConfigForm.h"
#include "src/touchegg-gui/presentation/config_forms/ChangeDesktopConfig.h"
#include "src/touchegg-gui/presentation/config_forms/MouseMoveConfig.h"
#include "src/touchegg-gui/presentation/config_forms/MouseWhellConfig.h"
#include "src/touchegg-gui/presentation/config_forms/RunCommandConfig.h"
#include "src/touchegg-gui/presentation/config_forms/SendKeysConfig.h"

/**
 * @~spanish
 * Factoría para crear los distintos formularios de configuración.
 *
 * @~english
 * Factory to create different comfiguration forms.
 */
class ConfigFormFactory {

    protected:

        /**
         * @~spanish
         * Única instancia de la clase.
         *
         * @~english
         * Single instance of the class.
         */
        static ConfigFormFactory* instance;

        // Hide constructors
        ConfigFormFactory(){}
        ConfigFormFactory(const ConfigFormFactory&){}
        const ConfigFormFactory& operator=(const ConfigFormFactory& cff) {
                return cff;
        }

    public:

        /**
         * @~spanish
         * Único método para obtener una instancia de la clase.
         * @return La única instancia de la clase.
         *
         * @~english
         * Only method to get an instance of the class.
         * @return The single instance of the class.
         */
        static ConfigFormFactory* getInstance();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Crea un nuevo ConfigForm, no olvidar liberar memoria.
         * @param  type Tipo de formulario a crear.
         * @return El ConfigForm.
         *
         * @~english
         * Creates a new ConfigForm, don't forget free memory.
         * @param  type Type of the form to create.
         * @return The ConfigForm.
         */
        virtual ConfigForm* createConfigForm(ActionTypeEnum::ActionType type)
                const = 0;

};

#endif // CONFIGFORMFACTORY_H
