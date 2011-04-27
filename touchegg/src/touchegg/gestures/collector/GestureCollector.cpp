/**
 * @file /src/touchegg/gestures/collector/GestureCollector.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureCollector
 * @author José Expósito
 */
#include "GestureCollector.h"


// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

void GestureCollector::deviceAdded(void* cookie, GeisInputDeviceId /*id*/,
        void* /*attrs*/) {
    GestureCollector* gc = (GestureCollector*)cookie;
    gc->semDevices->release();
}

void GestureCollector::deviceRemoved(void* cookie, GeisInputDeviceId /*id*/,
        void* /*attrs*/) {
    GestureCollector* gc = (GestureCollector*)cookie;
    gc->semDevices->acquire();
}

//------------------------------------------------------------------------------

void GestureCollector::gestureAdded(void* /*cookie*/, GeisGestureType /*type*/,
        GeisGestureId /*id*/, GeisSize /*numAttrs*/,
        GeisGestureAttr* /*attrs*/) {}

void GestureCollector::gestureRemoved(void* /*cookie*/, GeisGestureType/*type*/,
        GeisGestureId /*id*/, GeisSize /*numAttrs*/,
        GeisGestureAttr* /*attrs*/) {}

void GestureCollector::gestureStart(void* cookie, GeisGestureType type,
        GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs) {
    GestureCollector* gc = (GestureCollector*)cookie;
    emit gc->executeGestureStart(type, id, getGestureAttrs(numAttrs, attrs));
}

void GestureCollector::gestureUpdate(void* cookie, GeisGestureType type,
        GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs) {
    GestureCollector* gc = (GestureCollector*)cookie;
    emit gc->executeGestureUpdate(type, id, getGestureAttrs(numAttrs, attrs));
}

void GestureCollector::gestureFinish(void* cookie, GeisGestureType type,
        GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs) {
    GestureCollector* gc = (GestureCollector*)cookie;
    emit gc->executeGestureFinish(type, id, getGestureAttrs(numAttrs, attrs));
}


// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

QHash<QString, QVariant> GestureCollector::getGestureAttrs(GeisSize numAttrs,
        GeisGestureAttr* attrs) {
    QHash<QString, QVariant> ret;

    for(unsigned int n=0; n<numAttrs; n++) {
        QVariant value;

        switch (attrs[n].type) {
        case GEIS_ATTR_TYPE_BOOLEAN:
            value = attrs[n].boolean_val;
            break;
        case GEIS_ATTR_TYPE_FLOAT:
            value = attrs[n].float_val;
            break;
        case GEIS_ATTR_TYPE_INTEGER:
            value = attrs[n].integer_val;
            break;
        case GEIS_ATTR_TYPE_STRING:
            value = attrs[n].string_val;
            break;
        case GEIS_ATTR_TYPE_POINTER:
        case GEIS_ATTR_TYPE_UNKNOWN:
            break;
        }

        ret.insert(attrs[n].name, value);
    }

    return ret;
}


// ************************************************************************** //
// **********                   PROTECTED METHOS                   ********** //
// ************************************************************************** //

void GestureCollector::run() {
    this->semDevices = new QSemaphore(0);

    GeisXcbWinInfo xcbWinInfo;
    xcbWinInfo.display_name = NULL;
    xcbWinInfo.screenp      = NULL;
    xcbWinInfo.window_id    = QX11Info::appRootWindow(); // All gestures

    GeisWinInfo  winInfo;
    winInfo.win_type = GEIS_XCB_FULL_WINDOW;
    winInfo.win_info = &xcbWinInfo;

    // Inicializamos geis
    GeisInstance geisInstance;
    if(geis_init(&winInfo, &geisInstance) != GEIS_STATUS_SUCCESS) {
        qFatal("geis_init: Can't initialize utouch-geis");
    }

    // Estamos atentos a si se conectan o desconectan dispositivos de entrada
    // para no recoger gestos si no hay ninguno conectado
    GeisInputFuncs devicesFuncs;
    devicesFuncs.added = GestureCollector::deviceAdded;
    devicesFuncs.removed = GestureCollector::deviceRemoved;
    geis_input_devices(geisInstance, &devicesFuncs, this);

    // Establecemos las funciones de callback
    GeisGestureFuncs gestureFuncs;
    gestureFuncs.added   = GestureCollector::gestureAdded;
    gestureFuncs.removed = GestureCollector::gestureRemoved;
    gestureFuncs.start   = GestureCollector::gestureStart;
    gestureFuncs.update  = GestureCollector::gestureUpdate;
    gestureFuncs.finish  = GestureCollector::gestureFinish;

    // Nos suscribimos solo a los gestos que se vayan a usar
    Config* cfg = Config::getInstance();
    QStringList subscribeList = cfg->getUsedGestures();
    if(subscribeList.length() == 0)
        qFatal("Exiting, no gestures added to the configuration");
    char** subscribe = new char*[subscribeList.size() + 1];

    // Pasamos de QStringList a char**
    for (int i = 0; i < subscribeList.size(); i++) {
        subscribe[i] = new char[
                strlen(subscribeList.at(i).toStdString().c_str())+1];
        memcpy(subscribe[i], subscribeList.at(i).toStdString().c_str(),
                strlen(subscribeList.at(i).toStdString().c_str())+1);
    }
    subscribe[subscribeList.size()] = ((char)NULL);

    if(geis_subscribe(geisInstance, GEIS_ALL_INPUT_DEVICES,
            (const char**)subscribe, &gestureFuncs, this)
            != GEIS_STATUS_SUCCESS)
        qFatal("geis_subscribe: Can't subscribe to gestures");


    // Liberamos el char**
    int i = 0;
    while (subscribe[i]) {
        delete subscribe[i];
        i++;
    }
    delete subscribe;

    // Obtenemos los gestos
    int fd = -1;
    geis_configuration_get_value(geisInstance, GEIS_CONFIG_UNIX_FD, &fd);

    fd_set read_fds;
    for(;;) {
        // Si no hay dispositivos conectados esperamos
        if(this->semDevices->available() == 0)
            this->semDevices->acquire();

        FD_ZERO(&read_fds);
        FD_SET(fd, &read_fds);
        int sstat = select(fd+1, &read_fds, NULL, NULL, NULL);

        if (sstat < 0)
            qFatal("Error");

        if (FD_ISSET(fd, &read_fds))
          geis_event_dispatch(geisInstance);
    }

    geis_finish(geisInstance);
    delete this->semDevices;
}
