/**
 * @file /src/touchegg/Touchegg.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  Touchegg
 * @author José Expósito
 */
#ifndef TOUCHEGG_H
#define TOUCHEGG_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/config/Config.h"
#include "src/touchegg/gestures/handler/GestureHandler.h"
#include "src/touchegg/gestures/collector/GestureCollector.h"

/**
 * @~spanish
 * Inicializa y lanza Touchégg.
 *
 * @~english
 * Initializes and launch Touchégg.
 */
class Touchegg : public QObject {

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
         * Inicializa y lanza Touchégg.
         *
         * @~english
         * Initializes and launch Touchégg.
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
};

#endif // TOUCHEGG_H
