/**
 * @file /src/touchegg/gestures/implementations/Gesture.h
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
 * @class  Gesture
 */
#ifndef GESTURE_H
#define GESTURE_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/gestures/types/GestureTypeEnum.h"
#include "src/touchegg/gestures/types/GestureDirectionEnum.h"
#include "src/touchegg/actions/implementation/Action.h"

/**
 * @~spanish
 * Clase de la que deben heredar todos los gestos.
 *
 * @~english
 * Class that should inherit all the gestures.
 */
class Gesture
{

private:

    /**
     * @~spanish
     * Tipo del gesto.
     *
     * @~english
     * Gesture type.
     */
    GestureTypeEnum::GestureType type;

    /**
     * @~spanish
     * Número de dedos usados por el gesto.
     *
     * @~english
     * Number of fingers used by the gesture.
     */
    int numFingers;

    /**
     * @~spanish
     * Dirección del gesto.
     *
     * @~english
     * Direction of the gesture.
     */
    GestureDirectionEnum::GestureDirection dir;

    /**
     * @~spanish
     * ID del gesto.
     *
     * @~english
     * Gesture ID.
     */
    int id;

    /**
     * @~spanish
     * Atributos del gestos, siendo la clave el nombre del atributo (por
     * ejemplo "focus x", "touches"...) y el valor el valor del propio
     * atributo.
     *
     * @~english
     * Gesture attributes, where the key is the name of the attribute (ie
     * "focus x", "touches") and the value the value of the attribute.
     */
    QHash<QString, QVariant> attrs;

    /**
     * @~spanish
     * Acción asociada al gesto.
     *
     * @~english
     * Action associated to the gesture.
     */
    Action* action;

public:

    /**
     * @~spanish
     * Crea un gesto con las propiedades indicadas.
     * @param type   Tipo del gesto.
     * @param numFingers Número de dedos usados por el gesto.
     * @param dir Dirección del gesto.
     * @param id ID del gesto.
     * @param attrs Atributos del gestos, siendo la clave el nombre del
     *        atributo (por ejemplo "focus x", "touches"...) y el valor el
     *        valor del propio atributo.
     *
     * @~english
     * Creates a gesture with the specified properties.
     * @param type   Gesture type.
     * @param gestureType The gesture that is made.
     * @param numFingers Number of fingers used by the gesture.
     * @param dir Direction of the gesture.
     * @param id Gesture ID.
     * @param attrs Gesture attributes, where the key is the name of the
     *        attribute (ie "focus x", "touches") and the value the value of
     *        the attribute.
     */
    Gesture(GestureTypeEnum::GestureType type, int numFingers,
        GestureDirectionEnum::GestureDirection dir, int id,
        const QHash<QString, QVariant>& attrs);

    /**
     * @~spanish
     * Destructor.
     *
     * @~english
     * Destructor.
     */
    ~Gesture();

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Se llama cuando el gesto se inicia.
     *
     * @~english
     * Is called when the gesture is started.
     */
    void start() const;

    /**
     * @~spanish
     * Se llama cuando el gesto se actualiza.
     *
     * @~english
     * Is called when the gesture is updated.
     */
    void update() const;

    /**
     * @~spanish
     * Se llama cuando el gesto se finaliza.
     *
     * @~english
     * Is called when the gesture is finished.
     */
    void finish() const;

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Devuelve el tipo del gesto.
     * @return El tipo.
     *
     * @~english
     * Returns the gesture type.
     * @return The type.
     */
    GestureTypeEnum::GestureType getType() const;

    /**
     * @~spanish
     * Devuelve el número de dedos usados por el gesto.
     * @return El número de dedos.
     *
     * @~english
     * Returns the number of fingers used by the gesture.
     * @return The number of fingers.
     */
    int getNumFingers() const;

    /**
     * @~spanish
     * Devuelve la dirección del gesto.
     * @return La dirección.
     *
     * @~english
     * Returns the direction of the gesture.
     * @return The direction.
     */
    GestureDirectionEnum::GestureDirection getDirection() const;

    /**
     * @~spanish
     * Devuelve el ID del gesto.
     * @return El ID.
     *
     * @~english
     * Returns the gesture ID.
     * @return The ID.
     */
    int getId() const;

    /**
     * @~spanish
     * Devuelve los atributos del gesto.
     * @return Los atributos.
     *
     * @~english
     * Returns the gesture attributes.
     * @return The attributes.
     */
    const QHash<QString, QVariant>& getAttrs() const;

    /**
     * @~spanish
     * Devuelve la acción asociada al gesto.
     * @return La acción.
     *
     * @~english
     * Returns the gesture action.
     * @return The action.
     */
    const Action* getAction() const;

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Establece el tipo del gesto.
     * @param type El tipo.
     *
     * @~english
     * Sets the gesture type.
     * @param type The type.
     */
    void setType(GestureTypeEnum::GestureType type);

    /**
     * @~spanish
     * Establece el número de dedos usados por el gesto.
     * @return El número de dedos.
     *
     * @~english
     * Sets the number of fingers used by the gesture.
     * @return The number of fingers.
     */
    void setNumFingers(int numFingers);

    /**
     * @~spanish
     * Establece la dirección del gesto.
     * @return La dirección.
     *
     * @~english
     * Sets the direction of the gesture.
     * @return The direction.
     */
    void setDirection(GestureDirectionEnum::GestureDirection dir);

    /**
     * @~spanish
     * Establece el ID del gesto.
     * @param id El ID.
     *
     * @~english
     * Sets the gesture ID.
     * @param id The ID.
     */
    void setId(int id);

    /**
     * @~spanish
     * Establece los atributos del gesto.
     * @param attrs Los atributos.
     *
     * @~english
     * Sets the gesture attributes.
     * @param attrs The attributes.
     */
    void setAttrs(const QHash<QString, QVariant>& attrs);

    /**
     * @~spanish
     * Establece la acción a ejecutar por el gesto.
     * @param action La acción.
     *
     * @~english
     * Sets the action to be executed by gesture.
     * @param action The action.
     */
    void setAction(Action* action);

};

#endif // GESTURE_H
