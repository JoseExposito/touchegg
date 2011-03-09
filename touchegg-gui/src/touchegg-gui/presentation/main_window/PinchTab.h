/**
 * @file /src/touchegg-gui/presentation/main_window/PinchTab.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  PinchTab
 * @author José Expósito
 */
#ifndef PINCHTAB_H
#define PINCHTAB_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/presentation/widgets/GestureConfigWidget.h"
#include "src/touchegg-gui/logic/type/ActionTypeEnum.h"

/**
 * @~spanish
 * Pestaña para configurar los gestos de tipo "Pinch".
 *
 * @~english
 * Tab to configure "Pinch" gestures.
 */
class PinchTab : public QScrollArea  {

    public:

        /**
         * @~spanish
         * Constructor.
         *
         * @~english
         * Constructor.
         */
        PinchTab();
};

#endif // PINCHTAB_H
