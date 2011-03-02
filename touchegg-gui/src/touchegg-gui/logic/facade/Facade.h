/**
 * @file /src/touchegg-gui/logic/facade/Facade.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  Facade
 * @author José Expósito
 */
#ifndef FACADE_H
#define FACADE_H

#include "src/touchegg-gui/logic/application_service/GeneralServiceApp.h"
#include "src/touchegg-gui/logic/application_service/GestureServiceApp.h"
#include "src/touchegg-gui/data/transaction_manager/TransactionManager.h"

/**
 * @~spanish
 * Fachada para agrupar las funciones visibles por la capa de presentación.
 *
 * @~english
 * Façade to group all visible functions  by the presentation tier.
 */
class Facade {

    public:

        /**
         * @~spanish
         * Devuelve los datos de la propiedad indicada.
         * @param  property La propiedad.
         * @return Dichos datos o NULL si no se ha podido acceder.
         *
         * @~english
         * Returns data for the indicated property.
         * @param  property The property.
         * @return Such data or NULL if not able to access.
         */
        virtual GeneralTransfer readGeneralProperty(const QString& property)
                const = 0;

        /**
         * @~spanish
         * Actualiza la propiedad indicada.
         * @param property La propiedad.
         *
         * @~english
         * Updates the configuration of the specific gesture.
         * @param property The property.
         */
        virtual void updateGeneralProperty(const GeneralTransfer& property)
                const = 0;


        /**
         * @~spanish
         * Devuelve los datos del gestos indicado.
         * @param  type Tipo del gesto a actualizar.
         * @return Dichos datos o NULL si no se ha podido acceder.
         *
         * @~english
         * Returns data for the indicated gesture.
         * @param type Type of the gesture to update.
         * @return Such data or NULL if not able to access.
         */
        virtual GestureTransfer readGesture(GestureTypeEnum::GestureType type)
                const = 0;

        /**
         * @~spanish
         * Actualiza la configuración del gesto indicado.
         * @param  gesture Transfer con los datos del gesto a actualizar.
         *
         * @~english
         * Updates the configuration of the specific gesture.
         * @param  gesture Transfer with the data of the gesture to update.
         */
        virtual void updateGesture(const GestureTransfer& gesture) const = 0;

        /**
         * @~spanish
         * Guarda los cambios efectuados.
         *
         * @~english
         * Save changes.
         */
        virtual void commitData() const = 0;

};

#endif // FACADE_H
