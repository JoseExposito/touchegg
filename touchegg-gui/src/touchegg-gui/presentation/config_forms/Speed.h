/**
 * @file /src/touchegg-gui/presentation/config_forms/Speed.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  Speed
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#ifndef SPEED_H
#define SPEED_H

#include "src/touchegg-gui/presentation/config_forms/ConfigForm.h"
namespace Ui { class Speed; }


/**
 * @~spanish
 * Permite seleccionar un botón del ratón, ver la documentación en ConfigForm.
 *
 * @~english
 * Allows to select a mouse button, see the documentation in ConfigForm.
 */
class Speed : public ConfigForm {

    Q_OBJECT

    private:

        Ui::Speed *ui;

    public:

        Speed();

        ~Speed();

        QString getSettings() const;

        void setSettings(const QString& settings);

};

#endif // SPEED_H
