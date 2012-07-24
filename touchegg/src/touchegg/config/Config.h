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
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011 - 2012
 * @class  Config
 */
#ifndef CONFIG_H
#define CONFIG_H

#include "src/touchegg/util/Include.h"
#include "src/touchegg/gestures/types/GestureTypeEnum.h"
#include "src/touchegg/gestures/types/GestureDirectionEnum.h"
#include "src/touchegg/actions/types/ActionTypeEnum.h"

/**
 * Singleton that provides access to the configuration.
 */
class Config
{

public:

    /**
     * Only method to get an instance of the class.
     * @return The single instance of the class.
     */
    static Config *getInstance();

    /**
     * (Re)Load configuration.
     */
    static void loadConfig();

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Returns a list with all gestures used by the specified application.
     * If the app haven't got associated gestures returns an empty list.
     * They are saved directly in the format used for GEIS to subscribe to this gestures.
     * @param  application The application.
     * @return The list, composed by the name, in GEIS format, and the number of fingers.
     */
    QList< QPair<QStringList, int> > getUsedGestures(const QString &application) const;

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Returns the time, in milliseconds, which can run a composed gesture.
     * @return The time.
     */
    int getComposedGesturesTime() const;

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Returns the associated action type with a gesture.
     * @param  appClass Application where it is made ​​the gesture.
     * @param  gestureType The gesture that is made.
     * @param  numFingers Number of fingers used by the gesture.
     * @param  dir Direction of the gesture.
     * @return Type of associated action.
     */
    ActionTypeEnum::ActionType getAssociatedAction(const QString &appClass,
            GestureTypeEnum::GestureType gestureType, int numFingers,
            GestureDirectionEnum::GestureDirection dir) const;

    /**
     * Returns the associated config with the indicated gesture.
     * @param  appClass Application where it is made ​​the gesture.
     * @param  gestureType The gesture that is made.
     * @param  numFingers Number of fingers used by the gesture.
     * @param  dir Direction of the gesture.
     * @return The settings.
     */
    QString getAssociatedSettings(const QString &appClass,
            GestureTypeEnum::GestureType gestureType, int numFingers,
            GestureDirectionEnum::GestureDirection dir) const;

private:

    /**
     * Initializes the QHash's for the configuration and used gestures.
     * @param file File from which to read configuration.
     * @see settings
     * @see usedGestures
     */
    void initConfig(QFile &file);

    /**
     * Saves the used gestures in the list.
     * @param app The application.
     * @param gestureType The gesture to save.
     * @param numFingers Number of fingers.
     */
    void saveUsedGestures(const QString &app, const QString &gestureType, int numFingers);

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Time to wait between composed gestures.
     */
    int composedGesturesTime;

    /**
     * QHash with the configuration. The keys are like Application.GestureType.NumFingers.Direction.action/settings and
     * the value is the action or the settings associate to the gesture.
     */
    QHash<QString, QString> settings;

    /**
     * QHash with the gestures used by Touchégg, being the key the application and the value the gestures.
     * The gestures are saved directly in the format used for GEIS to subscribe to this gestures.
     */
    QHash<QString, QList< QPair<QStringList, int> > > usedGestures;

    //------------------------------------------------------------------------------------------------------------------

    /**
     * Single instance of the class.
     */
    static Config *instance;

    // Hide constructors
    Config();
    Config(const Config &);
    const Config &operator = (const Config &);

};

#endif // CONFIG_H
