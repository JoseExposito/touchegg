/**
 * @file /src/touchegg-gui/logic/facade/FacadeImp.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  FacadeImp
 * @author José Expósito
 */
#ifndef FACADEIMP_H
#define FACADEIMP_H

#include "src/touchegg-gui/logic/facade/Facade.h"
#include "src/touchegg-gui/logic/factory/LogicFactory.h"

/**
 * @~spanish
 * Implementación de Facade, ver la documentación en dicha clase.
 *
 * @~english
 * Facade implementation, to see documentation check that class.
 */
class FacadeImp : public Facade {

    public:

        GeneralTransfer readGeneralProperty(const QString& property) const;

        void updateGeneralProperty(const GeneralTransfer& property) const;

        GestureTransfer readGesture(GestureTypeEnum::GestureType type) const;

        void updateGesture(const GestureTransfer& gesture) const;

        void commitData() const;

};

#endif // FACADEIMP_H
