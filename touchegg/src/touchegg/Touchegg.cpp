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
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011 - 2012
 * @class  Touchegg
 */
#include "Touchegg.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

Touchegg::Touchegg(int &argc, char **argv)
    : QApplication(argc, argv),
      windowListener(new WindowListener(this)),
      gestureCollector(new GestureCollector(this)),
      gestureHandler(new GestureHandler(this))
{
    qDebug() << "Try to make a multitouch gesture. If everything goes well the "
            "information about the gesture must appear";

    connect(this->gestureCollector, SIGNAL(ready()), this, SLOT(start()));
}


// ****************************************************************************************************************** //
// **********                                       PROTECTED METHODS                                      ********** //
// ****************************************************************************************************************** //

bool Touchegg::x11EventFilter(XEvent *event)
{
    this->windowListener->x11Event(event);
    return false;
}


// ****************************************************************************************************************** //
// **********                                         PRIVATE SLOTS                                        ********** //
// ****************************************************************************************************************** //

void Touchegg::start()
{
    // Connect the WindowListener with the GestureCollector to get the multitouch gestures in the created windows
    connect(this->windowListener, SIGNAL(windowCreated(Window)),
            this->gestureCollector, SLOT(addWindow(Window)));
    connect(this->windowListener, SIGNAL(windowDeleted(Window)),
            this->gestureCollector, SLOT(removeWindow(Window)));

    // The GestureCollector collect the gestures and the GestureHandler perform its and add a layer to perform
    // composed gestures
    connect(gestureCollector, SIGNAL(executeGestureStart(
            QString, int, QHash<QString, QVariant>)),
            gestureHandler, SLOT(executeGestureStart(
                    QString, int, QHash<QString, QVariant>)));
    connect(gestureCollector, SIGNAL(executeGestureUpdate(
            QString, int, QHash<QString, QVariant>)),
            gestureHandler, SLOT(executeGestureUpdate(
                    QString, int, QHash<QString, QVariant>)));
    connect(gestureCollector, SIGNAL(executeGestureFinish(
            QString, int, QHash<QString, QVariant>)),
            gestureHandler, SLOT(executeGestureFinish(
                    QString, int, QHash<QString, QVariant>)));

    // Subscribe to global gestures
    this->gestureCollector->addWindow(QX11Info::appRootWindow());

    // Subscribe to application specific gestures
    foreach(Window w, this->windowListener->getClientList()) {
        this->gestureCollector->addWindow(w);
    }
}
