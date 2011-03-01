/**
 * @file /src/touchegg/Touchegg.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  Touchegg
 * @author José Expósito
 */
#include "Touchegg.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

Touchegg::Touchegg() {
    // Inicializamos la configuración
    Config::loadConfig();

    // Inicializamos los atributos
    this->gestureCollector = new GestureCollector();
    this->gestureHandler   = new GestureHandler();

    // Conectamos GeisLoop con GestureHandler para que el último trate los
    // eventos que recoge el primero.
    qRegisterMetaType<GeisGestureType>("GeisGestureType");
    qRegisterMetaType<GeisGestureId>("GeisGestureId");

    connect(gestureCollector, SIGNAL(executeGestureStart(
            GeisGestureType,GeisGestureId,QHash<QString,QVariant>)),
            gestureHandler, SLOT(executeGestureStart(
            GeisGestureType,GeisGestureId,QHash<QString,QVariant>)));
    connect(gestureCollector, SIGNAL(executeGestureUpdate(
            GeisGestureType,GeisGestureId,QHash<QString,QVariant>)),
            gestureHandler, SLOT(executeGestureUpdate(
            GeisGestureType,GeisGestureId,QHash<QString,QVariant>)));
    connect(gestureCollector, SIGNAL(executeGestureFinish(
            GeisGestureType,GeisGestureId,QHash<QString,QVariant>)),
            gestureHandler, SLOT(executeGestureFinish(
            GeisGestureType,GeisGestureId,QHash<QString,QVariant>)));

    // Lanzamos GeisLoop en un hilo para no congelar el bucle de eventos de Qt
    this->gestureCollector->start();
}

Touchegg::~Touchegg() {
    if(this->gestureCollector->isRunning())
        this->gestureCollector->exit();

    delete this->gestureCollector;
    delete this->gestureHandler;
}
