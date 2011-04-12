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

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * QHash con la configuración.
         * @see initConfig()
         *
         * @~english
         * QHash with the configuration.
         * @see initConfig()
         */
        QHash<QString, QString> settings;

        /**
         * @~spanish
         * Lista con los gestos utilizados por Touchégg, es decir, todos los que
         * tengan alguna acción asociada.
         * Se encuentran directamente en el formato utilizado por GEIS para
         * suscribirse a los mismo.
         *
         * @~english
         * List with the gestures used by Touchégg, this is, all gestures with
         * an  asocied action to it.
         * They are saved directly in the format used for GEIS to subscribe to
         * this gestures.
         */
        QStringList usedGestures;

        /**
         * @~spanish
         * Inicializa el QHash que contiene la configuración. Dicho QHash tendrá
         * como clave una cadena del tipo "touchegg/TWO_FINGERS_TAP/ALL/action"
         * y como valor, en este caso, la acción correspondiente.
         * @param node      Primer hijo del nodo raiz.
         * @param keyString Nombre del nodo raiz.
         *
         * @~english
         * Initializes the QHas that contains the settings. This QHash will have
         * as key a string like "touchegg/TWO_FINGERS_TAP/ALL/action" and as
         * value, in this case, the action.
         * @param node      First child of the root node.
         * @param keyString Name of the root node.
         */
        void initConfig(QDomNode node, const QString& keyString);

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
         * Se encuentran directamente en el formato utilizado por GEIS para
         * suscribirse a los mismo.
         * @return Dicha lista.
         *
         * @~english
         * Returns a list with all gestures with an associate action.
         * They are saved directly in the format used for GEIS to subscribe to
         * this gestures.
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
         * @param  gestureType El gesto que se realiza.
         * @param  appClass Aplicación sobre la que se realiza el gesto.
         * @return Tipo de la acción asociada.
         *
         * @~english
         * Returns the associated action type with a gesture.
         * @param  gestureType The gesture that is made.
         * @param  appClass Application where it is made ​​the gesture.
         * @return Type of associated action.
         */
        ActionTypeEnum::ActionType getAssociatedAction(
                GestureTypeEnum::GestureType gestureType, QString appClass)
                const;

        /**
         * @~spanish
         * Devuelve la configuración de la acción asocada a un gesto indicado.
         * @param  gestureType Gesto indicado.
         * @param  appClass Aplicación sobre la que se realiza el gesto.
         * @return La configuración.
         *
         * @~english
         * Returns the associated config with the indicated gesture.
         * @param  gestureType The gesture.
         * @param  appClass Application where it is made ​​the gesture.
         * @return The settings.
         */
        QString getAssociatedSettings(GestureTypeEnum::GestureType
                gestureType, QString appClass) const;

};

#endif // CONFIG_H
