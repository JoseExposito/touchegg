/**
 * @file /src/touchegg/actions/implementation/CloseWindow.cpp
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
 * @class  CloseWindow
 */
#include "CloseWindow.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

CloseWindow::CloseWindow(const QString &settings, Window window)
    : Action(settings, window) {}


// ****************************************************************************************************************** //
// **********                                        PUBLIC METHODS                                        ********** //
// ****************************************************************************************************************** //

void CloseWindow::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void CloseWindow::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void CloseWindow::executeFinish(const QHash<QString, QVariant>& /*attrs*/)
{
    // Close the window
    XClientMessageEvent event;
    event.window = this->window;
    event.type = ClientMessage;
    event.message_type = XInternAtom(QX11Info::display(), "_NET_CLOSE_WINDOW", false);
    event.format = 32;
    event.data.l[0] = CurrentTime;
    event.data.l[1] = 2;

    XSendEvent(QX11Info::display(), QX11Info::appRootWindow(QX11Info::appScreen()), false,
            (SubstructureNotifyMask | SubstructureRedirectMask), (XEvent *)&event);

    XFlush(QX11Info::display());
}
