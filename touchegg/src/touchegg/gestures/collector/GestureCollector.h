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
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011
 * @class  GestureCollector
 */
#ifndef GESTURECOLLECTOR_H
#define GESTURECOLLECTOR_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/config/Config.h"

/**
 * @~spanish
 * Recoge todos los gestos haciendo uso de utouch-geis y emite señales para
 * informar de ello.
 *
 * @~snglish
 * Collect all the gestures using utouch-geis and emits signals to report it.
 */
class GestureCollector : public QThread
{
    Q_OBJECT

private:

    /**
     * @~spanish
     * Instancia de GEIS v2.0 API.
     *
     * @~english
     * Single instance of the GEIS v2.0 API.
     */
    Geis geis;

    /**
     * @~spanish
     * Hash con todas las suscripciones creadas. Vale para poder liberarlas.
     *
     * @~english
     * Hash with all the created subscriptions. Used to free it.
     */
    QHash<Window, QList<GeisSubscription> > subscriptions;

    /**
     * @~spanish
     * Hash con todos los filtros creados. Vale para poder liberarlos.
     *
     * @~english
     * Hash with all the created filters. Used to free it.
     */
    QHash<Window, QList<GeisFilter> > filters;

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Devuelve un QHash con todos los atributos de un gesto, siendo la
     * clave el nombre del atributo (por ejemplo "focus x", "touches"...) y
     * el valor el valor del propio atributo.
     * @param event Información del gesto.
     * @return El QHash
     *
     * @~english
     * Returns a Hash with all attributes of a gesture, where the key is the
     * name of the attribute (ie "focus x", "touches") and the value the
     * value of the attribute.
     * @param event Information of the gesture.
     * @return The hash.
     */
    static QHash<QString, QVariant> getGestureAttrs(GeisEvent event);

    /**
     * @~spanish
     * Devuelve la clase de la ventana especificada.
     * @param  window Dicha ventana.
     * @return La clase.
     *
     * @~english
     * Returns the class of the specified window.
     * @param  window This window.
     * @return The class.
     */
    QString getWindowClass(Window window) const;

protected:

    /**
     * @~spanish
     * Función de inicio del hilo.
     *
     * @~english
     * Thread start function.
     */
    void run();

public:

    /**
     * @~spanish
     * Crea un GestureCollector para escuchar los eventos multitouch de la
     * ventana indicada.
     * @param w Dicha ventana.
     *
     * @~english
     * Creates a GestureCollector to listen the multitouch events of the
     * specified window.
     * @param w This window.
     */
    GestureCollector();

    /**
     * @~spanish
     * Destructor.
     *
     * @~english
     * Destructor.
     */
    virtual ~GestureCollector();

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Añade una ventana en la que escuchar lo gestos mltitouch.
     * @param w La ventana.
     *
     * @~english
     * Adds a window where listen to multitouch gestures.
     * @param w The window.
     */
    void addWindow(Window w);

    /**
     * @~spanish
     * Elimina una ventana en la que escuchar lo gestos mltitouch.
     * @param w La ventana.
     *
     * @~english
     * Removes a window where listen to multitouch gestures.
     * @param w The window.
     */
    void removeWindow(Window w);

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Función callback que se llamará cuando se inicie un gesto.
     * @param clt   Puntero a la propia clase.
     * @param event Evento con la información del gesto.
     *
     * @~english
     * Callback function that is called when a gesture starts.
     * @param clt   Pointer to the class itself.
     * @param event Event with the gesture information.
     */
    static void gestureStart(GestureCollector *gc, GeisEvent event);

    /// @see gestureStart()
    static void gestureUpdate(GestureCollector *gc, GeisEvent event);

    /// @see gestureStart()
    static void gestureFinish(GestureCollector *gc, GeisEvent event);

signals:

    /**
     * @~spanish
     * Señal que se emitirá cuando un gesto se inicie.
     * @param type  Tipo del gesto.
     * @param id    ID del gesto.
     * @param attrs Atributos del gestos, siendo la clave el nombre del
     *        atributo (por ejemplo "focus x", "touches"...) y el valor el
     *        valor del propio atributo.
     * @param w      ID de la ventana asociada al GestureCollector.
     * @param wClass Clase de la ventana asociada al GestureCollector.
     *
     * @~english
     * Signal is emitted when a gesture starts.
     * @param type  Gesture type.
     * @param id    Gesture ID.
     * @param attrs Gesture attributes, where the key is the name of the
     *        attribute (ie "focus x", "touches") and the value the value of
     *        the attribute.
     * @param w      ID of the window associated to the GestureCollector.
     * @param wClass Class of the window associated to the GestureCollector.
     */
    void executeGestureStart(const QString &type, int id,
        const QHash<QString, QVariant>& attrs);

    /// @see executeGestureStart()
    void executeGestureUpdate(const QString &type, int id,
        const QHash<QString, QVariant>& attrs);

    /// @see executeGestureStart()
    void executeGestureFinish(const QString &type, int id,
        const QHash<QString, QVariant>& attrs);

};

#endif // GESTURECOLLECTOR_H
