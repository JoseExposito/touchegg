/**
 * @file /src/touchegg/actions/implementation/DragAndDrop.cpp
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
 * @class  DragAndDrop
 */
#include "DragAndDrop.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

DragAndDrop::DragAndDrop(const QString &settings, Window window)
    : Action(settings, window)
{
    this->button = 1;

    QStringList strl = settings.split("=");
    if (strl.length() == 2 && strl.at(0) == "BUTTON") {
        bool ok = false;
        int aux = strl.at(1).toInt(&ok);

        if (ok && aux >= 1 && aux <= 9)
            this->button = aux;
        else
            qWarning() << "Error reading MOUSE_CLICK settings, using the default settings";
    } else {
        qWarning() << "Error reading MOUSE_CLICK settings, using the default settings";
    }
}


// ****************************************************************************************************************** //
// **********                                        PUBLIC METHODS                                        ********** //
// ****************************************************************************************************************** //

void DragAndDrop::executeStart(const QHash<QString, QVariant>& /*attrs*/)
{
    XTestFakeButtonEvent(QX11Info::display(), this->button, true, 0);
}

void DragAndDrop::executeUpdate(const QHash<QString, QVariant>& attrs)
{
    if (!attrs.contains(GEIS_GESTURE_ATTRIBUTE_DELTA_X) || !attrs.contains(GEIS_GESTURE_ATTRIBUTE_DELTA_Y))
        return;

    QCursor::setPos(QCursor::pos().x() + attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat(),
            QCursor::pos().y() + attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat());
}

void DragAndDrop::executeFinish(const QHash<QString, QVariant>& /*attrs*/)
{
    XTestFakeButtonEvent(QX11Info::display(), this->button, false, 0);
}
