/**
 * @file /src/touchegg-gui/presentation/gui_controller/GuiControllerImp.cpp
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
#include "GuiControllerImp.h"

// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void GuiControllerImp::execute(GuiEvent event, void* data) const {
    switch (event) {
    case READ_GENERAL_PROPERTY:
        break;

    case UPDATE_GENERAL_PROPERTY:
        break;

    case READ_GESTURE:
        break;

    case UPDATE_GESTURE: {
        LogicFactory* factory = LogicFactory::getInstance();
        Facade* facade = factory->createFacade();
        GestureTransfer* gt = (GestureTransfer*) data;
        facade->updateGesture(*gt);
        delete facade;
        break;
    }

    case COMMIT_DATA:
        break;
    }
}
