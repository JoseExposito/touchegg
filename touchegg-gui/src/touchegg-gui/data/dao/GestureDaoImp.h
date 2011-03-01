/**
 * @file /src/touchegg-gui/data/dao/GestureDaoImp.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureDaoImp
 * @author José Expósito
 */
#ifndef GESTUREDAOIMP_H
#define GESTUREDAOIMP_H

#include "src/touchegg-gui/data/dao/GestureDao.h"

/**
 * @~spanish
 * Implementación de GestureDao, ver la documentación en dicha clase.
 *
 * @~english
 * GestureDao implementation, to see documentation check that class.
 */
class GestureDaoImp : public GestureDao {

    private:

        QSettings* settings;

    public:

        GestureDaoImp(QSettings* settings);

        GestureTransfer read(GestureTypeEnum::GestureType type);

        void update(const GestureTransfer& gesture);

};

#endif // GESTUREDAOIMP_H
