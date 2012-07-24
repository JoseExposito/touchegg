/**
 * @file /src/touchegg/gestures/collector/GestureCollector.h
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
 * @class  GestureCollector
 */
#ifndef GESTURECOLLECTOR_H
#define GESTURECOLLECTOR_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/config/Config.h"

/**
 * Collect all the gestures using utouch-geis and emits signals to report it.
 */
class GestureCollector : public QObject
{
    Q_OBJECT

public:

    /**
     * Default constructor.
     * @param parent The parent of the class.
     */
    GestureCollector(QObject *parent = 0);

    /**
     * Destructor.
     */
    virtual ~GestureCollector();

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Callback function that is called when a gesture starts.
     * @param gc    Pointer to the class itself.
     * @param event Event with the gesture information.
     */
    static void gestureStart(GestureCollector *gc, GeisEvent event);

    /// @see gestureStart()
    static void gestureUpdate(GestureCollector *gc, GeisEvent event);

    /// @see gestureStart()
    static void gestureFinish(GestureCollector *gc, GeisEvent event);

    /**
     * Initialize list of avalilable gesture classes.
     *
     * @param event Event with available gesture information.
     */
    static void setupGestureEvent(GeisEvent event);

public slots:

    /**
     * Adds a window where listen to multitouch gestures.
     * @param w The window.
     */
    void addWindow(Window w);

    /**
     * Removes a window where listen to multitouch gestures.
     * @param w The window.
     */
    void removeWindow(Window w);

signals:

    /**
     * Signal emited when uTouch is inicializzed.
     */
    void ready();

    /**
     * Signal that is emitted when a gesture starts.
     * @param type  Gesture type.
     * @param id    Gesture ID.
     * @param attrs Gesture attributes, where the key is the name of the
     *        attribute (ie "focus x", "touches") and the value the value of
     *        the attribute.
     */
    void executeGestureStart(const QString &type, int id, const QHash<QString, QVariant>& attrs);

    /// @see executeGestureStart()
    void executeGestureUpdate(const QString &type, int id, const QHash<QString, QVariant>& attrs);

    /// @see executeGestureStart()
    void executeGestureFinish(const QString &type, int id, const QHash<QString, QVariant>& attrs);

private slots:

    /**
     * Slot that is called whenever a gesture is generated.
     */
    void geisEvent();

private:

    /**
     * Returns a Hash with all attributes of a gesture, where the key is the name of the attribute (ie "focus x",
     * "touches") and the value the value of the attribute.
     * @param event Information of the gesture.
     * @return The hash.
     */
    static QHash<QString, QVariant> getGestureAttrs(GeisEvent event);

    /**
     * Returns the class of the specified window.
     * @param  window This window.
     * @return The class.
     */
    QString getWindowClass(Window window) const;

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Single instance of the GEIS v2.0 API.
     */
    Geis geis;

    /**
     * Socket notifier that will emit a activated() signal whenever a gestures is produced.
     */
    QSocketNotifier *socketNotifier;

    /**
     * Saves a list of the filters associated to a window to allow to unsuscribe when close the window.
     */
    QHash <Window, QList<GeisFilter> > filters;

    /**
     * Saves a list of the subscriptions associated to a window to allow to unsuscribe when close the window.
     */
    QHash <Window, QList<GeisSubscription> > subscriptions;

    /**
     * Saves a list of the avalilable gesture classes.
     */
    static QList <GeisGestureClass> gestures;
};

#endif // GESTURECOLLECTOR_H
