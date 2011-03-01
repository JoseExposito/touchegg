/**
 * @file /src/touchegg-gui/presentation/gui_event/GuiEvent.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @author José Expósito
 */
#ifndef GUIEVENTS_H
#define GUIEVENTS_H

/**
 * @~spanish
 * Distintos eventos que recibirá o enviará el controlador de la interfaz.
 *
 * @~english
 * Different events that will receive or send the GUI controller.
 */
enum GuiEvent {
    READ_GENERAL_PROPERTY,
    UPDATE_GENERAL_PROPERTY,
    READ_GESTURE,
    UPDATE_GESTURE,
    COMMIT_DATA
};

#endif // GUIEVENTS_H
