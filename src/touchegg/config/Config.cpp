/**
 * @file /src/touchegg/config/Config.cpp
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 2 of the License,  or (at your option)  any later
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
#include "Config.h"

// ****************************************************************************************************************** //
// **********                                      ANONYMOUS NAMESPACE                                     ********** //
// ****************************************************************************************************************** //

namespace
{
    const char *USR_SHARE_CONFIG_FILE = "/usr/share/touchegg/touchegg.conf";
    const char *HOME_CONFIG_FILE      = "/.config/touchegg/touchegg.conf";
    const char *HOME_CONFIG_DIR       = ".config/touchegg";
}


// ****************************************************************************************************************** //
// **********                                 STATIC METHODS AND VARIABLES                                 ********** //
// ****************************************************************************************************************** //

Config *Config::instance = NULL;

Config *Config::getInstance()
{
    if (Config::instance == NULL)
        Config::instance = new Config();

    return Config::instance;
}

void Config::loadConfig()
{
    if (instance != NULL) {
        delete instance;
        instance = NULL;
    }
    Config::getInstance();
}


// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

Config::Config()
{
    this->composedGesturesTime = 0;
    QFile homeFile(QDir::homePath() + HOME_CONFIG_FILE);
    QFile usrFile(USR_SHARE_CONFIG_FILE);

    // If the /usr/share/touchegg configuration file is not found then exit
    if (!usrFile.exists()) {
        qFatal("%s not found, reinstall application can solve the problem\n", USR_SHARE_CONFIG_FILE);
    }

    // If the ~/.config/touchegg configuration file doesn't exist copy it
    if (!homeFile.exists()) {
        qDebug() << QDir::homePath() + HOME_CONFIG_FILE << " not found, copying config from " << USR_SHARE_CONFIG_FILE;
        QDir::home().mkdir(HOME_CONFIG_DIR);
        usrFile.copy(QDir::homePath() + HOME_CONFIG_FILE);
    }

    // Load the configuration into the QHash
    qDebug() << "Reading config from " << QDir::homePath() + HOME_CONFIG_FILE;
    this->initConfig(homeFile);
}

// ****************************************************************************************************************** //
// **********                                        PRIVATE METHODS                                       ********** //
// ****************************************************************************************************************** //

void Config::initConfig(QFile &file)
{
    // Loads the XML file
    QDomDocument document;
    if (!file.open(QIODevice::ReadOnly))
        qFatal("Can't open configuration file for read");
    if (!document.setContent(&file)) {
        file.close();
        qFatal("Error reading configuration, please, review the format");
    }
    file.close();

    /*
     * A very simple example of a configuration file:
     * <touchégg>
     *
     *     <settings>
     *         <property name="composed_gestures_time">140</property>
     *     </settings>
     *
     *     <application name="All">
     *
     *         <gesture type="tap" fingers="5" direction="">
     *             <action type="CLOSE_WINDOW"></action>
     *         </gesture>
     *
     *     </application>
     *
     *     <application name="Okular">
     *
     *         <gesture type="pinch" fingers="2" direction"in">
     *             <action type="SEND_KEYS">
     *                 HOLD_DOWN=Control_L:PRESS=KP_Add
     *             </action>
     *         </gesture>
     *
     *         <gesture type="pinch" fingers="2" direction"out">
     *             <action type="SEND_KEYS">
     *                 HOLD_DOWN=Control_L:PRESS=KP_Subtract
     *             </action>
     *         </gesture>
     *
     *     </application>
     *
     *     <application name="windowname.Leela090.exe">
     *
     *         <gesture type="TAP" fingers="3" direction="">
     *             <action type="SEND_KEYS">Alt+P</action>
     *         </gesture>
     *
     *         <gesture type="DRAG" fingers="3" direction="UP">
     *             <action type="SEND_KEYS">Control+R</action>
     *         </gesture>
     *
     *         <gesture type="DRAG" fingers="3" direction="DOWN">
     *             <action type="SEND_KEYS">Alt+R</action>
     *         </gesture>
     *
     *     </application>
     *
     * </touchégg>
     */

    for (QDomNode appNode=document.documentElement().firstChild(); !appNode.isNull(); appNode=appNode.nextSibling()) {
        QDomElement appElem = appNode.toElement();
        if (appElem.isNull())
            continue;

        // Load general Touchégg settings
        if (appElem.tagName() == "settings") {

            for (QDomNode propNode = appNode.firstChild(); !propNode.isNull(); propNode = propNode.nextSibling()) {
                if (!propNode.toElement().isNull()
                        && propNode.toElement().attribute("name") == "composed_gestures_time") {
                    this->composedGesturesTime = propNode.toElement().text().toInt();
                }
            }

        } else {
            // Load applications/gestures settings
            for (QDomNode gestureNode = appNode.firstChild(); !gestureNode.isNull();
                    gestureNode = gestureNode.nextSibling()) {
                QDomElement gestureElem = gestureNode.toElement();
                if (gestureElem.isNull())
                    continue;

                // For common configuration applications
                QStringList apps = appElem.attribute("name").split(",");
                QStringList keys;

                for (int n = 0; n < apps.length(); n++) {
                    QString appName = apps.at(n).trimmed();
                    QString key = appName + "."
                            + gestureElem.attribute("type") + "."
                            + gestureElem.attribute("fingers") + "."
                            + gestureElem.attribute("direction");
                    if (key.right(1) == ".")   // For the tap gestures,
                        key += "NO_DIRECTION"; // without direction
                    keys.append(key);
                }

                // Get the action
                QString action, timing;
                for (QDomNode actNode = gestureNode.firstChild(); !actNode.isNull(); actNode = actNode.nextSibling()) {
                    if (!actNode.toElement().isNull()) {
                        action = actNode.toElement().attribute("type");
                        timing = actNode.toElement().attribute("when");
                        // By default, perform the action at the end. 
                        if (timing != "AT_START" && timing != "AT_END") {
                            timing = "AT_END";
                        }
                    }
                }                

                // Get the settings
                QString settings;
                for (QDomNode settNode=gestureNode.firstChild(); !settNode.isNull(); settNode=settNode.nextSibling()) {
                    if (!settNode.toElement().isNull())
                        settings = settNode.toElement().text();
                }

                // Save the actions and the settings into the settings QHash
                for (int n = 0; n < keys.length(); n++) {
                    this->settings.insert(keys.at(n) + ".action", action);
                    this->settings.insert(keys.at(n) + ".settings", settings);
                    this->settings.insert(keys.at(n) + ".timing", timing);
                }

                //--------------------------------------------------------------

                // If is an used gesture add it to the usedGestures QHash
                if (action != "" && action != "NO_ACTION") {
                    for (int n = 0; n < apps.length(); n++) {
                        QString app = apps.at(n).trimmed();
                        QString gesture = gestureElem.attribute("type");
                        int fingers = gestureElem.attribute("fingers").toInt();

                        this->saveUsedGestures(app, gesture, fingers);
                    }
                }
            }

        }
    }
}

void Config::saveUsedGestures(const QString &app, const QString &gestureType, int numFingers)
{

    if (this->usedGestures.contains(app)) {
        QList< QPair<QStringList, int> > aux = this->usedGestures.value(app);
        QStringList gestures = GestureTypeEnum::getGeisEquivalent(GestureTypeEnum::getEnum(gestureType));

        QPair<QStringList, int> pair;
        pair.first = gestures;
        pair.second = numFingers;

        aux.append(pair);
        this->usedGestures.insert(app, aux);

    } else {
        QList< QPair<QStringList, int> > aux;
        QStringList gestures = GestureTypeEnum::getGeisEquivalent(GestureTypeEnum::getEnum(gestureType));

        QPair<QStringList, int> pair;
        pair.first = gestures;
        pair.second = numFingers;

        aux.append(pair);
        this->usedGestures.insert(app, aux);
    }
}


// ****************************************************************************************************************** //
// **********                                          GET/SET/IS                                          ********** //
// ****************************************************************************************************************** //

QList< QPair<QStringList, int> >  Config::getUsedGestures(
    const QString &application) const
{
    QList< QPair<QStringList, int> > r = this->usedGestures.value(application);
    return r;
}

//------------------------------------------------------------------------------

int Config::getComposedGesturesTime() const
{
    return this->composedGesturesTime;
}

//------------------------------------------------------------------------------

ActionTypeEnum::ActionType Config::getAssociatedAction(const QString &appName, const QString &appClass,
        GestureTypeEnum::GestureType gestureType, int numFingers,
        GestureDirectionEnum::GestureDirection dir) const
{
    return ActionTypeEnum::getEnum(getAssociation(
        appName, appClass, gestureType, numFingers, dir,
        "action", ActionTypeEnum::getValue(ActionTypeEnum::NO_ACTION)));
}

QString Config::getAssociatedSettings(const QString &appName, const QString &appClass,
        GestureTypeEnum::GestureType gestureType, int numFingers,
        GestureDirectionEnum::GestureDirection dir) const
{
    return getAssociation(appName, appClass, gestureType, numFingers, dir, "settings", "");
}

QString Config::getAssociatedTiming(const QString &appName, const QString &appClass,
        GestureTypeEnum::GestureType gestureType, int numFingers,
        GestureDirectionEnum::GestureDirection dir) const
{
    return getAssociation(appName, appClass, gestureType, numFingers, dir, "timing", "AT_END");
}

QString Config::getAssociation(const QString &appName, const QString &appClass,
        GestureTypeEnum::GestureType gestureType, int numFingers,
        GestureDirectionEnum::GestureDirection dir,
        QString settingType, QString defaultValue) const
{
    QString exactNameKey = "windowname." + appName + "."
            + GestureTypeEnum::getValue(gestureType) + "."
            + QString::number(numFingers) + "."
            + GestureDirectionEnum::getValue(dir) + "." + settingType;
    QString allDirectionsNameKey = "windowname." + appName + "."
            + GestureTypeEnum::getValue(gestureType) + "."
            + QString::number(numFingers) + ".ALL." + settingType;
    QString exactKey = appClass + "."
            + GestureTypeEnum::getValue(gestureType) + "."
            + QString::number(numFingers) + "."
            + GestureDirectionEnum::getValue(dir) + "." + settingType;
    QString allDirectionsKey = appClass + "."
            + GestureTypeEnum::getValue(gestureType) + "."
            + QString::number(numFingers) + ".ALL." + settingType;
    QString globalExactKey = "All."
            + GestureTypeEnum::getValue(gestureType) + "."
            + QString::number(numFingers) + "."
            + GestureDirectionEnum::getValue(dir) + "." + settingType;
    QString globalAllDirectionsKey = "All."
            + GestureTypeEnum::getValue(gestureType) + "."
            + QString::number(numFingers) + ".ALL." + settingType;

    if (this->settings.contains(exactNameKey))
        return this->settings.value(exactNameKey);
    else if (this->settings.contains(allDirectionsNameKey))
        return this->settings.value(allDirectionsNameKey);
    else if (this->settings.contains(exactKey))
        return this->settings.value(exactKey);
    else if (this->settings.contains(allDirectionsKey))
        return this->settings.value(allDirectionsKey);
    else if (this->settings.contains(globalExactKey))
        return this->settings.value(globalExactKey);
    else if (this->settings.contains(globalAllDirectionsKey))
        return this->settings.value(globalAllDirectionsKey);
    else
        return defaultValue;
}
