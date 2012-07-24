/**
 * @file /src/touchegg/gestures/implementation/Gesture.cpp
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
 * @class  Gesture
 */
#include "Gesture.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

Gesture::Gesture(GestureTypeEnum::GestureType type, int numFingers, GestureDirectionEnum::GestureDirection dir, int id,
    const QHash<QString, QVariant>& attrs)
    : type(type),
      numFingers(numFingers),
      dir(dir),
      id(id),
      attrs(attrs)
{

}

Gesture::~Gesture()
{
    delete this->action;
}


// ****************************************************************************************************************** //
// **********                                        PUBLIC METHODS                                        ********** //
// ****************************************************************************************************************** //

void Gesture::start() const
{
    if (this->action != NULL)
        this->action->executeStart(this->attrs);
}

void Gesture::update() const
{
    if (this->action != NULL)
        this->action->executeUpdate(this->attrs);
}

void Gesture::finish() const
{
    if (this->action != NULL)
        this->action->executeFinish(this->attrs);
}


// ****************************************************************************************************************** //
// **********                                          GET/SET/IS                                          ********** //
// ****************************************************************************************************************** //

GestureTypeEnum::GestureType Gesture::getType() const
{
    return this->type;
}

int Gesture::getNumFingers() const
{
    return this->numFingers;
}

GestureDirectionEnum::GestureDirection Gesture::getDirection() const
{
    return this->dir;
}

int Gesture::getId() const
{
    return this->id;
}

const QHash<QString, QVariant>& Gesture::getAttrs() const
{
    return this->attrs;
}

const Action *Gesture::getAction() const
{
    return this->action;
}

//----------------------------------------------------------------------------------------------------------------------

void Gesture::setType(GestureTypeEnum::GestureType type)
{
    this->type = type;
}

void Gesture::setNumFingers(int numFingers)
{
    this->numFingers = numFingers;
}

void Gesture::setDirection(GestureDirectionEnum::GestureDirection dir)
{
    this->dir = dir;
}

void Gesture::setId(int id)
{
    this->id = id;
}

void Gesture::setAttrs(const QHash<QString, QVariant>& attrs)
{
    this->attrs = attrs;
}

void Gesture::setAction(Action *action)
{
    this->action = action;
}
