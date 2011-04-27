/**
 * @file /src/touchegg-gui/presentation/main_window/GesturesTab.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GesturesTab
 * @author José Expósito
 */
#ifndef GESTURESTAB_H
#define GESTURESTAB_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/logic/facade/Facade.h"
#include "src/touchegg-gui/presentation/widgets/GestureConfigWidget.h"
namespace Ui { class GesturesTab; }


/**
 * @~spanish
 * Pestaña para configurar los gestos.
 *
 * @~english
 * Tab to configure the gestures.
 */
class GesturesTab : public QFrame {

    Q_OBJECT

    private:

        Ui::GesturesTab *ui;

        /**
         * @~spanish
         * Carga los gestos y acciones asociados a la aplicación indicada.
         * @param app La aplicación.
         *
         * @~english
         * Loads the gestures and actions associated to the specified app.
         * @param app The application.
         */
        void loadConfiguration(const QString& app);

        /**
         * @~spanish
         * Borra la fila indicada de la tabla con los gestos.
         * @param row Dicha fila.
         * @param deleteConfig Si se borra la configuración usada por la fila
         *        de disco.
         *
         * @~english
         * Removes the indicated row from the gestures table.
         * @param row Such row.
         * @param deleteConfig If removes the configuration used by the row from
         * disc.
         */
        void removeGesture(int row, bool deleteConfig);

    public:

        /**
         * @~spanish
         * Constructor.
         *
         * @~english
         * Constructor.
         */
        GesturesTab(QWidget *parent = 0);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * Destructor.
         */
        ~GesturesTab();

    private slots:

        /**
         * @~spanish
         * Se llama cada vez que se selecciona una nueva aplicación a configurar
         * en el correspondiente combo-box.
         * @param app Nombre de la aplicación seleccionada.
         *
         * @~english
         * Is called whenever an application is selected in the combo-box to be
         * configurated.
         * @param app Name of the selected application.
         */
        void on_appCombo_currentIndexChanged(QString app);

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Se llama cada vez que se pulsa el botón de añadir gestos.
         *
         * @~english
         * Is called whenever the add gestures button is pressed.
         */
        void on_addGestureBtn_clicked();

        /**
         * @~spanish
         * Se llama cada vez que se pulsa el botón de quitar gestos.
         *
         * @~english
         * Is called whenever the remove gestures button is pressed.
         */
        void on_removeGestureBtn_clicked();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Se llama cada vez que se pulsa el botón de añadir aplicaciones.
         *
         * @~english
         * Is called whenever the add applications button is pressed.
         */
        void on_addAppBtn_clicked();

        /**
         * @~spanish
         * Se llama cada vez que se pulsa el botón de quitar aplicaciones.
         *
         * @~english
         * Is called whenever the remove applications button is pressed.
         */
        void on_removeAppBtn_clicked();

        /**
         * @~spanish
         * Se llama cuando, al añadir una nueva aplicación, se termina de editar
         * el texto.
         *
         * @~english
         * Is called when, adding a new application, is finished editing the
         * text.
         */
        void editAppFinished();

};

#endif // GESTURESTAB_H
