/**
 * @file /src/touchegg/actions/implementation/ChangeViewport.cpp
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
 * @class  ChangeViewport
 */
#include "ChangeViewport.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

ChangeViewport::ChangeViewport(const QString &settings, Window window)
    : Action(settings, window)
{
    this->next = true;

    if (settings == "PREVIOUS")
        this->next = false;
    else if (settings == "NEXT")
        this->next = true;
    else
        qWarning() << "Error reading CHANGE_VIEWPORT settings, using the default settings";
}


// ****************************************************************************************************************** //
// **********                                        PUBLIC METHODS                                        ********** //
// ****************************************************************************************************************** //

void ChangeViewport::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void ChangeViewport::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void ChangeViewport::executeFinish(const QHash<QString, QVariant>& /*attrs*/)
{
    // Get the size of all viewports together
    Atom atomRet;
    int size;
    unsigned long numItems, bytesAfterReturn;
    unsigned char *propRet;

    int widthViews, heightViews;
    if (XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(),
            XInternAtom(QX11Info::display(), "_NET_DESKTOP_GEOMETRY", false),
            0, 100, false, XA_CARDINAL, &atomRet, &size, &numItems,
            &bytesAfterReturn, &propRet) == Success && numItems == 2) {
        int *aux = (int *)propRet;
        widthViews  = aux[0];
        heightViews = aux[1];
        XFree(propRet);

        if (widthViews == 0 || heightViews == 0)
            return;
    } else {
        return;
    }

    // Get the coordinates of the current viewport
    int currentX, currentY;
    if (XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(),
            XInternAtom(QX11Info::display(), "_NET_DESKTOP_VIEWPORT", false),
            0, 100, false, XA_CARDINAL, &atomRet, &size, &numItems,
            &bytesAfterReturn, &propRet) == Success && numItems == 2) {
        int *aux = (int *)propRet;
        currentX = aux[0];
        currentY = aux[1];
        XFree(propRet);
    } else {
        return;
    }

    // Get the coordinates of the next/previous viewport
    int nextX, nextY;
    if (this->next) {
        nextX = (currentX + QApplication::desktop()->width()) % widthViews;
        nextY = (nextX == 0)
                ? (currentY + QApplication::desktop()->height()) % heightViews
                : currentY;
    } else {
        nextX = (currentX - QApplication::desktop()->width()) % widthViews;
        if (nextX < 0) {
            nextY  = (currentY - QApplication::desktop()->height()) % heightViews;
            nextX *= -1;
            nextY *= -1;
        } else {
            nextY = currentY;
        }
    }

    // Change the viewport
    XClientMessageEvent event;
    event.window = QX11Info::appRootWindow(QX11Info::appScreen());
    event.type = ClientMessage;
    event.message_type = XInternAtom(QX11Info::display(), "_NET_DESKTOP_VIEWPORT", false);
    event.format = 32;
    event.data.l[0] = nextX;
    event.data.l[1] = nextY;

    XSendEvent(QX11Info::display(), QX11Info::appRootWindow(QX11Info::appScreen()), false,
            (SubstructureNotifyMask | SubstructureRedirectMask), (XEvent *)&event);
    XFlush(QX11Info::display());
}
