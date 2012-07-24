/**
 * @file /src/touchegg/actions/implementation/ResizeWindow.cpp
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
 * @class  ResizeWindow
 */
#include "ResizeWindow.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

ResizeWindow::ResizeWindow(const QString &settings, Window window)
    : Action(settings, window) {}


// ****************************************************************************************************************** //
// **********                                        PUBLIC METHODS                                        ********** //
// ****************************************************************************************************************** //

void ResizeWindow::executeStart(const QHash<QString, QVariant>& /*attrs*/)
{
    // Check if the window to resize is special (toolbar, descktop...) to not resize it
    Atom atomRet;
    int size;
    unsigned long numItems, bytesAfterReturn;
    unsigned char *propRet;

    if (XGetWindowProperty(QX11Info::display(), this->window,
            XInternAtom(QX11Info::display(), "_NET_WM_WINDOW_TYPE", false),
            0, 100, false, XA_ATOM, &atomRet, &size, &numItems, &bytesAfterReturn, &propRet) == Success) {
        Atom *types = (Atom *)propRet;
        Atom type = types[0]; // Only check the first type

        if (type == XInternAtom(QX11Info::display(), "_NET_WM_WINDOW_TYPE_DESKTOP", false)
                || type == XInternAtom(QX11Info::display(), "_NET_WM_WINDOW_TYPE_DOCK", false)
                || type == XInternAtom(QX11Info::display(), "_NET_WM_WINDOW_TYPE_SPLASH", false)) {
            this->window = 0;
        }
        XFree(propRet);
    }
}

void ResizeWindow::executeUpdate(const QHash<QString, QVariant>& attrs)
{
    if (this->window == 0)
        return;

    // Angle
    if (!attrs.contains(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_X1)
            || !attrs.contains(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_X2)
            || !attrs.contains(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_Y1)
            || !attrs.contains(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_Y2))
        return;

    float co = attrs.value(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_Y2).toFloat()
            - attrs.value(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_Y1).toFloat();
    float cc = attrs.value(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_X2).toFloat()
            - attrs.value(GEIS_GESTURE_ATTRIBUTE_BOUNDINGBOX_X1).toFloat();

    double angle = (int)(atan(co / cc) * 100);

    double incX, incY;
    if (angle > 75) {
        incX = 0;
        incY = 1;
    } else if (angle < 20) {
        incX = 1;
        incY = 0;
    } else {
        incX = cos(angle * (3.14 / 180));
        incY = sin(angle * (3.14 / 180));
    }

    // Resize the window
    XWindowAttributes xwa;
    XGetWindowAttributes(QX11Info::display(), this->window, &xwa);
    int inc = (int)attrs.value(GEIS_GESTURE_ATTRIBUTE_RADIUS_DELTA).toFloat() * 10;
    XResizeWindow(QX11Info::display(), this->window,
            xwa.width  + inc * incX,
            xwa.height + inc * incY);
    XFlush(QX11Info::display());
}

void ResizeWindow::executeFinish(const QHash<QString, QVariant>& /*attrs*/) {}
