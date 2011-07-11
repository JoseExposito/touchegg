/**
 * @file /src/touchegg/gestures/collector/GestureCollector.cpp
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 3 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 *
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011
 * @class  GestureCollector
 */
#include "GestureCollector.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

void GestureCollector::gestureStart(void* cookie, GeisGestureType type,
        GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs)
{
    GestureCollector* gc = (GestureCollector*)cookie;
    emit gc->executeGestureStart(type, id, getGestureAttrs(numAttrs, attrs));
}

void GestureCollector::gestureUpdate(void* cookie, GeisGestureType type,
        GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs)
{
    GestureCollector* gc = (GestureCollector*)cookie;
    emit gc->executeGestureUpdate(type, id, getGestureAttrs(numAttrs, attrs));
}

void GestureCollector::gestureFinish(void* cookie, GeisGestureType type,
        GeisGestureId id, GeisSize numAttrs, GeisGestureAttr* attrs)
{
    GestureCollector* gc = (GestureCollector*)cookie;
    emit gc->executeGestureFinish(type, id, getGestureAttrs(numAttrs, attrs));
}


// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

QHash<QString, QVariant> GestureCollector::getGestureAttrs(GeisSize numAttrs,
        GeisGestureAttr* attrs)
{
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

void GestureCollector::run()
{
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

    // Establecemos las funciones de callback
    GeisGestureFuncs gestureFuncs;
    gestureFuncs.start   = GestureCollector::gestureStart;
    gestureFuncs.update  = GestureCollector::gestureUpdate;
    gestureFuncs.finish  = GestureCollector::gestureFinish;

    // Nos suscribimos solo a los gestos que se vayan a usar

    // TODO Cuando esté incorporado el mecanismo para escuchar a los gestos
    //      globales en la root window y a los específicos en la ventana de cada
    //      aplicación sustituir el código entre llaves por las dos líneas
    //      comentadas

    //Config* cfg = Config::getInstance();
    //QStringList subscribeList = cfg->getUsedGestures("All");

    // {
    QStringList subscribeList;
    subscribeList.append(GEIS_GESTURE_TYPE_TAP2);
    subscribeList.append(GEIS_GESTURE_TYPE_TAP3);
    subscribeList.append(GEIS_GESTURE_TYPE_TAP4);
    subscribeList.append(GEIS_GESTURE_TYPE_TAP5);
    subscribeList.append(GEIS_GESTURE_TYPE_DRAG2);
    subscribeList.append(GEIS_GESTURE_TYPE_DRAG3);
    subscribeList.append(GEIS_GESTURE_TYPE_DRAG4);
    subscribeList.append(GEIS_GESTURE_TYPE_DRAG5);
    subscribeList.append(GEIS_GESTURE_TYPE_PINCH2);
    subscribeList.append(GEIS_GESTURE_TYPE_PINCH3);
    subscribeList.append(GEIS_GESTURE_TYPE_PINCH4);
    subscribeList.append(GEIS_GESTURE_TYPE_PINCH5);
    // }


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
        FD_ZERO(&read_fds);
        FD_SET(fd, &read_fds);
        int sstat = select(fd+1, &read_fds, NULL, NULL, NULL);

        if (sstat < 0)
            qFatal("Error");

        if (FD_ISSET(fd, &read_fds))
          geis_event_dispatch(geisInstance);
    }

    geis_finish(geisInstance);
}
