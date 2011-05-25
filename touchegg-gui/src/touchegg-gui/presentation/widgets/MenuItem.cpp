/**
 * @file /src/touchegg-gui/presentation/widgets/MenuItem.cpp
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
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#include "MenuItem.h"
#include "ui_MenuItem.h"


// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MenuItem::MenuItem(const QIcon& icon, const QString& text, QWidget* parent)
        : QWidget(parent)
        , ui(new Ui::MenuItem) {
    ui->setupUi(this);
    this->ui->textLabel->setText(text);
    this->ui->iconLabel->setPixmap(icon.pixmap(60, 60));
}

MenuItem::~MenuItem() {
    delete ui;
}
