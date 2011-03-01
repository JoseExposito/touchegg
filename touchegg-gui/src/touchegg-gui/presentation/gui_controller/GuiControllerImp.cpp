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

void GuiControllerImp::execute(GuiEvent event) const {
    switch (event) {
    case READ_GENERAL_PROPERTY:
    case UPDATE_GENERAL_PROPERTY:
    case READ_GESTURE:
    case UPDATE_GESTURE:
    case COMMIT_DATA:
    default:
        break;
    }
}
