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
#include "src/touchegg/gestures/types/GestureTypeEnum.h"
#include "src/touchegg/actions/types/ActionTypeEnum.h"

/**
 * @~spanish
 * Singleton que facilita el acceso a la configuración.
 *
 * @~english
 * Singleton that provides access to the configuration.
 */
class Config {

    private:

        // Constants to access to the settings
        static const char* USR_SHARE_CONFIG_FILE;
        static const char* HOME_CONFIG_FILE; // Sumarle el $HOME por delante
        static const char* HOME_CONFIG_DIR;

        static const char* TAP_AND_HOLD_TIME;


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
        Config(const Config&);
        const Config& operator = (const Config&);

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
        static Config* getInstance();

        /**
         * @~spanish
         * (Re)Carga la configuración.
         *
         * @~english
         * (Re)Load configuration.
         */
        static void loadConfig();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve una lista de todos los gestos con una acción asociada.
         * @return Dicha lista.
         *
         * @~english
         * Returns a list with all gestures with an associate action.
         * @return The list.
         */
        QStringList getUsedGestures() const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el tiempo, en milisegundos, en el que se puede ejecutar un
         * tap&hold.
         * @return El tiempo.
         *
         * @~english
         * Returns the time, in milliseconds, which can run a tap & hold.
         * @return The time.
         */
        int getTapAndHoldTime() const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el tipo de acción asociada a el gesto indicado.
         * @param  gestureType Gesto indicado.
         * @return Tipo de la acción asociada.
         *
         * @~english
         * Returns the associated action type with a gesture.
         * @param  gestureType The gesture.
         * @return Type of associated action.
         */
        ActionTypeEnum::ActionType getAssociatedAction(
                GestureTypeEnum::GestureType gestureType) const;

        /**
         * @~spanish
         * Devuelve la configuración de la acción asocada a un gesto indicado.
         * @param  gestureType Gesto indicado.
         * @return La configuración.
         *
         * @~english
         * Returns the associated config with the indicated gesture.
         * @param  gestureType The gesture.
         * @return The settings.
         */
        QString getAssociatedSettings(GestureTypeEnum::GestureType
                gestureType) const;

};

#endif // CONFIG_H
