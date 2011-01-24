/**
 * @file /src/touchegg/config/Config.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  Config
 * @author José Expósito
 */
#ifndef CONFIG_H
#define CONFIG_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/Action.h"
#include "src/touchegg/actions/RightButtonClick.h"
#include "src/touchegg/actions/MiddleButtonClick.h"
#include "src/touchegg/actions/MouseWheelUp.h"
#include "src/touchegg/actions/MouseWheelDown.h"
#include "src/touchegg/actions/MinimizeWindow.h"
#include "src/touchegg/actions/MaximizeRestoreWindow.h"
#include "src/touchegg/actions/CloseWindow.h"
#include "src/touchegg/actions/ResizeWindow.h"
#include "src/touchegg/actions/ShowDesktop.h"
#include "src/touchegg/actions/ChangeDesktop.h"
#include "src/touchegg/actions/SendKeys.h"


/**
 * @~spanish
 * Singleton que facilita el acceso a la configuración.
 *
 * @~english
 * Singleton that provides access to the configuration.
 */
class Config {

    private:

        // Constantes para acceder a la configuración
        static const char* USR_SHARE_CONFIG_FILE;
        static const char* HOME_CONFIG_FILE; // Sumarle el $HOME por delante

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Configuración usada.
         *
         * @~english
         * Configuration used.
         */
        QSettings* settings;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Única instancia de la clase.
         *
         * @~english
         * Single instance of the class.
         */
        static Config* instance;

        // Hide constructors
        Config();
        Config(const Config&){}
        const Config& operator = (const Config& c){return c;}

    public:

        // Tipos de gestos
        static const char* TWO_FINGERS_TAP;
        static const char* THREE_FINGERS_TAP;
        static const char* FOUR_FINGERS_TAP;
        static const char* FIVE_FINGERS_TAP;

        static const char* THREE_FINGERS_PINCH;

        static const char* TWO_FINGERS_DRAG_UP;
        static const char* TWO_FINGERS_DRAG_DOWN;
        static const char* TWO_FINGERS_DRAG_LEFT;
        static const char* TWO_FINGERS_DRAG_RIGHT;

        static const char* THREE_FINGERS_DRAG_UP;
        static const char* THREE_FINGERS_DRAG_DOWN;
        static const char* THREE_FINGERS_DRAG_LEFT;
        static const char* THREE_FINGERS_DRAG_RIGHT;

        static const char* FOUR_FINGERS_DRAG_UP;
        static const char* FOUR_FINGERS_DRAG_DOWN;
        static const char* FOUR_FINGERS_DRAG_LEFT;
        static const char* FOUR_FINGERS_DRAG_RIGHT;

        // Tipos de acciones
        static const char* RIGHT_BUTTON_CLICK;
        static const char* MIDDLE_BUTTON_CLICK;
        static const char* MOUSE_WHELL_UP;
        static const char* MOUSE_WHELL_DOWN;
        static const char* MINIMIZE_WINDOW;
        static const char* MAXIMIZE_RESTORE_WINDOW;
        static const char* CLOSE_WINDOW;
        static const char* RESIZE_WINDOW;
        static const char* SHOW_DESKTOP;
        static const char* CHANGE_DESKTOP;
        static const char* SEND_KEYS;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Único método para obtener una instancia de la clase.
         * @return La única instancia de la clase.
         *
         * @~english
         * Only method to get an instance of the class.
         * @return The single instance of the class.
         */
        static Config* getInstance();

        /**
         * @~spanish
         * Devuelve la acción asociada a el gesto indicado.
         * @param gesture Gesto indicado.
         * @return Acción asociada.
         *
         * @~english
         * Returns the associated action with a gesture.
         * @param gesture The gesture.
         * @return The associated action.
         */
        Action* getAssociatedAction(const char* gesture) const;

};

#endif // CONFIG_H
