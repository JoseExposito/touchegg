/**
 * @file /src/touchegg-gui/presentation/main_window/TapAndHoldTab.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  TapAndHoldTab
 * @author José Expósito
 */
#include "TapAndHoldTab.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

TapAndHoldTab::TapAndHoldTab() {
    // Estilo del panel
    this->setFrameShape(QFrame::NoFrame);
    this->setFrameShadow(QFrame::Plain);

    // Ponemos los componentes dentro del scroll area
    /*QFrame* aux = new QFrame;
    aux->setLayout(layout);
    this->setWidget(aux);
    this->setWidgetResizable(true);*/
}
