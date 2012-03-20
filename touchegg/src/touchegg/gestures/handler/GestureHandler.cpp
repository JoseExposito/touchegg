/**
 * @file /src/touchegg/gestures/handler/GestureHandler.cpp
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
 * @class  GestureHandler
 */
#include "GestureHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

GestureHandler::GestureHandler(QObject *parent)
    : QObject(parent),
      currentGesture(NULL),
      timerTap(new QTimer(this)),
      gestureFact(GestureFactory::getInstance()),
      actionFact(ActionFactory::getInstance()),
      config(Config::getInstance())
{
    this->timerTap->setInterval(this->config->getComposedGesturesTime());
    connect(this->timerTap, SIGNAL(timeout()), this, SLOT(executeTap()));
}

GestureHandler::~GestureHandler()
{
    delete this->currentGesture;
}


// ************************************************************************** //
// **********                     PUBLIC SLOTS                     ********** //
// ************************************************************************** //

void GestureHandler::executeGestureStart(const QString &type, int id,
        const QHash<QString, QVariant>& attrs)
{
    // Si no se está ejecutando ningún gesto creamos uno nuevo
    if (this->currentGesture == NULL) {
        this->currentGesture = this->createGesture(type, id, attrs, false);
        if (this->currentGesture != NULL) {
            // Ejecutamos el gesto
            qDebug() << "\tGesture Start" << id << type;

            this->currentGesture->start();
        }

        // Si el timer está en ejecución podemos hacer un TAP_AND_HOLD
    } else if (this->timerTap->isActive()) {
        this->timerTap->stop();

        // El nuevo gesto debe ser un drag con igual número de dedos que el tap
        // en ejecución para que se considere un TAP_AND_HOLD
        if (attrs.contains(GEIS_GESTURE_ATTRIBUTE_TOUCHES)
                && this->currentGesture->getAttrs().contains(
                        GEIS_GESTURE_ATTRIBUTE_TOUCHES)
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_TOUCHES)
                == this->currentGesture->getAttrs().value(
                        GEIS_GESTURE_ATTRIBUTE_TOUCHES)) {
            delete this->currentGesture;
            this->currentGesture = this->createGesture(type, id, attrs, true);

            if (this->currentGesture != NULL) {
                // Ejecutamos el gesto
                qDebug() << "\tGesture Start";
                this->currentGesture->start();
            }

            // Si no es un tap&hold ejecutamos el tap con normalidad
        } else {
            this->executeTap();
        }
    }
}

void GestureHandler::executeGestureUpdate(const QString &type, int id,
        const QHash<QString, QVariant>& attrs)
{
    // Si es un update del gesto en ejecución
    if (this->currentGesture != NULL
            && this->currentGesture->getId() == id
            && !this->timerTap->isActive()) {
        qDebug() << "\tGesture Update" << id << type;
        this->currentGesture->setAttrs(attrs);
        this->currentGesture->update();

        // Si no se está ejecutando ningún gesto es que es un TAP o un gesto no
        // soportado
    } else if (this->currentGesture == NULL) {
        // Si es un TAP, esperamos un poco para que se pueda usar un tap&hold
        this->currentGesture = this->createGesture(type, id, attrs, false);
        if (this->currentGesture != NULL) {
            this->timerTap->start();
        }

        // Si se recibe un TAP con el timer en ejecución es que es un DOUBLE_TAP
    } else if (this->currentGesture != NULL
            && this->timerTap->isActive()) {
        this->timerTap->stop();

        // El nuevo gesto debe ser un tap con igual número de dedos que el tap
        // en ejecución para que se considere un DOUBLE_TAP
        if (attrs.contains(GEIS_GESTURE_ATTRIBUTE_TOUCHES)
                && this->currentGesture->getAttrs().contains(
                        GEIS_GESTURE_ATTRIBUTE_TOUCHES)
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_TOUCHES)
                == this->currentGesture->getAttrs().value(
                        GEIS_GESTURE_ATTRIBUTE_TOUCHES)) {
            delete this->currentGesture;
            this->currentGesture = this->createGesture(type, id, attrs, true);

            if (this->currentGesture != NULL) {
                // Ejecutamos el gesto
                qDebug() << "\tGesture Start";
                this->currentGesture->start();

                qDebug() << "\tGesture Update";
                this->currentGesture->update();

                qDebug() << "\tGesture Finish";
                this->currentGesture->finish();

                delete this->currentGesture;
                this->currentGesture = NULL;
            }
        }
    }
}

void GestureHandler::executeGestureFinish(const QString &/*type*/, int id,
        const QHash<QString, QVariant>& attrs)
{
    if (this->currentGesture != NULL && this->currentGesture->getId() == id) {
        qDebug() << "\tGesture Finish";
        this->currentGesture->setAttrs(attrs);
        this->currentGesture->finish();
        delete this->currentGesture;
        this->currentGesture = NULL;
    }
}


// ************************************************************************** //
// **********                     PRIVATE SLOTS                    ********** //
// ************************************************************************** //

void GestureHandler::executeTap()
{
    this->timerTap->stop();

    if (this->currentGesture != NULL) {
        qDebug() << "\tGesture Start";
        this->currentGesture->start();

        qDebug() << "\tGesture Update";
        this->currentGesture->update();

        qDebug() << "\tGesture Finish";
        this->currentGesture->finish();

        delete this->currentGesture;
        this->currentGesture = NULL;
    }
}


// ************************************************************************** //
// **********                   PRIVATE METHODS                    ********** //
// ************************************************************************** //

Gesture *GestureHandler::createGesture(const QString &type, int id,
        const QHash<QString, QVariant>& attrs, bool isComposedGesture) const
{
    // Creamos el gesto sin su acción
    Gesture *ret;
    if (isComposedGesture)
        ret = this->gestureFact->createComposedGesture(type, id, attrs);
    else
        ret = this->gestureFact->createSimpleGesture(type, id, attrs);

    if (ret == NULL)
        return NULL;

    // Vemos sobre que ventana se ha ejecutado
    Window gestureWindow = this->getGestureWindow(
            attrs.value(GEIS_GESTURE_ATTRIBUTE_CHILD_WINDOW_ID).toInt());
    if (gestureWindow == None)
        return NULL;
    QString appClass = this->getAppClass(gestureWindow);

    // Creamos y asignamos la acción asociada al gesto
    ActionTypeEnum::ActionType actionType = this->config->getAssociatedAction(
            appClass, ret->getType(), ret->getNumFingers(),
            ret->getDirection());
    QString actionSettings = this->config->getAssociatedSettings(appClass,
            ret->getType(), ret->getNumFingers(), ret->getDirection());

    ret->setAction(this->actionFact->createAction(actionType, actionSettings,
            gestureWindow));

    // Mostramos los datos sobre el gesto
    qDebug() << "[+] New gesture:";
    qDebug() << "\tType      -> " << GestureTypeEnum::getValue(ret->getType());
    qDebug() << "\tFingers   -> " << ret->getNumFingers();
    qDebug() << "\tDirection -> " << GestureDirectionEnum::getValue(
            ret->getDirection());
    qDebug() << "\tAction    -> " << ActionTypeEnum::getValue(actionType);
    qDebug() << "\tApp Class -> " << appClass;

    return ret;
}

//------------------------------------------------------------------------------

Window GestureHandler::getGestureWindow(Window window) const
{
    Window topIn = this->getTopLevelWindow(window);
    if (topIn == None)
        return None;

    // Comparamos la top-level window de la ventana pasada con las de las
    // posibles fake-top-level windows (realmente no son top-level, pero son las
    // ventanas que guardan los atributos y de más), devolviendo la ventana que
    // contiene el título, la clase, etc
    Atom atomRet;
    int size;
    unsigned long numItems, bytesAfterReturn;
    unsigned char *propRet;
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

        if (status == Success) {

            Window *aux = (Window *)propRet;
            unsigned int n = 0;
            while (ret == None && n < numItems) {
                // Vemos si la top-level window de la ventana de la lista
                // coincide con la de la pasada como argumento
                if (this->getTopLevelWindow(aux[n]) == topIn)
                    ret = aux[n];
                n++;
            }
            offset += offsetSize;
            XFree(propRet);
        }
    } while (status == Success && bytesAfterReturn != 0);

    return ret;
}

Window GestureHandler::getTopLevelWindow(Window window) const
{
    Window  root, parent;
    Window *children;
    unsigned int numChildren;

    if (XQueryTree(QX11Info::display(), window, &root, &parent, &children,
            &numChildren) != 0) {
        if (children != NULL)
            XFree(children);

        if (parent == root)
            return window;
        else
            return this->getTopLevelWindow(parent);

    } else {
        return None;
    }
}

QString GestureHandler::getAppClass(Window window) const
{
    XClassHint *classHint = XAllocClassHint();
    XGetClassHint(QX11Info::display(), window, classHint);
    QString ret = classHint->res_class;
    XFree(classHint->res_class);
    XFree(classHint->res_name);
    return ret;
}
