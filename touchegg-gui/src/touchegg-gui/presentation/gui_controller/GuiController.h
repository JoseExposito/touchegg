/**
 * @file /src/touchegg-gui/presentation/gui_controller/GuiController.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GuiController
 * @author José Expósito
 */
#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/presentation/gui_event/GuiEvent.h"

/**
 * @~spanish
 * Maneja la interfaz.
 *
 * @~english
 * Manages the GUI.
 */
class GuiController {

    protected:

        /**
         * @~spanish
         * Única instancia de la clase.
         *
         * @~english
         * Single instance of the class.
         */
        static GuiController* instance;

        // Hide constructors
        GuiController(){}
        GuiController(const GuiController&){}
        const GuiController& operator=(const GuiController& gc) { return gc; }

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
        static GuiController* getInstance();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Realiza una acción dependiendo del tipo de evento que reciba.
         * @param event El evento.
         *
         * @~english
         * Executes an action depending on the type of event that receive.
         * @param event The event.
         */
        virtual void execute(GuiEvent event) const = 0;

};

#endif // GUICONTROLLER_H
