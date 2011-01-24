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
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

GestureExecutor GestureHandler::gestureExecutor;

void GestureHandler::gestureAdded(void* /*cookie*/, GeisGestureType /*type*/,
        GeisGestureId /*id*/, GeisSize /*numAttrs*/,
        GeisGestureAttr* /*attrs*/) {}

void GestureHandler::gestureRemoved(void* /*cookie*/, GeisGestureType /*type*/,
        GeisGestureId /*id*/, GeisSize /*numAttrs*/,
        GeisGestureAttr* /*attrs*/) {}

void GestureHandler::gestureStart(void* /*cookie*/, GeisGestureType type,
        GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs) {
    gestureExecutor.executeGestureStart(type, id,
        getGestureAttrs(numAttrs, attrs));
}

void GestureHandler::gestureUpdate(void* /*cookie*/, GeisGestureType type,
        GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs) {
    gestureExecutor.executeGestureUpdate(type, id,
        getGestureAttrs(numAttrs, attrs));
}

void GestureHandler::gestureFinish(void* /*cookie*/, GeisGestureType type,
        GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs) {
    gestureExecutor.executeGestureFinish(type, id,
        getGestureAttrs(numAttrs, attrs));
}


// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

QHash<QString, QVariant> GestureHandler::getGestureAttrs(GeisSize numAttrs,
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
        case GEIS_ATTR_TYPE_UNKNOWN:
            break;
        }

        ret.insert(attrs[n].name, value);
    }

    return ret;
}


// ************************************************************************** //
// **********                     PUBLIC SLOTS                     ********** //
// ************************************************************************** //

void GestureHandler::run() {
    GeisInstance instance;
    GeisWinInfo  winInfo;

    GeisXcbWinInfo xcbWinInfo;
    xcbWinInfo.display_name = NULL;
    xcbWinInfo.screenp      = NULL;
    // Root window para recibir todos los gestos
    xcbWinInfo.window_id    = QX11Info::appRootWindow();

    winInfo.win_type = GEIS_XCB_FULL_WINDOW;
    winInfo.win_info = &xcbWinInfo;

    // Inicializamos geis
    if(geis_init(&winInfo, &instance) != GEIS_STATUS_SUCCESS) {
        qFatal("geis_init: Can't initialize utouch-geis");
    }

    // Establecemos las funciones de callback
    GeisGestureFuncs gestureFuncs;
    gestureFuncs.added   = GestureHandler::gestureAdded;
    gestureFuncs.removed = GestureHandler::gestureRemoved;
    gestureFuncs.start   = GestureHandler::gestureStart;
    gestureFuncs.update  = GestureHandler::gestureUpdate;
    gestureFuncs.finish  = GestureHandler::gestureFinish;

    // Nos subscribimos a los gestos que queremos recibir
    const char* subscribe[] = {
        GEIS_GESTURE_TYPE_TAP2,
        GEIS_GESTURE_TYPE_TAP3,
        GEIS_GESTURE_TYPE_TAP4,
        GEIS_GESTURE_TYPE_TAP5,
        GEIS_GESTURE_TYPE_DRAG2,
        GEIS_GESTURE_TYPE_DRAG3,
        GEIS_GESTURE_TYPE_DRAG4,
        GEIS_GESTURE_TYPE_PINCH3,
        NULL
    };

    if(geis_subscribe(instance, GEIS_ALL_INPUT_DEVICES, subscribe,
                &gestureFuncs, NULL) != GEIS_STATUS_SUCCESS)
            qFatal("geis_subscribe: Can't subscribe to gestures");

    // Thanks to the geistest developer for this code
    int fd = -1;
    geis_configuration_get_value(instance, GEIS_CONFIG_UNIX_FD, &fd);

    for(;;) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(fd, &read_fds);
        int sstat = select(fd+1, &read_fds, NULL, NULL, NULL);

        if (sstat < 0)
            qFatal("Error");

        if (FD_ISSET(fd, &read_fds))
          geis_event_dispatch(instance);
    }
    // :D

    geis_finish(instance);
}
