/**
 * @file /src/touchegg-gui/data/dao/GeneralDaoImp.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GeneralDaoImp
 * @author José Expósito
 */
#ifndef GENERALDAOIMP_H
#define GENERALDAOIMP_H

#include "src/touchegg-gui/data/dao/GeneralDao.h"

/**
 * @~spanish
 * Implementación de GeneralDao, ver la documentación en dicha clase.
 *
 * @~english
 * GeneralDao implementation, to see documentation check that class.
 */
class GeneralDaoImp : public GeneralDao {

    private:

        QSettings* settings;

    public:

        GeneralDaoImp(QSettings* settings);

        GeneralTransfer read(const QString& property);

        void update(const GeneralTransfer& property);

};

#endif // GENERALDAOIMP_H
