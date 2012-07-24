/**
 * @file src/touchegg/gestures/types/GestureDirectionEnum.h
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
 * @class  GestureDirectionEnum
 */
#ifndef GESTUREDIRECTIONENUM_H
#define GESTUREDIRECTIONENUM_H

#include "src/touchegg/util/Include.h"

/**
 * Contains an enumerated type with availables directions of gestures.
 */
class GestureDirectionEnum : public QObject
{

    Q_OBJECT
    Q_ENUMS(GestureDirection)

public:

    /**
     * Enumerated type with supported directions.
     */
    enum GestureDirection {
        NO_DIRECTION,
        ALL,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        IN,
        OUT
    };

    /**
     * Converts the enum to QString.
     * @return The QString.
     */
    static QString getValue(GestureDirection gtEnum);

    /**
     * Converts the indicated QString to the equivalent enum type.
     * @return The enum type.
     */
    static GestureDirection getEnum(const QString &gtString);

};

#endif // GESTUREDIRECTIONENUM_H
