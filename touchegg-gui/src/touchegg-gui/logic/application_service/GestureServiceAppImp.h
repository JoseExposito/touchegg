/**
 * @file /src/touchegg-gui/logic/transfer/GestureServiceAppImp.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureServiceAppImp
 * @author José Expósito
 */
#ifndef GESTURESERVICEAPPIMP_H
#define GESTURESERVICEAPPIMP_H

#include "src/touchegg-gui/logic/application_service/GestureServiceApp.h"

/**
 * @~spanish
 * Implementación de GestureServiceApp, ver la documentación en dicha clase.
 *
 * @~english
 * GestureDao GestureServiceApp, to see documentation check that class.
 */
class GestureServiceAppImp : public GestureServiceApp {

    public:

        GestureTransfer read(GestureTypeEnum::GestureType type);

        void update(const GestureTransfer& gesture);
};

#endif // GESTURESERVICEAPPIMP_H
