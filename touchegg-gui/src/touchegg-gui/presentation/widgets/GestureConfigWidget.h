/**
 * @file /src/touchegg-gui/presentation/widgets/GestureConfig.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureConfig
 * @author José Expósito
 */
#ifndef GESTURECONFIG_H
#define GESTURECONFIG_H

#include "src/touchegg-gui/util/Include.h"
#include "src/touchegg-gui/logic/type/GestureTypeEnum.h"
#include "src/touchegg-gui/logic/type/ActionTypeEnum.h"
#include "src/touchegg-gui/presentation/gui_controller/GuiController.h"
#include "src/touchegg-gui/presentation/gui_event/GuiEvent.h"
#include "src/touchegg-gui/logic/transfer/GestureTransfer.h"
#include "src/touchegg-gui/presentation/config_forms/ConfigFormFactory.h"

/**
 * @~spanish
 * Widget con la imagen del geso a configurar, la acción asociada al mismo y
 * un botón para editar las propiedades de la acción.
 *
 * @~english
 * Widget with the gesture image to configure, the associated action and a
 * button to edit the action settings.
 */
class GestureConfigWidget : public QFrame {

    Q_OBJECT

    private:

        /**
         * @~spanish
         * Gesto que configurará el widget.
         *
         * @~english
         * Gesture that set up the widget.
         */
        GestureTypeEnum::GestureType gestureType;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Label con la imagen del gesto a configurar.
         *
         * @~english
         * Label with the image of the gesture to confiure.
         */
        QLabel* gestureLabel;

        /**
         * @~spanish
         * ComboBox con las acciones que se pueden asociar al gesto.
         *
         * @~english
         * ComboBox with the actions that can be associated to the gesture.
         */
        QComboBox* allowedActionsCombo;

        /**
         * @~spanish
         * Botón para configurar la acción elegida.
         *
         * @~english
         * Button to configure the selected action.
         */
        QPushButton* configButton;

        /**
         * @~spanish
         * Formulario para onfigurar la acción.
         *
         * @~english
         * Form to configure the action.
         */
        ConfigForm* configForm;

        /**
         * @~spanish
         * Layout usado.
         *
         * @~english
         * Used layout.
         */
        QGridLayout* layout;

    private slots:

        /**
         * @~spanish
         * Se llama cada vez que la acción seleccionada en el combo box cambia,
         * actualizando la configuración.
         * @param newAction Nueva acción asociada al gesto.
         *
         * @~english
         * It is called whenever the action selected in the combo box changes,
         * updating the configuration.
         * @param newAction New action associated to the gesture.
         */
        void actionChanged(int newAction);

        /**
         * @~spanish
         * Se llama cada vez que se pulsa en el botón para configurar la acción.
         * @param checked Si el botón es apretado o soltado.
         *
         * @~english
         * It is called whenever the configuration button is toggled.
         * @param checked If is pressed or released.
         */
        void showConfigForm(bool checked) const;

        /**
         * @~spanish
         * Se llama cada vez que la configuración cambia.
         *
         * @~english
         * It is called whenever the configuration is changed.
         */
        void configChanged() const;

    public:

        /**
         * @~spanish
         * Constructor.
         * @param gestureType    Tipo del gesto a configurar.
         * @param gestureImage   Ruta de la imagen del gesto.
         * @param allowedActions Acciones que se pueden asociar al gesto.
         *
         * @~english
         * Constructor.
         * @param gestureType    Gesture type to configure.
         * @param gestureImage   Path of the gesture image.
         * @param allowedActions Actions that can be associated to the gesture.
         */
        GestureConfigWidget(GestureTypeEnum::GestureType gestureType,
                const QString& gestureImage, const QStringList& allowedActions);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * Destructor.
         */
        ~GestureConfigWidget();

};

#endif // GESTURECONFIG_H
