/**
 * @file /src/touchegg-gui/presentation/widgets/MenuItem.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MenuItem
 * @author José Expósito
 */
#ifndef MENUITEM_H
#define MENUITEM_H

#include "src/touchegg-gui/util/Include.h"
namespace Ui { class MenuItem; }

/**
 * @~spanish
 * Widget con un icono y un texto para el menú de la izquierda.
 *
 * @~english
 * Widget with a icon and a text for the menu of the left.
 */
class MenuItem : public QWidget {

    Q_OBJECT

    private:

        Ui::MenuItem *ui;

    public:

        /**
         * @~spanish
         * Constructor por defecto.
         * @param icon Icono a mostrar.
         * @param text Texto a mostrar.
         * @param parent Padre del widget.
         *
         * @~english
         * Constructor by default.
         * @param icon Icon to show.
         * @param text Text to show.
         * @param parent Parent of the widget.
         */
        MenuItem(const QIcon& icon, const QString& text, QWidget* parent = 0);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * Destructor.
         */
        ~MenuItem();

};

#endif // MENUITEM_H
