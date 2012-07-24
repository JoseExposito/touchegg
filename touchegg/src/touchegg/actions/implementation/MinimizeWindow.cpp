/**
 * @file /src/touchegg/actions/implementation/MinimizeWindow.cpp
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
 * @class  MinimizeWindow
 */
#include "MinimizeWindow.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

MinimizeWindow::MinimizeWindow(const QString &settings, Window window)
    : Action(settings, window) {}


// ****************************************************************************************************************** //
// **********                                        PUBLIC METHODS                                        ********** //
// ****************************************************************************************************************** //

void MinimizeWindow::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void MinimizeWindow::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void MinimizeWindow::executeFinish(const QHash<QString, QVariant>& /*attrs*/)
{
    // Minimize the window
    XClientMessageEvent event;
    event.window = this->window;
    event.type = ClientMessage;
    event.message_type = XInternAtom(QX11Info::display(), "WM_CHANGE_STATE", false);
    event.format = 32;
    event.data.l[0] = IconicState;

    XSendEvent(QX11Info::display(), QX11Info::appRootWindow(QX11Info::appScreen()), false,
            (SubstructureNotifyMask | SubstructureRedirectMask), (XEvent *)&event);
    XFlush(QX11Info::display());
}
