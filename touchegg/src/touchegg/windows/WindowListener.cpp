/**
 * @file /src/touchegg/windows/WindowListener.cpp
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
 * @class  WindowListener
 */
#include "WindowListener.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

WindowListener::WindowListener(QObject *parent)
    : QObject(parent),
      clientList(this->getClientList())
{

}


// ****************************************************************************************************************** //
// **********                                        PUBLIC METHODS                                        ********** //
// ****************************************************************************************************************** //

void WindowListener::x11Event(XEvent *event)
{
    if (event->type == PropertyNotify
            && event->xproperty.atom == XInternAtom(QX11Info::display(), "_NET_CLIENT_LIST", false)) {
        bool isNew;
        QList<Window> oldList = this->clientList;
        this->clientList = this->getClientList();

        Window w = this->getDifferentWindow(this->clientList, oldList, &isNew);

        if (w != None) {
            if (isNew)
                emit this->windowCreated(w);
            else
                emit this->windowDeleted(w);
        }

    }
}

QList<Window> WindowListener::getClientList() const
{
    Atom atomRet;
    int size;
    unsigned long numItems, bytesAfterReturn;
    unsigned char *propRet;
    long offset = 0;
    long offsetSize = 100;
    int status;
    Atom atomList = XInternAtom(QX11Info::display(), "_NET_CLIENT_LIST", false);
    QList<Window> ret;

    do {
        status = XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(), atomList, offset, offsetSize, false,
                XA_WINDOW, &atomRet, &size, &numItems, &bytesAfterReturn, &propRet);

        if (status == Success) {
            Window *aux = (Window *)propRet;
            unsigned int n = 0;
            while (n < numItems) {
                ret.append(aux[n]);
                n++;
            }
            offset += offsetSize;
            XFree(propRet);
        }
    } while (status == Success && bytesAfterReturn != 0);

    return ret;
}


// ****************************************************************************************************************** //
// **********                                        PRIVATE METHODS                                       ********** //
// ****************************************************************************************************************** //

Window WindowListener::getDifferentWindow(QList<Window> lnew, QList<Window> lold, bool *isNew) const
{
    if (lnew == lold) {
        return None;
    } else {
        // Because _NET_CLIENT_LIST is order from old to new windows, we only need to return the last window of the
        // longer list
        *isNew = lnew.length() > lold.length();
        return lnew.length() > lold.length() ? lnew.last() : lold.last();
    }
}

