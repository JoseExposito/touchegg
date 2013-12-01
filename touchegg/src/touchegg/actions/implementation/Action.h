/**
 * @file /src/touchegg/actions/implementation/Action.h
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 2 of the License,  or (at your option)  any later
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
 * @class  Action
 */
#ifndef ACTION_H
#define ACTION_H

#include "src/touchegg/util/Include.h"

/**
 * Class that should inherit all actions. Actions are operations associated with
 * a gesture that will be executed when this gesture is caught.
 */
class Action
{

public:

    /**
     * Constructor.
     * @param settings Gesture settings.
     * @param window   Window on which execute the action.
     */
    Action(const QString &settings, Window window)
        : settings(settings),
          window(window) {

        at_start = false;     
    }

    virtual ~Action() {}

    /**
     * Another constructor, this one also takes timing information.
     * @param settings Gesture settings.
     * @param timing Timing information.
     * @param window Window on which to execute the action
     */
    Action(const QString &settings, const QString &timing, Window window)
        : settings(settings),
          window(window) {
    
        if (timing == "AT_START") {
            at_start = true;
        } else {
            at_start = false;
        }
    }

    /**
     * Part of the action that will be executed when the gesture is started.
     * @param attrs Gesture attributes, where the key is the name of the attribute (ie "focus x", "touches") and the
     *        value the value of the attribute.
     */
    virtual void executeStart(const QHash<QString, QVariant>& attrs) = 0;

    /**
     * Part of the action that will be executed when the gesture is updated.
     * @param attrs Gesture attributes, where the key is the name of the attribute (ie "focus x", "touches") and the
     *        value the value of the attribute.
     */
    virtual void executeUpdate(const QHash<QString, QVariant>& attrs) = 0;

    /**
     * Part of the action that will be executed when the gesture finish.
     * @param attrs Gesture attributes, where the key is the name of the attribute (ie "focus x", "touches") and the
     *        value the value of the attribute.
     */
    virtual void executeFinish(const QHash<QString, QVariant>& attrs) = 0;

protected:

    /**
     * Action settings.
     */
    QString settings;

    /**
     * Timing information (only applies to certain actions).
     */
    bool at_start;

    /**
     * Window on which execute the action.
     */
    Window window;

};

#endif // ACTION_H
