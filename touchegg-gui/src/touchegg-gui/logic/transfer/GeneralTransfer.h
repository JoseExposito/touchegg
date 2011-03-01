/**
 * @file /src/touchegg-gui/logic/transfer/GeneralTransfer.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GeneralTransfer
 * @author José Expósito
 */
#ifndef GENERALTRANSFER_H
#define GENERALTRANSFER_H

#include "src/touchegg-gui/util/Include.h"

/**
 * @~spanish
 * Clase para transferir los datos generales de la configuración.
 *
 * @~english
 * Class to transfer general settings.
 */
class GeneralTransfer {

    private:

        /**
         * @~spanish
         * Nombre del campo en el que leer/escribir la configuración general.
         *
         * @~english
         * Field name to read/write general config.
         */
        QString field;

        /**
         * @~spanish
         * Valor del campo.
         *
         * @~english
         * Value of the field.
         */
        QString value;

    public:

        /**
         * @~spanish
         * Contructor.
         * @param field Campo en el que leer/escribir.
         * @param value Valor del campo.
         *
         * @~english
         * Constructor.
         * @param field Field to read/write.
         * @param value Value of the field.
         */
        GeneralTransfer(const QString& field, const QString& value = "");

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuleve el nombre del campo en el que leer/escribir.
         * @return El nombre del campo.
         *
         * @~english
         * Returns the field name to read/write.
         * @return The field name.
         */
        const QString& getField() const;

        /**
         * @~spanish
         * Devuleve el valor del campo en el que leer/escribir.
         * @return El valor del campo.
         *
         * @~english
         * Returns the field value to read/write.
         * @return The field value.
         */
        const QString& getValue() const;

        /**
         * @~spanish
         * Establece el nombre del campo en el que leer/escribir.
         * @param field El nombre.
         *
         * @~english
         * Sets the name of the field to read/write.
         * @param field The name.
         */
        void setField(const QString& field);

        /**
         * @~spanish
         * Establece el valor del campo en el que leer/escribir.
         * @param value El valor.
         *
         * @~english
         * Sets the value of the field to read/write.
         * @param value The value.
         */
        void setValue(const QString& value);

};

#endif // GENERALTRANSFER_H
