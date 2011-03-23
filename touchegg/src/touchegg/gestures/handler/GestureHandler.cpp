/**
 * @file /src/touchegg/gestures/handler/GestureHandler.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureHandler
 * @author José Expósito
 */
#include "GestureHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

GestureHandler::GestureHandler() : QThread() {
    this->currentGesture = NULL;

    this->gestureFact = GestureFactory::getInstance();
    this->actionFact  = ActionFactory::getInstance();
    this->config      = Config::getInstance();

    this->timerTap = new QTimer(this);
    this->timerTap->setInterval(this->config->getTapAndHoldTime());
    connect(this->timerTap, SIGNAL(timeout()), this, SLOT(executeTap()));
}

GestureHandler::~GestureHandler() {
    if(this->currentGesture != NULL)
        delete this->currentGesture;
    delete timerTap;
}


// ************************************************************************** //
// **********                     PRIVATE SLOTS                    ********** //
// ************************************************************************** //

void GestureHandler::executeTap() {
    this->timerTap->stop();

    if(this->currentGesture != NULL) {
        qDebug() << "    Gesture Update";
        qDebug() << "    Gesture Finish";

        this->currentGesture->update();
        this->currentGesture->finish();

        delete this->currentGesture;
        this->currentGesture = NULL;
    }
}


// ************************************************************************** //
// **********                     PUBLIC SLOTS                     ********** //
// ************************************************************************** //

void GestureHandler::executeGestureStart(GeisGestureType type,
        GeisGestureId id, const QHash<QString, QVariant>& attrs) {
    // Si no se está ejecutando ningún gesto creamos uno nuevo
    if(this->currentGesture == NULL) {
        this->currentGesture = this->gestureFact->createGesture(type,id,attrs);

        if(this->currentGesture != NULL) {
            // Creamos y asignamos la acción asociada al gesto
            ActionTypeEnum::ActionType actionType =
                    this->config->getAssociatedAction(
                    this->currentGesture->getType());
            QString actionSettings = this->config->getAssociatedSettings(
                    this->currentGesture->getType());
            this->currentGesture->setAction(this->actionFact->createAction(
                    actionType, actionSettings));

            // Mostramos información sobre el gesto
            qDebug() << "[+] New gesture:";
            qDebug() << "\tType   -> " << GestureTypeEnum::getValue(
                    this->currentGesture->getType());
            qDebug() << "\tAction -> " << ActionTypeEnum::getValue(actionType);
            qDebug() << "    Gesture Start";

            // Ejecutamos el gesto
            this->currentGesture->start();
        }

    // Si el timer está en ejecución podemos hacer un tap&hold
    } else if(this->timerTap->isActive()) {
        this->timerTap->stop();

        // El nuevo gesto debe ser un drag con igual número de dedos que el tap
        // en ejecución para que se considere un tap&hold
        if(type == GEIS_GESTURE_PRIMITIVE_DRAG
                && attrs.contains("touches")
                && this->currentGesture->getAttrs().contains("touches")
                && attrs.value("touches", -1)
                   == this->currentGesture->getAttrs().value("touches", -1)) {
            delete this->currentGesture;
            this->currentGesture = this->gestureFact->createTapAndHold(type, id,
                    attrs);

            if(this->currentGesture != NULL) {
                // Creamos y asignamos la acción asociada al gesto
                ActionTypeEnum::ActionType actionType =
                        this->config->getAssociatedAction(
                        this->currentGesture->getType());
                QString actionSettings = this->config->getAssociatedSettings(
                        this->currentGesture->getType());
                this->currentGesture->setAction(this->actionFact->createAction(
                        actionType, actionSettings));

                // Mostramos información sobre el gesto
                qDebug() << "[+] New gesture:";
                qDebug() << "\tType   -> " << GestureTypeEnum::getValue(
                        this->currentGesture->getType());
                qDebug() << "\tAction -> "
                         << ActionTypeEnum::getValue(actionType);
                qDebug() << "    Gesture Start";

                // Ejecutamos el gesto
                this->currentGesture->start();
            }

        // Si no es un tap&hold ejecutamos el tap con normalidad
        } else {
            this->executeTap();
        }

    }
}

void GestureHandler::executeGestureUpdate(GeisGestureType type,
        GeisGestureId id,const QHash<QString, QVariant>& attrs) {
    // Si es un update del gesto en ejecución
    if(this->currentGesture != NULL && this->currentGesture->getId() == id) {
        qDebug() << "    Gesture Update";
        this->currentGesture->setAttrs(attrs);
        this->currentGesture->update();

    // Si no se está ejecutando ningún gesto es que es un TAP o un gesto no
    // soportado
    } else if(this->currentGesture == NULL) {
        // Si es un TAP, esperamos un poco para que se pueda usar un tap&hold
        this->executeGestureStart(type,id,attrs);
        if(this->currentGesture != NULL) {
            this->timerTap->start();
        }
    }
}

void GestureHandler::executeGestureFinish(GeisGestureType /*type*/,
        GeisGestureId /*id*/, const QHash<QString, QVariant>& attrs) {
    if(this->currentGesture != NULL) {
        qDebug() << "    Gesture Finish";
        this->currentGesture->setAttrs(attrs);
        this->currentGesture->finish();
        delete this->currentGesture;
        this->currentGesture = NULL;
    }
}
