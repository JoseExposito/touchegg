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
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011 - 2012
 * @class  GestureHandler
 */
#include "GestureHandler.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

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


// ****************************************************************************************************************** //
// **********                                         PUBLIC SLOTS                                         ********** //
// ****************************************************************************************************************** //

void GestureHandler::executeGestureStart(const QString &type, int id, const QHash<QString, QVariant>& attrs)
{
    // If not gesture is running create one
    if (this->currentGesture == NULL) {
        this->currentGesture = this->createGesture(type, id, attrs, false);
        if (this->currentGesture != NULL) {
            qDebug() << "\tGesture Start" << id << type;
            this->currentGesture->start();
        }
    }
}

void GestureHandler::executeGestureUpdate(const QString &type, int id, const QHash<QString, QVariant>& attrs)
{
    // If is an update of the current gesture execute it
    if (this->currentGesture != NULL && this->currentGesture->getId() == id && !this->timerTap->isActive()) {
        qDebug() << "\tGesture Update" << id << type;
        this->currentGesture->setAttrs(attrs);
        this->currentGesture->update();

    // If no gesture is running the gesture is a TAP, an unsupported gesture, or in Precise a DRAG
    } else if (this->currentGesture == NULL) {

        Gesture *gesture = this->createGesture(type, id, attrs, false);
        if (gesture != NULL) {
            this->currentGesture = gesture;

            // If the gesture is a tap allow to make a tap & hold
            if (gesture->getType() == GestureTypeEnum::TAP) {
                this->timerTap->start();

            // In Precise the DeltaX and DeltaY attrs in start are 0. Create the Drag here
            } else if (gesture->getType() == GestureTypeEnum::DRAG) {
                qDebug() << "\tGesture Start";
                this->currentGesture->start();
                qDebug() << "\tGesture Update" << id << type;
                this->currentGesture->update();
            }
        }

    // If is an update whith the timer running it is a DOUBLE_TAP or a TAP_AND_HOLD
    } else if (this->currentGesture != NULL && this->timerTap->isActive()) {
        this->timerTap->stop();

        int currentNumFingers = this->currentGesture->getAttrs().value(GEIS_GESTURE_ATTRIBUTE_TOUCHES).toInt();
        int newNumFingers     = attrs.value(GEIS_GESTURE_ATTRIBUTE_TOUCHES).toInt();
        Gesture *gesture      = this->createGesture(type, id, attrs, true);

        if (gesture != NULL && currentNumFingers == newNumFingers) {

            // TAP_AND_HOLD
            if (gesture->getType() == GestureTypeEnum::TAP_AND_HOLD) {
                this->currentGesture = gesture;

                qDebug() << "\tGesture Start";
                this->currentGesture->start();

                qDebug() << "\tGesture Update";
                this->currentGesture->update();

            // DOUBLE_TAP
            } else if (gesture->getType() == GestureTypeEnum::DOUBLE_TAP) {
                this->currentGesture = gesture;

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

void GestureHandler::executeGestureFinish(const QString &/*type*/, int id, const QHash<QString, QVariant>& attrs)
{
    if (this->currentGesture != NULL && this->currentGesture->getId() == id) {
        qDebug() << "\tGesture Finish";
        this->currentGesture->setAttrs(attrs);
        this->currentGesture->finish();
        delete this->currentGesture;
        this->currentGesture = NULL;
    }
}


// ****************************************************************************************************************** //
// **********                                         PRIVATE SLOTS                                        ********** //
// ****************************************************************************************************************** //

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


// ****************************************************************************************************************** //
// **********                                        PRIVATE METHODS                                       ********** //
// ****************************************************************************************************************** //

Gesture *GestureHandler::createGesture(const QString &type, int id, const QHash<QString, QVariant>& attrs,
    bool isComposedGesture) const
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
    Window gestureWindow = this->getGestureWindow(attrs.value(GEIS_GESTURE_ATTRIBUTE_CHILD_WINDOW_ID).toInt());
    if (gestureWindow == None)
        return NULL;
    QString appClass = this->getAppClass(gestureWindow);

    // Creamos y asignamos la acción asociada al gesto
    ActionTypeEnum::ActionType actionType = this->config->getAssociatedAction(appClass, ret->getType(),
            ret->getNumFingers(), ret->getDirection());
    QString actionSettings = this->config->getAssociatedSettings(appClass, ret->getType(), ret->getNumFingers(),
            ret->getDirection());

    ret->setAction(this->actionFact->createAction(actionType, actionSettings, gestureWindow));

    // Mostramos los datos sobre el gesto
    qDebug() << "[+] New gesture:";
    qDebug() << "\tType      -> " << GestureTypeEnum::getValue(ret->getType());
    qDebug() << "\tFingers   -> " << ret->getNumFingers();
    qDebug() << "\tDirection -> " << GestureDirectionEnum::getValue(ret->getDirection());
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

    // Compare the top-level window of the specified window with the possible fake-top-level window (really they are not
    // top-level windows, but are the windows that stores the attributes and more), returning the window that contains
    // the title, the class...
    Atom atomRet;
    int size;
    unsigned long numItems, bytesAfterReturn;
    unsigned char *propRet;
    long offset = 0;
    long offsetSize = 100;

    Window ret = None;

    int status;
    Atom atomList = XInternAtom(QX11Info::display(), "_NET_CLIENT_LIST_STACKING", false);
    do {
        status = XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(), atomList,
                offset, offsetSize, false, XA_WINDOW, &atomRet, &size,
                &numItems, &bytesAfterReturn, &propRet);

        if (status == Success) {
            Window *aux = (Window *)propRet;
            unsigned int n = 0;
            while (ret == None && n < numItems) {
                // Check if the top-level window of the window of the list coincides with the window passed as argument
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
