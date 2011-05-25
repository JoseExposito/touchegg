/**
 * @file /src/touchegg-gui/data/dao/ToucheggDao.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  GestureDao
 * @author Copyright (C) 2011 José Expósito <jose.exposito89@gmail.com>
 */
#ifndef GESTUREDAO_H
#define GESTUREDAO_H

#include "src/touchegg-gui/util/Include.h"


/**
 * @~spanish
 * Data Access Object para acceder a la configuración de Touchégg.
 *
 * @~english
 * Data Access Object to access to the Touchégg configuration.
 */
class ToucheggDao {

    private:

        /**
         * @~spanish
         * Configuración usada.
         *
         * @~english
         * Configuration used.
         */
        QHash<QString, QString>* settings;

    public:

        /**
         * @~spanish
         * Crea un DAO que trabaja con la configuración indicada.
         * @param settings La configuración.
         *
         * @~english
         * Creates a DAO that works with the specified settings.
         * @param settings The settings.
         */
        ToucheggDao(QHash<QString, QString>* settings);

        /**
         * @~spanish
         * Devuelve los datos almacenados en la ruta indicada. Por ejemplo, para
         * leer la acción asociada a un gesto habría que pasar la ruta
         * "TWO_FINGERS_TAP.ALL.action".
         * @param  path Dicha ruta
         * @return Los datos o "" si la ruta no existe.
         *
         * @~english
         * Returns the data stored in the indicated path. For example, to read
         * the action associated to a gesture the path would have to pass
         * "TWO_FINGERS_TAP.ALL.action".
         * @param  path Such path.
         * @return Such data or "" if the path doesn't exist.
         */
        QString read(const QString& path) const;

        /**
         * @~spanish
         * Actualiza los datos almacenados en la ruta indicada. Si la ruta no
         * existía la crea. Si existía los datos se actualizan.
         * @see read
         * @param path  La ruta.
         * @param value Los nuevos datos.
         *
         * @~english
         * It updates the data stored in the indicated path. If the path didn't
         * exists creates. If the path exist updates.
         * @see read
         * @param path  The path.
         * @param value The new data.
         */
        void update(const QString& path, const QString& value);

        /**
         * @~spanish
         * Borra la ruta indicada.
         * @see read
         * @param path  La ruta.
         *
         * @~english
         * Removes the indicated path.
         * @see read
         * @param path  The path.
         */
        void remove(const QString& path);

        /**
         * @~spanish
         * Devuelve una lista con todas las aplicaciones usadas por Touchégg.
         * @return Dicha lista.
         *
         * @~english
         * Returns a list with all applications used by Touchégg.
         * @return Such list.
         */
        QStringList getUsedApplications() const ;

        /**
         * @~spanish
         * Devuelve todos los gestos usados por una aplicación indicada.
         * @param app Dicha aplicación.
         *
         * @~english
         * Returns all gestures used by the specified application.
         * @param app Such application.
         */
        QStringList getUsedGestures(const QString& app) const;

};

#endif // GESTUREDAO_H
