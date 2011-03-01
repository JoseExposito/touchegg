/**
 * @file /src/touchegg-gui/logic/transfer/GeneralServiceAppImp.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GeneralServiceAppImp
 * @author José Expósito
 */
#ifndef GENERALSERVICEAPPIMP_H
#define GENERALSERVICEAPPIMP_H

#include "src/touchegg-gui/logic/application_service/GeneralServiceApp.h"

/**
 * @~spanish
 * Implementación de GeneralServiceApp, ver la documentación en dicha clase.
 *
 * @~english
 * GeneralServiceApp implementation, to see documentation check that class.
 */
class GeneralServiceAppImp : public GeneralServiceApp {

    public:

        GeneralTransfer read(const QString& property);

        void update(const GeneralTransfer& property);
};

#endif // GENERALSERVICEAPPIMP_H
