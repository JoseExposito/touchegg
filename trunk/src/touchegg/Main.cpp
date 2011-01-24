/**
 * @file /src/touchegg/Main.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @author José Expósito
 */
#include "src/touchegg/gestures/handler/GestureHandler.h"

/**
 * @~spanish
 * Función de inicio de Egg Window Manager.
 * @param argc Número de argumentos recibidos por consola.
 * @param argc Lista de argumentos.
 *
 * @~english
 * Start function for Egg Window Manager.
 * @param argc Number of arguments received by console.
 * @param argc Argument list.
 */
int main(int argc, char** argv) {
    QApplication app(argc, argv);

    GestureHandler gHandler;
    QTimer::singleShot(0, &gHandler, SLOT(run()));

    return app.exec();
}
