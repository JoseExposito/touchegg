/**
 * @file /src/touchegg/Touchegg.cpp
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
 * @class  Touchegg
 */
#include "Touchegg.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

Touchegg::Touchegg(int argc, char** argv)
        : QApplication(argc, argv),
          gestureCollector(new GestureCollector),
          gestureHandler(new GestureHandler),
          clientList(this->getClientList())
{
    // Inicializamos Touchégg cuando uTouch esté listo
    connect(this->gestureCollector, SIGNAL(ready()), this, SLOT(start()));

    // Conectamos el GestureCollector con el GestureHandler para que el último
    // trate los eventos que recoge el primero
    connect(gestureCollector, SIGNAL(executeGestureStart(
            QString,int,QHash<QString,QVariant>)),
            gestureHandler, SLOT(executeGestureStart(
            QString,int,QHash<QString,QVariant>)));
    connect(gestureCollector, SIGNAL(executeGestureUpdate(
            QString,int,QHash<QString,QVariant>)),
            gestureHandler, SLOT(executeGestureUpdate(
            QString,int,QHash<QString,QVariant>)));
    connect(gestureCollector, SIGNAL(executeGestureFinish(
            QString,int,QHash<QString,QVariant>)),
            gestureHandler, SLOT(executeGestureFinish(
            QString,int,QHash<QString,QVariant>)));
}

Touchegg::~Touchegg()
{
    delete this->gestureCollector;
    delete this->gestureHandler;
}


// ************************************************************************** //
// **********                    PRIVATE SLOTS                     ********** //
// ************************************************************************** //

void Touchegg::start()
{
    // Nos suscribimos a los gestos globales
    this->gestureCollector->addWindow(QX11Info::appRootWindow());

    // Obtenemos la lista actual de ventanas para suscribirnos a ellas
    this->clientList = this->getClientList();

    foreach(Window w, this->clientList) {
        this->gestureCollector->addWindow(w);
    }
}


// ************************************************************************** //
// **********                   PROTECTED METHODS                  ********** //
// ************************************************************************** //

bool Touchegg::x11EventFilter(XEvent* event)
{
    if(event->type == PropertyNotify && event->xproperty.atom == XInternAtom(
            QX11Info::display(), "_NET_CLIENT_LIST", false)) {
        bool isNew;
        QList<Window> oldList = this->clientList;
        this->clientList = this->getClientList();

        Window w = this->getDifferentWindow(this->clientList, oldList, &isNew);

        if(w != None) {
            if(isNew)
                this->gestureCollector->addWindow(w);
            else
                this->gestureCollector->removeWindow(w);
        }

    }
    return false;
}


// ************************************************************************** //
// **********                   PRIVATE METHODS                    ********** //
// ************************************************************************** //

QList<Window> Touchegg::getClientList() const
{
    Atom atomRet;
    int size;
    unsigned long numItems, bytesAfterReturn;
    unsigned char* propRet;
    long offset = 0;
    long offsetSize = 100;
    int status;
    Atom atomList = XInternAtom(QX11Info::display(), "_NET_CLIENT_LIST", false);
    QList<Window> ret;

    do {
        status = XGetWindowProperty(QX11Info::display(),
                QX11Info::appRootWindow(), atomList, offset, offsetSize, false,
                XA_WINDOW, &atomRet,&size,&numItems,&bytesAfterReturn,&propRet);

        if(status == Success) {
            Window* aux = (Window*)propRet;
            unsigned int n=0;
            while(n < numItems) {
                ret.append(aux[n]);
                n++;
            }
            offset += offsetSize;
            XFree(propRet);
        }
    } while(status == Success && bytesAfterReturn != 0);

    return ret;
}

Window Touchegg::getDifferentWindow(QList<Window> lnew, QList<Window> lold,
        bool* isNew) const
{
    if(lnew == lold) {
        return None;
    } else {
        // Como _NET_CLIENT_LIST lleva un orden de primero las ventanas viejas y
        // luego las nuevas, nos basta con devolver la última ventana de la
        // lista más larga
        *isNew = lnew.length() > lold.length();
        return lnew.length() > lold.length() ? lnew.last() : lold.last();
    }
}
