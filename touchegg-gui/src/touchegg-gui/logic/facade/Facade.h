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

#include "src/touchegg-gui/logic/application_service/ToucheggServiceApp.h"
#include "src/touchegg-gui/data/transaction_manager/TransactionManager.h"


/**
 * @~spanish
 * Fachada para agrupar las funciones visibles por la capa de presentación.
 *
 * @~english
 * Façade to group all visible functions by the presentation tier.
 */
class Facade {

    public:

        /// @see ToucheggDao::read()
        QString toucheggRead(const QString& path) const;

        /// @see ToucheggDao::update()
        void toucheggUpdate(const QString& path, const QString& value) const;

        /// @see ToucheggDao::remove()
        void toucheggRemove(const QString& path) const;

        /// @see ToucheggDao::getApplication()
        QStringList getToucheggUsedApplications() const;

        /// @see ToucheggDao::getUsedGestures()
        QStringList getToucheggUsedGestures(const QString& app) const;

        //----------------------------------------------------------------------

        /// @see TransactionManager::commit()
        void commitData() const;

        /// @see TransactionManager::rollback()
        void rollbackData() const;

};

#endif // FACADE_H
