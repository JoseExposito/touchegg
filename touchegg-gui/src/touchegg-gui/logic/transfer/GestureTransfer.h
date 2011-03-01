/**
 * @file /src/touchegg-gui/logic/transfer/GestureTransfer.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureTransfer
 * @author José Expósito
 */
#ifndef GESTURETRANSFER_H
#define GESTURETRANSFER_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/logic/type/GestureTypeEnum.h"
#include "src/touchegg-gui/logic/type/ActionTypeEnum.h"

/**
 * @~spanish
 * Clase para transferir los datos de los gestos.
 *
 * @~english
 * Class to transfer gestures settings.
 */
class GestureTransfer {

    private:

        /**
         * @~spanish
         * Tipo del gesto a leer/escribir.
         *
         * @~english
         * Gesture type to read/write.
         */
        GestureTypeEnum::GestureType gestureType;

        /**
         * @~spanish
         * Tipo de la acción a leer/escribir.
         *
         * @~english
         * Action type to read/write.
         */
        ActionTypeEnum::ActionType actionType;

        /**
         * @~spanish
         * Configuración del gesto a leer/escribir.
         *
         * @~english
         * Gesture settings to read/write.
         */
        QString settings;

    public:

        /**
         * @~spanish
         * Constructor.
         * @param gestureType Tipo del gesto a leer/escribir.
         *
         * @~english
         * Constructor.
         * @param gestureType Gesture type to read/write.
         */
        GestureTransfer(GestureTypeEnum::GestureType gestureType);

        /**
         * @~spanish
         * Constructor.
         * @param gestureType Tipo del gesto a leer/escribir.
         * @param actionType  Tipo de la acción a leer/escribir.
         * @param settings    Configuración del gesto a leer/escribir.
         *
         * @~english
         * Constructor.
         * @param gestureType Gesture type to read/write.
         * @param actionType  Action type to read/write.
         * @param settings    Gesture settings to read/write.
         */
        GestureTransfer(GestureTypeEnum::GestureType gestureType,
                        ActionTypeEnum::ActionType actionType,
                        const QString& settings);

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuleve el tipo de gesto a leer/escribir.
         * @return El tipo.
         *
         * @~english
         * Returns the gesture type to read/write.
         * @return The type.
         */
        GestureTypeEnum::GestureType getGestureType() const;

        /**
         * @~spanish
         * Devuleve el tipo de acción a leer/escribir.
         * @return El tipo.
         *
         * @~english
         * Returns the action type to read/write.
         * @return The type.
         */
        ActionTypeEnum::ActionType getActionType() const;

        /**
         * @~spanish
         * Devuleve la configuración del gesto a leer/escribir.
         * @return La configuración.
         *
         * @~english
         * Returns the gesture settings to read/write.
         * @return The settings.
         */
        const QString& getSettings() const;

        /**
         * @~spanish
         * Establece el tipo de gesto a leer/escribir.
         * @param gestureType El tipo.
         *
         * @~english
         * Sets the type of the gesture to read/write.
         * @param gestureType The type.
         */
        void setGestureType(GestureTypeEnum::GestureType gestureType);

        /**
         * @~spanish
         * Establece el tipo de gesto a leer/escribir.
         * @param gestureType El tipo.
         *
         * @~english
         * Sets the type of the gesture to read/write.
         * @param gestureType The type.
         */
        void setActionType(ActionTypeEnum::ActionType actionType);

        /**
         * @~spanish
         * Establece la configuración del gesto a leer/escribir.
         * @param settings La configuración.
         *
         * @~english
         * Sets the settings of the gesture to read/write.
         * @param settings The settings.
         */
        void setSettings(const QString& settings);

};

#endif // GESTURETRANSFER_H
