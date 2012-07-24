/**
 * @file /src/touchegg/actions/implementation/ChangeDesktop.cpp
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
 * @class  ChangeDesktop
 */
#include "ChangeDesktop.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

ChangeDesktop::ChangeDesktop(const QString &settings, Window window)
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

void ChangeDesktop::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void ChangeDesktop::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void ChangeDesktop::executeFinish(const QHash<QString, QVariant>& /*attrs*/)
{
    // Get the number of desktops
    Atom atomRet;
    int size;
    unsigned long numItems, bytesAfterReturn;
    unsigned char *propRet;

    XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(),
            XInternAtom(QX11Info::display(), "_NET_NUMBER_OF_DESKTOPS", false),
            0, 1, false, XA_CARDINAL, &atomRet, &size, &numItems, &bytesAfterReturn, &propRet);
    int numDesktops = (int) * propRet;
    XFree(propRet);

    // Get the current desktop
    XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(),
            XInternAtom(QX11Info::display(), "_NET_CURRENT_DESKTOP", false),
            0, 1, false, XA_CARDINAL, &atomRet, &size, &numItems, &bytesAfterReturn, &propRet);
    int currentDesktop = (int) * propRet;
    XFree(propRet);

    // Switch to the next/previous desktop
    int nextDesktop = this->next
            ? (currentDesktop + 1) % numDesktops
            : (currentDesktop - 1 + numDesktops) % numDesktops;

    XClientMessageEvent event;
    event.window = QX11Info::appRootWindow(QX11Info::appScreen());
    event.type = ClientMessage;
    event.message_type = XInternAtom(QX11Info::display(), "_NET_CURRENT_DESKTOP", false);
    event.format = 32;
    event.data.l[0] = nextDesktop;

    XSendEvent(QX11Info::display(), QX11Info::appRootWindow(QX11Info::appScreen()), false,
            (SubstructureNotifyMask | SubstructureRedirectMask), (XEvent *)&event);
    XFlush(QX11Info::display());
}
