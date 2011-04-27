/**
 * @file /src/touchegg-gui/logic/application_service/ToucheggServiceApp.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ToucheggServiceApp
 * @author José Expósito
 */
#ifndef TOUCHEGGSERVICEAPP_H
#define TOUCHEGGSERVICEAPP_H

#include "src/touchegg-gui/data/transaction_manager/TransactionManager.h"
#include "src/touchegg-gui/data/dao/ToucheggDao.h"

/**
 * @~spanish
 * Servicio de aplicación para facilitar la configuración de Touchégg.
 *
 * @~english
 * Application service to facilitate Touchégg configuration.
 */
class ToucheggServiceApp {

    public:

        /// @see ToucheggDao::read()
        QString read(const QString& path) const;

        /// @see ToucheggDao::update()
        void update(const QString& path, const QString& value) const;

        /// @see ToucheggDao::remove()
        void remove(const QString& path) const;

        /// @see ToucheggDao::getUsedApplication()
        QStringList getUsedApplications() const;

        /// @see ToucheggDao::getUsedGestures()
        QStringList getUsedGestures(const QString& app) const;
};

#endif // TOUCHEGGSERVICEAPP_H
