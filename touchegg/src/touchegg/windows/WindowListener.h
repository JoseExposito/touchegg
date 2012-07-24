/**
 * @file /src/touchegg/windows/WindowListener.h
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
 * @class  WindowListener
 */
#ifndef WINDOWLISTENER_H
#define WINDOWLISTENER_H

#include "src/touchegg/util/Include.h"

/**
 * Detects the creation or destruction of the windows and emits the windowCreated or windowDeleted signals respectively.
 */
class WindowListener : public QObject
{
    Q_OBJECT

public:

    /**
     * Default constructor.
     * @param parent The parent of the class.
     */
    WindowListener(QObject *parent = 0);

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Called whenever a X11 event occurs. Is necessary to filter that event to know if is a creation or destruction of
     * a window and emit the corresponding signals.
     */
    void x11Event(XEvent *event);

    /**
     * Returns the list of existing windows checking the _NET_CLIENT_LIST property set by the window manager.
     * @return The list.
     */
    QList<Window> getClientList() const;

signals:

    /**
     * Emited when a new window is created.
     */
    void windowCreated(Window w);

    /**
     * Emited when a window is closed/deleted.
     */
    void windowDeleted(Window w);

private:

    /**
     * Given two lists of windows returns the difference between them, corresponding to the last window created/deleted.
     * @param  lnew  The list with the new windows.
     * @param  lold  The list with the old windows.
     * @param  isNew true if the returned window has been created, false if has been deleted.
     * @return The created/deleted window or None if the two list are equals.
     */
    Window getDifferentWindow(QList<Window> lnew, QList<Window> lold, bool *isNew) const;

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Current list with the existing windows.
     */
    QList<Window> clientList;

};

#endif // WINDOWLISTENER_H
