/**
 * @file /src/touchegg-gui/logic/factory/LogicFactory.h
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
#ifndef LOGICFACTORY_H
#define LOGICFACTORY_H

#include "src/touchegg-gui/logic/facade/Facade.h"
#include "src/touchegg-gui/logic/application_service/GeneralServiceApp.h"
#include "src/touchegg-gui/logic/application_service/GestureServiceApp.h"

/**
 * @~spanish
 * Factoría para crear las distintas clases de la capa de datos.
 *
 * @~english
 * Factory to create different class of data tier.
 */
class LogicFactory {

    protected:

        /**
         * @~spanish
         * Única instancia de la clase.
         *
         * @~english
         * Single instance of the class.
         */
        static LogicFactory* instance;

        // Hide constructors
        LogicFactory(){}
        LogicFactory(const LogicFactory&){}
        const LogicFactory& operator=(const LogicFactory& df) { return df; }

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
        static LogicFactory* getInstance();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Crea un nuevo Facade, no olvidar liberar memoria.
         * @return El Facade.
         *
         * @~english
         * Creates a new Facade, don't forget free memory.
         * @return The Facade.
         */
        virtual Facade* createFacade() const = 0;

        /**
         * @~spanish
         * Crea un nuevo GeneralServiceApp, no olvidar liberar memoria.
         * @return El GeneralServiceApp.
         *
         * @~english
         * Creates a new GeneralServiceApp, don't forget free memory.
         * @return The GeneralServiceApp.
         */
        virtual GeneralServiceApp* createGeneralServiceApp() const = 0;

        /**
         * @~spanish
         * Crea un nuevo GestureServiceApp, no olvidar liberar memoria.
         * @return El GestureServiceApp.
         *
         * @~english
         * Creates a new GestureServiceApp, don't forget free memory.
         * @return The GestureServiceApp.
         */
        virtual GestureServiceApp* createGestureServiceApp() const = 0;
};

#endif // LOGICFACTORY_H
