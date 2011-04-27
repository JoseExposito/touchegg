/**
 * @file /src/touchegg-gui/presentation/config_forms/ConfigForm.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  ConfigForm
 * @author José Expósito
 */
#ifndef CONFIGFORM_H
#define CONFIGFORM_H

#include "src/touchegg-gui/util/Include.h"

/**
 * @~spanish
 * Clase base para los formularios de configuración.
 *
 * @~english
 * Base class for the config forms.
 */
class ConfigForm : public QDialog {

    Q_OBJECT

    public:

        /**
         * @~spanish
         * Devuelve la configuración introducida en el formulario.
         * @return La configuración.
         *
         * @~english
         * Returns the configuration introduced in the form.
         * @return The configuration.
         */
        virtual QString getSettings() const = 0;

        /**
         * @~spanish
         * Establece la configuración del formulario.
         * @param settings La configuración.
         *
         * @~english
         * Sets the configuration.
         * @param settings The configuration.
         */
        virtual void setSettings(const QString& settings) = 0;

    signals:

        /**
         * @~spanish
         * Señal que se emitirá cada vez que la configuración cambie.
         *
         * @~english
         * Signal that will emit each time that configuration changes.
         */
        void configChanged() const;
};

#endif // CONFIGFORM_H
