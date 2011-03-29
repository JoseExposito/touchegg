/**
 * @file src/touchegg/actions/types/ActionTypeEnum.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ActionTypeEnum
 * @author José Expósito
 */
#ifndef ACTIONTYPEENUM_H
#define ACTIONTYPEENUM_H

#include "src/touchegg/util/Include.h"


/**
 * @~spanish
 * Contiene un tipo enumerado con las acciones soportadas.
 *
 * @~english
 * Contains a enumeradted type with supported actions.
 */
class ActionTypeEnum : public QObject {

    Q_OBJECT
    Q_ENUMS(ActionType);

    public:

        /**
         * @~spanish
         * Tipo enumerado con las acciones soportadas.
         *
         * @~english
         * Enumerated type with supported actions.
         */
        enum ActionType {
            NO_ACTION,
            MOUSE_MOVE,
            RIGHT_BUTTON_CLICK,
            MIDDLE_BUTTON_CLICK,
            VERTICAL_SCROLL,
            HORIZONTAL_SCROLL,
            MINIMIZE_WINDOW,
            MAXIMIZE_RESTORE_WINDOW,
            CLOSE_WINDOW,
            RESIZE_WINDOW,
            SHOW_DESKTOP,
            CHANGE_DESKTOP,
            SEND_KEYS,
            MOVE_WINDOW,
            RUN_COMMAND,
            DRAG_AND_DROP,
            LEFT_BUTTON_CLICK
        };

        /**
         * @~spanish
         * Convierte el tipo enumedrado a QString.
         * @return El QString
         *
         * @~english
         * Converts the enum to QString.
         * @return The QString.
         */
        static QString getValue(ActionType atEnum);

        /**
         * @~spanish
         * Convierte el QString indicado en su equivalente tipo enumedrado.
         * @return El tipo enumerado
         *
         * @~english
         * Converts the indicated QString to the equivalent enum type.
         * @return The enum type.
         */
        static ActionType getEnum(const QString& atString);
};

#endif // ACTIONTYPEENUM_H
