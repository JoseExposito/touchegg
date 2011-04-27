/**
 * @file /src/touchegg-gui/logic/facade/Facade.cpp
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
#include "Facade.h"

// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

QString Facade::toucheggRead(const QString& path) const {
    ToucheggServiceApp sa;
    return sa.read(path);
}

void Facade::toucheggUpdate(const QString& path, const QString& value) const {
    ToucheggServiceApp sa;
    sa.update(path, value);
}

void Facade::toucheggRemove(const QString& path) const {
    ToucheggServiceApp sa;
    return sa.remove(path);
}

QStringList Facade::getToucheggUsedApplications() const {
    ToucheggServiceApp sa;
    return sa.getUsedApplications();
}

QStringList Facade::getToucheggUsedGestures(const QString& app) const {
    ToucheggServiceApp sa;
    return sa.getUsedGestures(app);
}

//------------------------------------------------------------------------------

void Facade::commitData() const {
    TransactionManager* tm = TransactionManager::getInstance();
    tm->commit();
}

void Facade::rollbackData() const {
    TransactionManager* tm = TransactionManager::getInstance();
    tm->rollback();
}
