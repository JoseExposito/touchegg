/**
 * @file /src/touchegg-gui/presentation/widgets/GestureConfigWidget.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureConfigWidget
 * @author José Expósito
 */
#ifndef GESTURECONFIGWIDGET_H
#define GESTURECONFIGWIDGET_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/presentation/config_forms/ConfigFormFactory.h"
#include "src/touchegg-gui/presentation/config_forms/ConfigForm.h"
#include "src/touchegg-gui/logic/facade/Facade.h"
namespace Ui { class GestureConfigWidget; }


/**
 * @~spanish
 * Widget para configurar las acciones asociadas a un gesto.
 *
 * @~english
 * Widget to configure the actions associated to a gesture.
 */
class GestureConfigWidget : public QFrame {

    Q_OBJECT

    private:

        Ui::GestureConfigWidget *ui;

        /**
         * @~spanish
         * Aplicación sobre la que se configuran los gestos.
         *
         * @~english
         * Application over configure the gestures.
         */
        QString app;

        /**
         * @~spanish
         * Formulario de configuración de la acción, si la acción no es
         * configurable valdrá NULL.
         *
         * @~english
         * Form to configure the action, if the action isn't configurable it
         * will be NULL.
         */
        ConfigForm* configForm;

        /**
         * @~spanish
         * Gesto que se está configurando.
         *
         * @~english
         * Gesture that is configuring.
         */
        QString gesture;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Carga en el combo-box todos los gestos disponibles.
         *
         * @~english
         * Loads in the combo-box all available gestures.
         */
        void loadAllGestures();

        /**
         * @~spanish
         * Carga en el combo-box todas las acciones disponibles.
         *
         * @~english
         * Loads in the combo-box all available actions.
         */
        void loadAllActions();

    public:

        /**
         * @~spanish
         * Constructor.
         * @param app      Aplicación sobre la que se configuran los gestos.
         * @param gesture  Gesto a cargar por defecto.
         * @param action   Acción a cargar por defecto.
         * @param settings Configuración por defecto.
         * @param parent   Padre del widget.
         *
         * @~english
         * Constructor.
         * @param app      Application over configure the gestures.
         * @param gesture  Gesture to load by default.
         * @param action   Action to load by default.
         * @param settings Settings by default.
         * @param parent   Parent of the widget.
         */
        GestureConfigWidget(const QString& app, const QString& gesture = "" ,
                const QString& action = "", const QString& settings = "",
                QWidget* parent = 0);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * Destructor.
         */
        ~GestureConfigWidget();

        /**
         * @~spanish
         * Borra la configuración seleccionada en el widget.
         *
         * @~english
         * Removes the confguration selected in the widget.
         */
        void deleteConfig();

    private slots:

        /**
         * @~spanish
         * Se llama cando se selecciona un gesto en el combo-box.
         * @param index Índice del item seleccionado.
         *
         * @~english
         * Is called whenever a gesture is selected in the combo-box.
         * @param index The index of the selected item.
         */
        void gestureChanged(int index);

        /**
         * @~spanish
         * Se llama cando se seleccioa una acción en el combo-box.
         * @param index Índice del item seleccionado.
         *
         * @~english
         * Is called whenever an action is selected in the combo-box.
         * @param index The index of the selected item.
         */
        void actionChanged(int index);


        /**
         * @~spanish
         * Se llama cada vez que se pulsa el botón que muestra la configuración.
         *
         * @~english
         * It is called whenever the the button to change configuration is
         * pressed.
         */
        void on_configBtn_clicked();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Se llama cada vez que la configuración cambia.
         *
         * @~english
         * It is called whenever the configuration is changed.
         */
        void configChanged() const;

};

#endif // GESTURECONFIGWIDGET_H
