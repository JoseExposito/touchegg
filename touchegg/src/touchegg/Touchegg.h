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
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011
 * @class  Touchegg
 */
#ifndef TOUCHEGG_H
#define TOUCHEGG_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/gestures/collector/GestureCollector.h"
#include "src/touchegg/gestures/handler/GestureHandler.h"

/**
 * @~spanish
 * Inicializa y conecta el GestureCollector y el GestureHandler. Además escucha
 * la creación/destrucción de ventanas, indicandoselo al GestureCollector.
 *
 * @~english
 * Initializes and connect the GestureCollector and the GestureHandler. In
 * addition, listens for the creation/destruction of windows, sending signals to
 * the GestureCollector.
 */
class Touchegg : public QApplication
{
    Q_OBJECT

private:

    /**
     * @~spanish
     * Bucle que recoge todos los gestos producidos.
     *
     * @~english
     * Loop that collects all the gestures produced.
     */
    GestureCollector* gestureCollector;

    /**
     * @~spanish
     * Recoge todos los gestos que captura GestureCollector y los trata.
     *
     * @~english
     * Collect all the gestures that captures GestureCollector and handle.
     */
    GestureHandler* gestureHandler;

    /**
     * @~spanish
     * Lista con las ventanas existentes. Es necesaria para poder subscribirnos
     * a los eventos multitouch de las ventanas que lo requieran.
     *
     * @~englis
     * List with the existing windows. Is necessary for subscribe to de
     * multitouch events to the windows that requires it.
     */
    QList<Window> clientList;

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Devuelve la lista de ventanas existentes.
     * @return Dicha lista.
     *
     * @~english
     * Returns the list of existing windows.
     * @return The list.
     */
    QList<Window> getClientList() const;

    /**
     * @~spanish
     * Dadas dos listas de ventanas devuelve la diferencia entre ellas, que
     * coincidirá con la última ventana creada/eliminada.
     * @param  lnew  La lista con las ventanas nuevas.
     * @param  lold  La lista con las ventanas viejas.
     * @param  isNew true si la ventana devuelta ha sido creada, false si ha
     *         sido eliminada.
     * @return La ventana creada/eliminada o None si las dos listas son iguales.
     *
     * @~english
     * Given two lists of windows returns the difference between them,
     * corresponding to the last window created/deleted.
     * @param  lnew  The list with the new windows.
     * @param  lold  The list with the old windows.
     * @param  isNew true if the returned window has been created, false if has
     *         been deleted.
     * @return The created/deleted window or None if the two list are equals.
     */
    Window getDifferentWindow(QList<Window> lnew, QList<Window> lold,
            bool* isNew) const;

protected:

    /**
     * @~spanish
     * Reimplementa el método QApplication::x11EventFilter. En este método se
     * recibirán las notificaciones de creación/destrucción de ventanas (previa
     * llamada a XSelectInput en el constructor) y se gestionarán como
     * corresponda.
     * @param event El evento que se ha producido.
     * @return true para evitar que el evento sea tratado con normalidad, es
     *         decir, cuando ya lo tratamos nosotros, false para que el
     *         evento se trate connormalidad.
     *
     * @~english
     * Reimplement the method QApplication::x11EventFilter. This method receives
     * the notifications of creation/destruction of windows (previously calling
     * XSelectInput function in the constructor) and manage it as appropiate
     * using the correct event handler.
     * @param event The event that occurred.
     * @return true if you want to stop the event from being processed, ie
     *         when we treat ourselves, false for normal event dispatching.
     */
    virtual bool x11EventFilter(XEvent* event);

public:

    /**
     * @~spanish
     * Inicializa Touchégg.
     *
     * @~english
     * Initializes Touchégg.
     */
    Touchegg(int argc, char** argv);

    /**
     * @~spanish
     * Destructor.
     *
     * @~english
     * Destructor.
     */
    virtual ~Touchegg();

public slots:

    /**
     * @~spanish
     * Lanza Touchégg
     *
     * @~english
     * Launch Touchégg.
     */
    void start();

signals:

    /**
     * @~spanish
     * Señal que se envía al GestureCollector para que escuche los eventos
     * multitouch en la ventana indicada.
     *
     * @~english
     * Signal that is send to the GestureCollector for listen the multitouch
     * events in the specified window.
     */
    void addListener(Window w);

    /**
     * @~spanish
     * Señal que se envía al GestureCollector para que deje de escuchar los
     * eventos multitouch en la ventana indicada.
     *
     * @~english
     * Signal that is send to the GestureCollector for stop listen the
     * multitouch events in the specified window.
     */
    void removeListener(Window w);

};

#endif // TOUCHEGG_H
