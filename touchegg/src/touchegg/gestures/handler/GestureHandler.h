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
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011
 * @class  GestureHandler
 */
#ifndef GESTUREHANDLER_H
#define GESTUREHANDLER_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/config/Config.h"
#include "src/touchegg/gestures/factory/GestureFactory.h"
#include "src/touchegg/actions/factory/ActionFactory.h"

/**
 * @~spanish
 * Clase que recibe los gestos, los procesa y ejecuta la acción correspondiente.
 *
 * @~english
 * Class that receives the gestures, processes it and execute the corresponding
 * action.
 */
class GestureHandler : public QObject
{

    Q_OBJECT

private:

    /**
     * @~spanish
     * Gesto que se está ejecutando.
     *
     * @~english
     * Gesture that is running.
     */
    Gesture* currentGesture;

    /**
     * @~spanish
     * Timer que ejecuta los taps siempre que el gesto no resulte ser un
     * tap&hold.
     *
     * @~english
     * Timer that running the taps always that the gesture does not prove
     * to be a tap&hold.
     */
    QTimer* timerTap;

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Factoría para crear los gestos.
     *
     * @~english
     * Factory to create gestures.
     */
    GestureFactory* gestureFact;

    /**
     * @~spanish
     * Factoría para crear las acciones.
     *
     * @~english
     * Factory to create gestures.
     */
    ActionFactory* actionFact;

    /**
     * @~spanish
     * Provee acceso a la configurración.
     *
     * @~english
     * Provides access to configurración.
     */
    Config* config;

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Crea un gesto estandar con su acción.
     * @param  type  Tipo del gesto.
     * @param  id    ID del gesto.
     * @param  attrs Atributos del gestos, siendo la clave el nombre del
     *         atributo (por ejemplo "focus x", "touches"...) y el valor el
     *         valor del propio atributo.
     * @param  isComposedGesture Si es un gesto compuesto (tap&hold, double
     *         tap...) o no.
     * @param  gestureWindow ID de la ventana sobre la que se ejecuta el gesto.
     * @param  wClass Clase de la ventana sobre la que se produce el gesto.
     * @return El gesto o NULL.
     *
     * @~english
     * Create a estandar gesture with their action.
     * @param  type  Gesture type.
     * @param  id    Gesture ID.
     * @param  attrs Gesture attributes, where the key is the name of the
     *         attribute (ie "focus x", "touches") and the value the value of
     *         the attribute.
     * @param  isComposedGesture If is a composed gesture (tap&hold, double
     *         tap) or not.
     * @param  gestureWindow ID of the window on which the gesture occurs.
     * @param  wClass Class of the window on which the gesture occurs.
     * @return The gesture or NULL.
     */
    Gesture* createGesture(const QString &type, int id,
        const QHash<QString, QVariant>& attrs, bool isComposedGesture) const;

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Devuelve la ventana sobre la que se produce el gesto.
     * @param  window Ventana que nos pasa GEIS.
     * @return Dicha ventana.
     *
     * @~english
     * Returns window over the gestures is make.
     * @param  window The window that GEIS returns.
     * @return This window.
     */
    Window getGestureWindow(Window window) const;

    /**
     * @~spanish
     * Devuelve la ventana de más alto nivel de la ventana indicada.
     * @param  window La ventana.
     * @return Dicha ventana
     *
     * @~english
     * Returns the top level window of the specified window.
     * @param  window The window.
     * @return This window.
     */
    Window getTopLevelWindow(Window window) const;

    /**
     * @~spanish
     * Devuelve la clase de la ventana especificada, por ejemplo, para
     * cualquier ventana de XTerm la clase será "XTerm".
     * @param  window Dicha ventana.
     * @return La clase.
     *
     * @~english
     * Returns the class of a window, for example, "XTerm" is the class of
     * all instances of XTerm.
     * @param  window This window.
     * @return The class.
     */
    QString getAppClass(Window window) const;

private slots:

    /**
     * @~spanish
     * Ejecuta los taps que no han resultado ser un tap&hold.
     *
     * @~english
     * Run the taps that have not proven to be a tap&hold.
     */
    void executeTap();

public:

    /**
     * @~spanish
     * Constructor.
     *
     * @~english
     * Constructor.
     */
    GestureHandler();

    /**
     * @~spanish
     * Destructor.
     *
     * @~english
     * Destructor.
     */
    virtual ~GestureHandler();

public slots:

    /**
     * @~spanish
     * Ejecuta el gesto indicado.
     * @param type   Tipo del gesto.
     * @param id     ID del gesto.
     * @param attrs  Atributos del gestos, siendo la clave el nombre del
     *        atributo (por ejemplo "focus x", "touches"...) y el valor el
     *        valor del propio atributo.
     *
     * @~english
     * Runs the indicated gesture.
     * @param type   Gesture type.
     * @param id     Gesture ID.
     * @param attrs  Gesture attributes, where the key is the name of the
     *        attribute (ie "focus x", "touches") and the value the value of
     *        the attribute.
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

#endif // GESTUREHANDLER_H
