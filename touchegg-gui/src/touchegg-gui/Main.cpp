/**
 * @file /src/touchegg-gui/Main.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @author José Expósito
 */
#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/presentation/main_window/MainWindow.h"

/**
 * @~spanish
 * Función de inicio de Touchégg-GUI.
 * @param argc Número de argumentos recibidos por consola.
 * @param argv Lista de argumentos.
 *
 * @~english
 * Start function for Touchégg-GUI.
 * @param argc Number of arguments received by console.
 * @param argv Argument list.
 */
int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();

    // TEST!
    /*LogicFactory* factory = LogicFactory::getInstance();
    Facade*       facade  = factory->createFacade();

    qDebug() << "Valor de la propiedad general tap_and_hold_time:";
    qDebug() << facade->readGeneralProperty("tap_and_hold_time").getValue();

    qDebug() << "Modificandola a 350, leyendo nuevo valor:";
    GeneralTransfer gt("tap_and_hold_time", "350");
    facade->updateGeneralProperty(gt);
    qDebug() << facade->readGeneralProperty("tap_and_hold_time").getValue();

    //--------------------------------------------------------------------------

    qDebug() << "Leyendo las propiedades del gesto TWO_FINGERS_DRAG_DOWN:";
    GestureTransfer gt1 = facade->readGesture(
            GestureTypeEnum::TWO_FINGERS_DRAG_DOWN);
    qDebug() << GestureTypeEnum::getValue(gt1.getGestureType());
    qDebug() << ActionTypeEnum::getValue(gt1.getActionType());
    qDebug() << gt1.getSettings();

    qDebug() << "Modificando el gesto y leyendo el nuevo valor:";
    GestureTransfer gt2(GestureTypeEnum::TWO_FINGERS_DRAG_DOWN,
            ActionTypeEnum::DRAG_AND_DROP, "Soy la nueva cfg");
    facade->updateGesture(gt2);
    qDebug() << GestureTypeEnum::getValue(gt2.getGestureType());
    qDebug() << ActionTypeEnum::getValue(gt2.getActionType());
    qDebug() << gt2.getSettings();

    //--------------------------------------------------------------------------

    qDebug() << "Guardando datos";
    facade->commitData();*/
}
