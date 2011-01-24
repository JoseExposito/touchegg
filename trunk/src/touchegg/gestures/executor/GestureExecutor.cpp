/**
 * @file /src/touchegg/gestures/executor/GestureExecutor.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureFactory
 * @author José Expósito
 */
#include "GestureExecutor.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

GestureExecutor::GestureExecutor() {
    this->currentGesture = NULL;
}

GestureExecutor::~GestureExecutor() {
    if(this->currentGesture != NULL)
        delete this->currentGesture;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void GestureExecutor::executeGestureStart(GeisGestureType /*type*/,
        GeisGestureId /*id*/, QHash<QString, QVariant> /*attrs*/) {}

void GestureExecutor::executeGestureUpdate(GeisGestureType type,
        GeisGestureId id, QHash<QString, QVariant> attrs) {
    // Si no se está ejecutando ningún gesto creamos uno nuevo
    if(this->currentGesture == NULL) {
        GestureFactory* gf = GestureFactory::getInstance();
        this->currentGesture = gf->createGesture(type, id, attrs);
        this->lastTimestamp  = attrs.value("timestamp").toInt();

        if(this->currentGesture != NULL) {
            this->currentGesture->start();
            this->currentGesture->update();
        }

    // Si es un update del gesto en ejecución
    } else if(this->currentGesture != NULL
            && this->currentGesture->getId() == id) {
        this->lastTimestamp  = attrs.value("timestamp").toInt();
        this->currentGesture->update();

    // Si hay un gesto ejecutándose, pero el timestamp es muy grande es que se
    // ha producido el bug de utouch-geis
    } else if(this->currentGesture != NULL
            && attrs.value("timestamp").toInt() - this->lastTimestamp > 500) {
        // Borramos el gesto que se está ejecutando, aunque por el bug realmente
        // ya no está en ejecución
        delete this->currentGesture;
        this->currentGesture = NULL;
        this->executeGestureUpdate(type, id, attrs);
    }
}

void GestureExecutor::executeGestureFinish(GeisGestureType type,
        GeisGestureId id, QHash<QString, QVariant> attrs) {
    if(this->currentGesture != NULL && this->currentGesture->getId() == id) {
        this->currentGesture->finish();
        this->lastTimestamp  = attrs.value("timestamp").toInt();

        delete this->currentGesture;
        this->currentGesture = NULL;
    }
}
