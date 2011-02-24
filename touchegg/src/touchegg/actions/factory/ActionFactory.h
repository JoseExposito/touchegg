/**
 * @file /src/touchegg/actions/factory/ActionFactory.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ActionFactory
 * @author José Expósito
 */
#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/types/ActionTypeEnum.h"
#include "src/touchegg/actions/implementations/Action.h"
#include "src/touchegg/actions/implementations/MouseMove.h"
#include "src/touchegg/actions/implementations/RightButtonClick.h"
#include "src/touchegg/actions/implementations/MiddleButtonClick.h"
#include "src/touchegg/actions/implementations/MouseWheelUp.h"
#include "src/touchegg/actions/implementations/MouseWheelDown.h"
#include "src/touchegg/actions/implementations/MinimizeWindow.h"
#include "src/touchegg/actions/implementations/MaximizeRestoreWindow.h"
#include "src/touchegg/actions/implementations/CloseWindow.h"
#include "src/touchegg/actions/implementations/ResizeWindow.h"
#include "src/touchegg/actions/implementations/ShowDesktop.h"
#include "src/touchegg/actions/implementations/ChangeDesktop.h"
#include "src/touchegg/actions/implementations/SendKeys.h"
#include "src/touchegg/actions/implementations/MoveWindow.h"
#include "src/touchegg/actions/implementations/RunCommand.h"
#include "src/touchegg/actions/implementations/DragAndDrop.h"
#include "src/touchegg/actions/implementations/LeftButtonClick.h"

/**
 * @~spanish
 * Factoría para crear las distintas acciones.
 *
 * @~english
 * Factory to create the different actions.
 */
class ActionFactory {

    private:

        /**
         * @~spanish
         * Única instancia de la clase.
         *
         * @~english
         * Single instance of the class.
         */
        static ActionFactory* instance;

        // Hide constructors
        ActionFactory(){}
        ActionFactory(const ActionFactory&){}
        const ActionFactory& operator = (const ActionFactory& gf){return gf;}

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
        static ActionFactory* getInstance();

        /**
         * @~spanish
         * Crea la acción indicada. IMPORTANTE: No olvidar liberar memoria.
         * @param  actionType Tipo de acción a crear.
         * @param  settings   Configuración de la acción.
         * @return La acción.
         *
         * @~english
         * Creates the especific action. IMPORTANT: Don't forget to free memory.
         * @param  actionType Action type to create.
         * @param  settings   Action settings.
         * @return The action.
         */
        Action* createAction(ActionTypeEnum::ActionType actionType,
                const QString& settings);

};

#endif // ACTIONFACTORY_H
