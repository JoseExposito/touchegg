/**
 * @file /src/touchegg-gui/presentation/gui_controller/GuiController.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GuiController
 * @author José Expósito
 */
#include "GuiController.h"
#include "src/touchegg-gui/presentation/gui_controller/GuiControllerImp.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

GuiController* GuiController::instance = NULL;

GuiController* GuiController::getInstance() {
    if(GuiController::instance == NULL)
        GuiController::instance = new GuiControllerImp;

    return GuiController::instance;
}

