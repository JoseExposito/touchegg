/**
 * @file /src/touchegg/Touchegg.cpp
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
#include "Touchegg.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

Touchegg::Touchegg()
    : gestureCollector(new GestureCollector),
    gestureHandler(new GestureHandler)
{

}

Touchegg::~Touchegg()
{
    if(this->gestureCollector->isRunning())
        this->gestureCollector->exit();

    delete this->gestureCollector;
    delete this->gestureHandler;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void Touchegg::start()
{
    // Conectamos GestureHandler con GestureHandler para que el último trate los
    // eventos que recoge el primero.
    qRegisterMetaType<GeisGestureType>("GeisGestureType");
    qRegisterMetaType<GeisGestureId>("GeisGestureId");

    connect(gestureCollector, SIGNAL(executeGestureStart(
            GeisGestureType,GeisGestureId,QHash<QString,QVariant>)),
            gestureHandler, SLOT(executeGestureStart(
            GeisGestureType,GeisGestureId,QHash<QString,QVariant>)));
    connect(gestureCollector, SIGNAL(executeGestureUpdate(
            GeisGestureType,GeisGestureId,QHash<QString,QVariant>)),
            gestureHandler, SLOT(executeGestureUpdate(
            GeisGestureType,GeisGestureId,QHash<QString,QVariant>)));
    connect(gestureCollector, SIGNAL(executeGestureFinish(
            GeisGestureType,GeisGestureId,QHash<QString,QVariant>)),
            gestureHandler, SLOT(executeGestureFinish(
            GeisGestureType,GeisGestureId,QHash<QString,QVariant>)));

    // Lanzamos GestureHandler en un hilo aparte para no congelar el bucle de
    // eventos de Qt
    this->gestureCollector->start();
}
