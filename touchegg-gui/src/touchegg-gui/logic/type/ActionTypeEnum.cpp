/**
 * @file /src/touchegg-gui/logic/type/ActionTypeEnum.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ActionTypeEnum
 * @author José Expósito
 */
#include "ActionTypeEnum.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

QString ActionTypeEnum::getValue(ActionType atEnum) {
    ActionTypeEnum actionTypeEnum;
    int index = actionTypeEnum.metaObject()->indexOfEnumerator("ActionType");
    QMetaEnum metaEnum = actionTypeEnum.metaObject()->enumerator(index);
    return metaEnum.valueToKey(atEnum);
}

ActionTypeEnum::ActionType ActionTypeEnum::getEnum(const QString& atString) {
    ActionTypeEnum actionTypeEnum;
    int index = actionTypeEnum.metaObject()->indexOfEnumerator("ActionType");
    QMetaEnum metaEnum = actionTypeEnum.metaObject()->enumerator(index);
    return (ActionTypeEnum::ActionType)metaEnum.keyToValue(
            atString.toStdString().c_str());
}
