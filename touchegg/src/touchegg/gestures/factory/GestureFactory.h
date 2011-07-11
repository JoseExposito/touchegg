/**
 * @file /src/touchegg/gestures/factory/GestureFactory.h
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
 * @class  GestureFactory
 */
#ifndef GESTUREFACTORY_H
#define GESTUREFACTORY_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/gestures/types/GestureTypeEnum.h"
#include "src/touchegg/gestures/implementation/Gesture.h"

/**
 * @~spanish
 * Factoría para crear los distintos gestos.
 *
 * @~english
 * Factory to create the different gestures.
 */
class GestureFactory
{

private:

    /**
     * @~spanish
     * Única instancia de la clase.
     *
     * @~english
     * Single instance of the class.
     */
    static GestureFactory* instance;

    // Hide constructors
    GestureFactory(){}
    GestureFactory(const GestureFactory&);
    const GestureFactory& operator = (const GestureFactory&);

public:

    /**
     * @~spanish
     * Único método para obtener una instancia de la clase.
     * @return La única instancia de la clase.
     *
     * @~english
     * Only method to get an instance of the class.
     * @return The single instance of the class.
     */
    static GestureFactory* getInstance();

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Crea un gesto no-compuesto con las propiedades indicadas.
     * IMPORTANTE: No olvidar liberar memoria.
     * @param type  Tipo del gesto.
     * @param id    ID del gesto.
     * @param attrs Atributos del gestos, siendo la clave el nombre del
     *        atributo (por ejemplo "focus x", "touches"...) y el valor el
     *        valor del propio atributo.
     * @return El gesto.
     *
     * @~english
     * Creates a no-composed gesture with the specified properties.
     * IMPORTANT: Don't forget to free memory.
     * @param type  Gesture type.
     * @param id    Gesture ID.
     * @param attrs Gesture attributes, where the key is the name of the
     *        attribute (ie "focus x", "touches") and the value the value of
     *        the attribute.
     * @return The gesture.
     */
    Gesture* createSimpleGesture(GeisGestureType type, GeisGestureId id,
    QHash<QString, QVariant> attrs);

    /**
     * @~spanish
     * Crea un gesto compuesto (tap&hol, double tap...) con las propiedades
     * indicadas.
     * IMPORTANTE: No olvidar liberar memoria.
     * @param type  Tipo del gesto.
     * @param id    ID del gesto.
     * @param attrs Atributos del gestos, siendo la clave el nombre del
     *        atributo (por ejemplo "focus x", "touches"...) y el valor el
     *        valor del propio atributo.
     * @return El gesto.
     *
     * @~english
     * Creates a composed gesture (tap&hold, double tap...) with the
     * specified properties.
     * IMPORTANT: Don't forget to free memory.
     * @param type  Gesture type.
     * @param id    Gesture ID.
     * @param attrs Gesture attributes, where the key is the name of the
     *        attribute (ie "focus x", "touches") and the value the value of
     *        the attribute.
     * @return The gesture.
     */
    Gesture* createComposedGesture(GeisGestureType type, GeisGestureId id,
    QHash<QString, QVariant> attrs);
};

#endif // GESTUREFACTORY_H
