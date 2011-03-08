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

void* GuiControllerImp::execute(GuiEvent event, void* data) const {
    switch (event) {
    case READ_GENERAL_PROPERTY: {
        LogicFactory* factory = LogicFactory::getInstance();
        Facade* facade = factory->createFacade();
        QString* property = (QString*)data;
        GeneralTransfer  aux = facade->readGeneralProperty(*property);
        GeneralTransfer* ret = new GeneralTransfer(aux.getField(),
                aux.getValue());
        delete facade;
        return ret;
    }

    case UPDATE_GENERAL_PROPERTY: {
        LogicFactory* factory = LogicFactory::getInstance();
        Facade* facade = factory->createFacade();
        GeneralTransfer* gt = (GeneralTransfer*) data;
        facade->updateGeneralProperty(*gt);
        delete facade;
        return NULL;
    }

    case READ_GESTURE: {
        LogicFactory* factory = LogicFactory::getInstance();
        Facade* facade = factory->createFacade();
        GestureTypeEnum::GestureType* type=(GestureTypeEnum::GestureType*)data;
        GestureTransfer aux = facade->readGesture(*type);
        GestureTransfer* ret = new GestureTransfer(aux.getGestureType(),
                aux.getActionType(), aux.getSettings());
        delete facade;
        return ret;
    }

    case UPDATE_GESTURE: {
        LogicFactory* factory = LogicFactory::getInstance();
        Facade* facade = factory->createFacade();
        GestureTransfer* gt = (GestureTransfer*) data;
        facade->updateGesture(*gt);
        delete facade;
        return NULL;
    }

    case COMMIT_DATA: {
        LogicFactory* factory = LogicFactory::getInstance();
        Facade* facade = factory->createFacade();
        facade->commitData();
        delete facade;
        return NULL;
    }

    default:
        return NULL;
    }
}
