/**
 * @file /src/touchegg-gui/presentation/gui_controller/GuiControllerImp.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GuiControllerImp
 * @author José Expósito
 */
#ifndef GUICONTROLLERIMP_H
#define GUICONTROLLERIMP_H

#include "src/touchegg-gui/presentation/gui_controller/GuiController.h"
#include "src/touchegg-gui/logic/factory/LogicFactory.h"

/**
 * @~spanish
 * Implementación de GuiController, ver la documentación en dicha clase.
 *
 * @~english
 * GuiController implementation, to see documentation check that class.
 */
class GuiControllerImp : public GuiController {

    public:

        void* execute(GuiEvent event, void* data) const;

};

#endif // GUICONTROLLERIMP_H
