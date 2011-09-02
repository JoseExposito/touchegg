/**
 * @file /src/touchegg/config/Config.h
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 3 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 *
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011
 * @class  Config
 */
#ifndef CONFIG_H
#define CONFIG_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/gestures/types/GestureTypeEnum.h"
#include "src/touchegg/gestures/types/GestureDirectionEnum.h"
#include "src/touchegg/actions/types/ActionTypeEnum.h"

/**
 * @~spanish
 * Singleton que facilita el acceso a la configuración.
 *
 * @~english
 * Singleton that provides access to the configuration.
 */
class Config
{

private:

    /**
     * @~spanish
     * Tiempo a esperar entre los gestos compuestos.
     *
     * @~english
     * Time to wait between composed gestures.
     */
    int composedGesturesTime;

    /**
     * @~spanish
     * QHash con la configuración. Las claves son del tipo
     * Aplicación.TipoGesto.NúmeroDedos.Dirección.action/settings y el valor
     * será la acción o la configuración asociada al gesto.
     *
     * @~english
     * QHash with the configuration. The keys are like
     * Application.GestureType.NumFingers.Direction.action/settings and the
     * value is the action or the settings associate to the gesture.
     */
    QHash<QString, QString> settings;

    /**
     * @~spanish
     * QHash con los gestos utilizados por Touchégg, siendo la clave la
     * aplicación y el valor los gestos.
     * Los gestos se encuentran directamente en el formato utilizado por
     * GEIS para suscribirse a los mismo.
     *
     * @~english
     * QHash with the gestures used by Touchégg, being the key the
     * application and the value the gestures.
     * The gestures are saved directly in the format used for GEIS to
     * subscribe to this gestures.
     */
    QHash<QString, QList< QPair<QStringList, int> > > usedGestures;

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Inicializa los QHash's de configuración y gestos usados.
     * @param file Archivo desde el que leer la configuración.
     * @see settings
     * @see usedGestures
     *
     * @~english
     * Initializes the QHash's for the configuration and used gestures.
     * @param file File from which to read configuration.
     * @see settings
     * @see usedGestures
     */
    void initConfig(QFile& file);

    /**
     * @~spanish
     * Guarda los gestos usados en la lista.
     * @param app Aplicación.
     * @param gestureType Tipo del gesto.
     * @param numFingers Número de dedos.
     *
     * @~english
     * Saves the used gestures in the list.
     * @param app The application.
     * @param gestureType The gesture to save.
     * @param numFingers Number of fingers.
     */
    void saveUsedGestures(const QString &app, const QString &gestureType,
            int numFingers);

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Única instancia de la clase.
     *
     * @~english
     * Single instance of the class.
     */
    static Config* instance;

    // Hide constructors
    Config();
    Config(const Config&);
    const Config& operator = (const Config&);

public:

    /**
     * @~spanish
     * Único método para obtener una instancia de la clase.
     * @return La única instancia de la clase.
     *
     * @~english
     * Only method to get an instance of the class.
     * @return The single instance of the class.
     */
    static Config* getInstance();

    /**
     * @~spanish
     * (Re)Carga la configuración.
     *
     * @~english
     * (Re)Load configuration.
     */
    static void loadConfig();

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Devuelve una lista con todos los gestos utilizados por la aplicación
     * indicada. Si no tiene gestos asociados devuelve una lista vacia.
     * Se encuentran directamente en el formato utilizado por GEIS para
     * suscribirse a los mismo.
     * @param  application La aplicación.
     * @return Dicha lista, compuesta por el nombre en formato GEIS y el número
     *         de dedos.
     *
     * @~english
     * Returns a list with all gestures used by the specified application.
     * If the app haven't got associated gestures returns an empty list.
     * They are saved directly in the format used for GEIS to subscribe to
     * this gestures.
     * @param  The application.
     * @return The list, composed by the name, in GEIS format, and the number of
     *         fingers.
     */
    QList< QPair<QStringList, int> > getUsedGestures(
            const QString& application) const;

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Devuelve el tiempo, en milisegundos, en el que se puede ejecutar un
     * gesto compuesto.
     * @return El tiempo.
     *
     * @~english
     * Returns the time, in milliseconds, which can run a composed gesture.
     * @return The time.
     */
    int getComposedGesturesTime() const;

    //--------------------------------------------------------------------------

    /**
     * @~spanish
     * Devuelve el tipo de acción asociada a el gesto indicado.
     * @param  appClass Aplicación sobre la que se realiza el gesto.
     * @param  gestureType El gesto que se realiza.
     * @param  numFingers Número de dedos usados por el gesto.
     * @param  dir Dirección del gesto.
     * @return Tipo de la acción asociada.
     *
     * @~english
     * Returns the associated action type with a gesture.
     * @param  appClass Application where it is made ​​the gesture.
     * @param  gestureType The gesture that is made.
     * @param  numFingers Number of fingers used by the gesture.
     * @param  dir Direction of the gesture.
     * @return Type of associated action.
     */
    ActionTypeEnum::ActionType getAssociatedAction(const QString& appClass,
        GestureTypeEnum::GestureType gestureType, int numFingers,
        GestureDirectionEnum::GestureDirection dir) const;

    /**
     * @~spanish
     * Devuelve la configuración de la acción asocada a un gesto indicado.
     * @param  appClass Aplicación sobre la que se realiza el gesto.
     * @param  gestureType El gesto que se realiza.
     * @param  numFingers Número de dedos usados por el gesto.
     * @param  dir Dirección del gesto.
     * @return La configuración.
     *
     * @~english
     * Returns the associated config with the indicated gesture.
     * @param  appClass Application where it is made ​​the gesture.
     * @param  gestureType The gesture that is made.
     * @param  numFingers Number of fingers used by the gesture.
     * @param  dir Direction of the gesture.
     * @return The settings.
     */
    QString getAssociatedSettings(const QString& appClass,
        GestureTypeEnum::GestureType gestureType, int numFingers,
        GestureDirectionEnum::GestureDirection dir) const;

};

#endif // CONFIG_H
