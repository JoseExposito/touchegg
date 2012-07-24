/**
 * @file /src/touchegg/gestures/handler/GestureHandler.h
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
 * @class  GestureHandler
 */
#ifndef GESTUREHANDLER_H
#define GESTUREHANDLER_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/config/Config.h"
#include "src/touchegg/gestures/factory/GestureFactory.h"
#include "src/touchegg/actions/factory/ActionFactory.h"

/**
 * Class that receives the gestures, processes it and execute the corresponding action.
 */
class GestureHandler : public QObject
{
    Q_OBJECT

public:

    /**
     * Default constructor.
     * @param parent The parent of the class.
     */
    GestureHandler(QObject *parent = 0);

    /**
     * Destructor.
     */
    virtual ~GestureHandler();

public slots:

    /**
     * Runs the indicated gesture.
     * @param type   Gesture type.
     * @param id     Gesture ID.
     * @param attrs  Gesture attributes, where the key is the name of the attribute (ie "focus x", "touches") and the
     *        value the value of the attribute.
     */
    void executeGestureStart(const QString &type, int id, const QHash<QString, QVariant>& attrs);

    /// @see executeGestureStart()
    void executeGestureUpdate(const QString &type, int id, const QHash<QString, QVariant>& attrs);

    /// @see executeGestureStart()
    void executeGestureFinish(const QString &type, int id, const QHash<QString, QVariant>& attrs);

private slots:

    /**
     * Run the taps that have not proven to be a composed gesture.
     */
    void executeTap();

private:

    /**
     * Create a estandar gesture with their action.
     * @param  type  Gesture type.
     * @param  id    Gesture ID.
     * @param  attrs Gesture attributes, where the key is the name of the
     *         attribute (ie "focus x", "touches") and the value the value of
     *         the attribute.
     * @param  isComposedGesture If is a composed gesture (tap&hold, double
     *         tap) or not.
     * @return The gesture or NULL.
     */
    Gesture *createGesture(const QString &type, int id, const QHash<QString, QVariant>& attrs,
        bool isComposedGesture) const;

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Returns window over the gestures is make.
     * @param  window The window that GEIS returns.
     * @return This window.
     */
    Window getGestureWindow(Window window) const;

    /**
     * Returns the top level window of the specified window.
     * @param  window The window.
     * @return This window.
     */
    Window getTopLevelWindow(Window window) const;

    /**
     * Returns the class of a window, for example, "XTerm" is the class of all instances of XTerm.
     * @param  window This window.
     * @return The class.
     */
    QString getAppClass(Window window) const;

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Gesture that is running.
     */
    Gesture *currentGesture;

    /**
     * Timer that running the taps always that the gesture does not prove to be a composed gesture.
     */
    QTimer *timerTap;

    /**
     * Factory to create gestures.
     */
    GestureFactory *gestureFact;

    /**
     * Factory to create actions.
     */
    ActionFactory *actionFact;

    /**
     * Provides access to the configuration.
     */
    Config *config;

};

#endif // GESTUREHANDLER_H
