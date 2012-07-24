/**
 * @file /src/touchegg/actions/implementation/SendKeys.cpp
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
 * @class  SendKeys
 */
#include "SendKeys.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

SendKeys::SendKeys(const QString &settings, Window window)
    : Action(settings, window)
{
    // Read the keys to send from te configuration
    QStringList keys = settings.split("+");

    foreach(QString key, keys) {
        if (key == "Control" || key == "Shift" || key == "Super" || key == "Alt") {
            key = key.append("_L");
            KeySym keySym = XStringToKeysym(key.toStdString().c_str());
            KeyCode keyCode = XKeysymToKeycode(QX11Info::display(), keySym);
            this->holdDownKeys.append(keyCode);

        } else if (key == "AltGr") {
            KeySym keySym = XStringToKeysym("Alt_R");
            KeyCode keyCode = XKeysymToKeycode(QX11Info::display(), keySym);
            this->holdDownKeys.append(keyCode);

        } else {
            KeySym keySym = XStringToKeysym(key.toStdString().c_str());
            KeyCode keyCode = XKeysymToKeycode(QX11Info::display(), keySym);
            this->pressBetweenKeys.append(keyCode);
        }
    }

    // Bring the window under the cursor to front, because only the window with the focus can receive keys
    XClientMessageEvent event;
    event.window = this-> window;
    event.type = ClientMessage;
    event.message_type = XInternAtom(QX11Info::display(), "_NET_ACTIVE_WINDOW", false);
    event.format = 32;
    event.data.l[0] = 2;
    event.data.l[1] = CurrentTime;
    event.data.l[2] = 0;

    XSendEvent(QX11Info::display(), QX11Info::appRootWindow(QX11Info::appScreen()), false,
            (SubstructureNotifyMask | SubstructureRedirectMask), (XEvent *)&event);
    XFlush(QX11Info::display());
}


// ****************************************************************************************************************** //
// **********                                        PUBLIC METHODS                                        ********** //
// ****************************************************************************************************************** //

void SendKeys::executeStart(const QHash<QString, QVariant>& /*attrs*/) {}

void SendKeys::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void SendKeys::executeFinish(const QHash<QString, QVariant>& /*attrs*/)
{

    for (int n = 0; n < this->holdDownKeys.length(); n++) {
        XTestFakeKeyEvent(QX11Info::display(), this->holdDownKeys.at(n), true, 0);
    }

    for (int n = 0; n < this->pressBetweenKeys.length(); n++) {
        XTestFakeKeyEvent(QX11Info::display(), this->pressBetweenKeys.at(n), true, 0);
        XTestFakeKeyEvent(QX11Info::display(), this->pressBetweenKeys.at(n), false, 0);
    }

    for (int n = 0; n < this->holdDownKeys.length(); n++) {
        XTestFakeKeyEvent(QX11Info::display(), this->holdDownKeys.at(n), false, 0);
    }
}
