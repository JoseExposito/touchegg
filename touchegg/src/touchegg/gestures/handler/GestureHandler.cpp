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
// **********                   PRIVATE METHODS                    ********** //
// ************************************************************************** //

Window GestureHandler::getGestureWindow(Window window) const {
    Window topIn = this->getTopLevelWindow(window);
    if(topIn == None)
        return None;

    // Comparamos la top-level window de la ventana pasada con las de las
    // posibles fake-top-level windows (realmente no son top-level, pero son las
    // ventanas que guardan los atributos y de más), devolviendo la ventana que
    // contiene el título, la clase, etc
    Atom atomRet;
    int size;
    unsigned long numItems, bytesAfterReturn;
    unsigned char* propRet;
    long offset = 0;
    long offsetSize = 100;

    Window ret = None;

    int status;
    Atom atomList = XInternAtom(QX11Info::display(),
            "_NET_CLIENT_LIST_STACKING", false);
    do {
        status = XGetWindowProperty(QX11Info::display(),
                QX11Info::appRootWindow(), atomList,
                offset, offsetSize, false, XA_WINDOW, &atomRet, &size,
                &numItems, &bytesAfterReturn, &propRet);

        if(status == Success) {

            Window* aux = (Window*)propRet;
            unsigned int n=0;
            while(ret == None && n<numItems) {
                // Vemos si la top-level window de la ventana de la lista
                // coincide con la de la pasada como argumento
                if(this->getTopLevelWindow(aux[n]) == topIn)
                    ret = aux[n];
                n++;
            }
            offset += offsetSize;
            XFree(propRet);
        }
    } while(status == Success && bytesAfterReturn != 0);

    return ret;
}

Window GestureHandler::getTopLevelWindow(Window window) const {
    Window  root, parent;
    Window* children;
    unsigned int numChildren;

    if(XQueryTree(QX11Info::display(), window, &root, &parent, &children,
            &numChildren) != 0) {
        if(children != NULL)
            XFree(children);

        if(parent == root)
            return window;
        else
            return this->getTopLevelWindow(parent);

    } else {
        return None;
    }
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

    qDebug() << "\n#################################";
    qDebug() << hex << "0x" << this->getGestureWindow(
                    attrs.value(GEIS_GESTURE_ATTRIBUTE_CHILD_WINDOW_ID).toInt());
    qDebug() << "#################################\n";

    // Si no se está ejecutando ningún gesto creamos uno nuevo
    if(this->currentGesture == NULL) {
        this->currentGesture = this->gestureFact->createGesture(type,id,attrs);

        if(this->currentGesture != NULL) {
            // Creamos y asignamos la acción asociada al gesto
            ActionTypeEnum::ActionType actionType =
                    this->config->getAssociatedAction(
                    this->currentGesture->getType()); // TODO Pasarle la clase de la ventana
            QString actionSettings = this->config->getAssociatedSettings(
                    this->currentGesture->getType());
            Window window = this->getGestureWindow(attrs.value(
                    GEIS_GESTURE_ATTRIBUTE_CHILD_WINDOW_ID).toInt());
            this->currentGesture->setAction(this->actionFact->createAction(
                    actionType, actionSettings, window));

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
                && attrs.contains(GEIS_GESTURE_ATTRIBUTE_TOUCHES)
                && this->currentGesture->getAttrs().contains(
                        GEIS_GESTURE_ATTRIBUTE_TOUCHES)
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_TOUCHES, -1)
                   == this->currentGesture->getAttrs().value(
                        GEIS_GESTURE_ATTRIBUTE_TOUCHES, -1)) {
            delete this->currentGesture;
            this->currentGesture = this->gestureFact->createTapAndHold(type, id,
                    attrs);

            if(this->currentGesture != NULL) {
                // Creamos y asignamos la acción asociada al gesto
                // Creamos y asignamos la acción asociada al gesto
                ActionTypeEnum::ActionType actionType =
                        this->config->getAssociatedAction(
                        this->currentGesture->getType()); // TODO Pasarle la clase de la ventana
                QString actionSettings = this->config->getAssociatedSettings(
                        this->currentGesture->getType());
                Window window = this->getGestureWindow(attrs.value(
                        GEIS_GESTURE_ATTRIBUTE_CHILD_WINDOW_ID).toInt());
                this->currentGesture->setAction(this->actionFact->createAction(
                        actionType, actionSettings, window));

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
