/**
 * @file /src/touchegg/actions/implementation/MoveWindow.cpp
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
 * @class  MoveWindow
 */
#include "MoveWindow.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

MoveWindow::MoveWindow(const QString &settings, Window window)
    : Action(settings, window) {}


// ****************************************************************************************************************** //
// **********                                        PUBLIC METHODS                                        ********** //
// ****************************************************************************************************************** //

void MoveWindow::executeStart(const QHash<QString, QVariant>& /*attrs*/)
{
    XTestFakeKeyEvent(QX11Info::display(), XKeysymToKeycode(QX11Info::display(), XK_Alt_L), true, 0);
    XTestFakeButtonEvent(QX11Info::display(), Button1, true, 0);
    XFlush(QX11Info::display());
}

void MoveWindow::executeUpdate(const QHash<QString, QVariant>& attrs)
{
    if (!attrs.contains(GEIS_GESTURE_ATTRIBUTE_DELTA_X) || !attrs.contains(GEIS_GESTURE_ATTRIBUTE_DELTA_Y))
        return;

    XTestFakeRelativeMotionEvent(QX11Info::display(),
            + attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() * 0.1,
            + attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() * 0.1, 0);

    XFlush(QX11Info::display());
}

void MoveWindow::executeFinish(const QHash<QString, QVariant>& /*attrs*/)
{
    XTestFakeKeyEvent(QX11Info::display(), XKeysymToKeycode(QX11Info::display(), XK_Alt_L), false, 0);
    XTestFakeButtonEvent(QX11Info::display(), Button1, false, 0);
    XFlush(QX11Info::display());
}
