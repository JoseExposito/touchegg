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
 * Inicializa y lanza Touchégg.
 *
 * @~english
 * Initializes and launch Touchégg.
 */
class Touchegg : public QObject
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

public:

    /**
     * @~spanish
     * Inicializa Touchégg.
     *
     * @~english
     * Initializes Touchégg.
     */
    Touchegg();

    /**
     * @~spanish
     * Destructor.
     *
     * @~english
     * Destructor.
     */
    virtual ~Touchegg();

    /**
     * @~spanish
     * Lanza Touchégg
     *
     * @~english
     * Launch Touchégg
     */
    void start();

};

#endif // TOUCHEGG_H
