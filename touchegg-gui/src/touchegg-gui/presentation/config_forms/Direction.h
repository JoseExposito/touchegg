/**
 * @file /src/touchegg-gui/presentation/config_forms/Direction.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  Direction
 * @author José Expósito
 */
#ifndef DIRECTION_H
#define DIRECTION_H

#include "src/touchegg-gui/presentation/config_forms/ConfigForm.h"
namespace Ui { class Direction; }

/**
 * @~spanish
 * Permite seleccionar una dirección, ver la documentación en ConfigForm.
 *
 * @~english
 * Allows to select a direction, see the documentation in ConfigForm.
 */
class Direction : public ConfigForm {

    Q_OBJECT

    private:

        Ui::Direction *ui;

    public:

        Direction();

        ~Direction();

        QString getSettings() const;

        void setSettings(const QString& settings);

};

#endif // DIRECTION_H
