/**
 * @file /src/touchegg/actions/implementation/Scroll.h
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
 * @class  Scroll
 */
#ifndef SCROLL_H
#define SCROLL_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * Emulates the mouse whell.
 */
class Scroll : public Action
{

public:

    Scroll(const QString &settings, Window window);

    void executeStart(const QHash<QString, QVariant>& attrs);

    void executeUpdate(const QHash<QString, QVariant>& attrs);

    void executeFinish(const QHash<QString, QVariant>& attrs);

private:

    /**
     * Scroll speed. More is slower.
     */
    int horizontalSpeed;

    /**
     * Scroll speed. More is slower.
     */
    int verticalSpeed;

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Accumulated space to scrolling up.
     */
    int upScrollSpace;

    /**
     * Accumulated space to scrolling down.
     */
    int downScrollSpace;

    /**
     * Accumulated space to scrolling left.
     */
    int leftScrollSpace;

    /**
     * Accumulated space to scrolling right.
     */
    int rightScrollSpace;

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Button of the mouse to scroll up.
     */
    int buttonUp;

    /**
     * Button of the mouse to scroll down.
     */
    int buttonDown;

    /**
     * Button of the mouse to scroll left.
     */
    int buttonLeft;

    /**
     * Button of the mouse to scroll right.
     */
    int buttonRight;

};

#endif // SCROLL_H
