/**
 * @file /src/touchegg/Touchegg.h
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
#ifndef TOUCHEGG_H
#define TOUCHEGG_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/windows/WindowListener.h"
#include "src/touchegg/gestures/collector/GestureCollector.h"
#include "src/touchegg/gestures/handler/GestureHandler.h"

/**
 * Initializes and launches Touchégg. To do this uses this three clases:
 * - WindowListener: To detect the creation or destruction of the windows and listen, if is neccessary, the multitouch
 *   events in that window.
 * - GestureCollector: To get the multitouch events in the windows selected by the WindowListener.
 * - GestureHandler: To treat the multitouch events collected by the GestureCollector.
 */
class Touchegg : public QApplication
{
    Q_OBJECT

public:

    /**
     * Creates all the necessary classes, but Touchégg will be launched in the start() slot, when uTouch will be ready.
     */
    Touchegg(int &argc, char **argv);

protected:

    /**
     * Reimplement the method QApplication::x11EventFilter. This method receives the notifications of
     * creation/destruction of windows and manage it as appropiate using WindowListener.
     * @param  event The event that occurred.
     * @return true if you want to stop the event from being processed, ie when we treat ourselves, false for normal
     *         event dispatching.
     */
    virtual bool x11EventFilter(XEvent *event);

private slots:

    /**
     * This slot is called when uTouch is ready. Launches Touchégg.
     */
    void start();

private:

    /**
     * Class to get the creation and destruction of windows.
     * @see x11EventFilter()
     * @see WindowListener
     */
    WindowListener *windowListener;

    /**
     * Class to collect all the gestures.
     * @see GestureCollector
     */
    GestureCollector *gestureCollector;

    /**
     * Class to treat the gestures and execute the corresponding action.
     * @see GestureHandler
     */
    GestureHandler *gestureHandler;

};

#endif // TOUCHEGG_H
