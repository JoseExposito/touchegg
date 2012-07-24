/**
 * @file /src/touchegg/actions/implementation/ShowDesktop.cpp
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
 * @class  ShowDesktop
 */
#include "ShowDesktop.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

ShowDesktop::ShowDesktop(const QString &settings, Window window)
    : Action(settings, window) {}


// ****************************************************************************************************************** //
// **********                                        PUBLIC METHODS                                        ********** //
// ****************************************************************************************************************** //

void ShowDesktop::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void ShowDesktop::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void ShowDesktop::executeFinish(const QHash<QString, QVariant>& /*attrs*/)
{
    // Check if it is already in show desktop mode
    Atom atomRet;
    int size;
    unsigned long numItems, bytesAfterReturn;
    unsigned char *propRet;

    XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(),
            XInternAtom(QX11Info::display(), "_NET_SHOWING_DESKTOP", false),
            0, 1, false, XA_CARDINAL, &atomRet, &size, &numItems, &bytesAfterReturn, &propRet);

    if (propRet == NULL)
        return;

    bool isShowingDesktop = *((bool *) propRet);
    XFree(propRet);

    // Minimize or restore the windows
    XClientMessageEvent event;
    event.window = QX11Info::appRootWindow(QX11Info::appScreen());
    event.type = ClientMessage;
    event.message_type = XInternAtom(QX11Info::display(), "_NET_SHOWING_DESKTOP", false);
    event.format = 32;
    event.data.l[0] = !isShowingDesktop;

    XSendEvent(QX11Info::display(), QX11Info::appRootWindow(QX11Info::appScreen()), false,
            (SubstructureNotifyMask | SubstructureRedirectMask), (XEvent *)&event);
    XFlush(QX11Info::display());
}
