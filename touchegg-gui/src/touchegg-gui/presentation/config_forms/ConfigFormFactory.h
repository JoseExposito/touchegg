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

#include "src/touchegg-gui/presentation/config_forms/ConfigForm.h"
#include "src/touchegg-gui/presentation/config_forms/MouseButtons.h"
#include "src/touchegg-gui/presentation/config_forms/Direction.h"
#include "src/touchegg-gui/presentation/config_forms/Speed.h"
#include "src/touchegg-gui/presentation/config_forms/RunCommand.h"
#include "src/touchegg-gui/presentation/config_forms/SendKeys.h"

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
        ConfigFormFactory(const ConfigFormFactory&);
        const ConfigFormFactory& operator=(const ConfigFormFactory&);

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
         * Crea un nuevo ConfigForm, no olvidar liberar memoria. Devuelve NULL
         * si la acción introducida no es configurable.
         * @param  actionType Tipo de formulario a crear.
         * @return El ConfigForm.
         *
         * @~english
         * Creates a new ConfigForm, don't forget free memory. Returns NULL if
         * the introduced action is not configurable.
         * @param  actionType Type of the form to create.
         * @return The ConfigForm.
         */
        ConfigForm* createConfigForm(const QString& actionType) const;

};

#endif // CONFIGFORMFACTORY_H
