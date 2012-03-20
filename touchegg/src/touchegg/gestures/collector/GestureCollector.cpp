/**
 * @file /src/touchegg/gestures/collector/GestureCollector.cpp
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
 * @class  GestureCollector
 */
#include "GestureCollector.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

void GestureCollector::gestureStart(GestureCollector *gc, GeisEvent event)
{
    // "type" es GEIS_GESTURE_TYPE_TAP1, GEIS_GESTURE_TYPE_PINCH3...
    QHash<QString, QVariant> attrs = getGestureAttrs(event);
    QString type = attrs.value(
            GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME).toString();
    int id = attrs.value("geis gesture class id").toInt();
    emit gc->executeGestureStart(type, id, attrs);
}

void GestureCollector::gestureUpdate(GestureCollector *gc, GeisEvent event)
{
    QHash<QString, QVariant> attrs = getGestureAttrs(event);
    QString type = attrs.value(
            GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME).toString();
    int id = attrs.value("geis gesture class id").toInt();
    emit gc->executeGestureUpdate(type, id, attrs);
}

void GestureCollector::gestureFinish(GestureCollector *gc, GeisEvent event)
{
    QHash<QString, QVariant> attrs = getGestureAttrs(event);
    QString type = attrs.value(
            GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME).toString();
    int id = attrs.value("geis gesture class id").toInt();
    emit gc->executeGestureFinish(type, id, attrs);
}


// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

GestureCollector::GestureCollector(QObject *parent)
    : QObject(parent)
{
    /* La instancia de GEIS es única, por lo que se puede tener un único bucle
     * para recoger los gestos en run(). Con GEIS v2.0 se pueden añadir
     * subcripciones a dicha instancia para escuchar en diferentes ventanas.
     */
    this->geis = geis_new(GEIS_INIT_TRACK_DEVICES, NULL);

    if (!this->geis)
        qFatal("Failed to initialize geis instance");

    // Inicilizamos el socket que recibirá los eventos de uTouch
    int fd;
    geis_get_configuration(this->geis, GEIS_CONFIGURATION_FD, &fd);
    this->socketNotifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);
    connect(this->socketNotifier, SIGNAL(activated(int)), SLOT(geisEvent()));
}

GestureCollector::~GestureCollector()
{
    geis_delete(this->geis);
}


// ************************************************************************** //
// **********                     PUBLIC SLOTS                     ********** //
// ************************************************************************** //

void GestureCollector::addWindow(Window w)
{
    // Si no hay que escuchar por ningún gesto en la ventana indicada salimos
    Config *cfg = Config::getInstance();

    QList< QPair<QStringList, int> > subscribeList;
    if (w == QX11Info::appRootWindow())
        subscribeList = cfg->getUsedGestures("All");
    else
        subscribeList = cfg->getUsedGestures(this->getWindowClass(w));

    if (subscribeList.length() == 0)
        return;

    // Nos suscribimos solo a los gestos que nos interesan
    for (int n = 0; n < subscribeList.length(); n++) {
        QPair<QStringList, int> aux = subscribeList.at(n);
        int numFingers = aux.second;

        foreach(QString gesture, aux.first) {
            // Creamos el filtro
            GeisFilter filter = geis_filter_new(this->geis, "filter");

            geis_filter_add_term(filter,
                    GEIS_FILTER_CLASS,
                    GEIS_GESTURE_ATTRIBUTE_TOUCHES, GEIS_FILTER_OP_EQ,
                    numFingers,
                    GEIS_CLASS_ATTRIBUTE_NAME, GEIS_FILTER_OP_EQ,
                    gesture.toStdString().c_str(),
                    NULL);

            // Escuchamos en la ventana indicada
            geis_filter_add_term(filter, GEIS_FILTER_REGION,
                    GEIS_REGION_ATTRIBUTE_WINDOWID, GEIS_FILTER_OP_EQ, w, NULL);

            // Creamos la subcripción, le añadimos el filtro y la activamos
            GeisSubscription subscription = geis_subscription_new(
                    this->geis, "subscription", GEIS_SUBSCRIPTION_CONT);
            geis_subscription_add_filter(subscription, filter);
            geis_subscription_activate(subscription);

            // Guardamos la subcrición y el filtro para borrarlos cuando se
            // destruya la ventana asociada
            if (this->subscriptions.contains(w)) {
                QList<GeisSubscription> aux = this->subscriptions.value(w);
                aux.append(subscription);
                this->subscriptions.insert(w, aux);
            } else {
                QList<GeisSubscription> aux;
                aux.append(subscription);
                this->subscriptions.insert(w, aux);
            }

            if (this->filters.contains(w)) {
                QList<GeisFilter> aux = this->filters.value(w);
                aux.append(filter);
                this->filters.insert(w, aux);
            } else {
                QList<GeisFilter> aux;
                aux.append(filter);
                this->filters.insert(w, aux);
            }
        }
    }
}

void GestureCollector::removeWindow(Window w)
{
    QList<GeisSubscription> subs = this->subscriptions.value(w);
    foreach (GeisSubscription s, subs) {
        geis_subscription_delete(s);
    }
    this->subscriptions.remove(w);

    QList<GeisFilter> fils = this->filters.value(w);
    foreach (GeisFilter f, fils) {
        geis_filter_delete(f);
    }
    this->filters.remove(w);
}


// ************************************************************************** //
// **********                    PRIVATE SLOTS                     ********** //
// ************************************************************************** //

void GestureCollector::geisEvent()
{
    GeisStatus status;

    status = geis_dispatch_events(this->geis);
    if (status != GEIS_STATUS_SUCCESS) {
        qWarning("Failed to dispatch geis events");
        return;
    }

    GeisEvent event;
    for (status = geis_next_event(this->geis, &event);
            status == GEIS_STATUS_SUCCESS || status == GEIS_STATUS_CONTINUE;
            status = geis_next_event(this->geis, &event)) {
        switch (geis_event_type(event)) {
        case GEIS_EVENT_GESTURE_BEGIN:
            GestureCollector::gestureStart(this, event);
            break;
        case GEIS_EVENT_GESTURE_UPDATE:
            GestureCollector::gestureUpdate(this, event);
            break;
        case GEIS_EVENT_GESTURE_END:
            GestureCollector::gestureFinish(this, event);
            break;
        case GEIS_EVENT_INIT_COMPLETE:
            emit this->ready();
            break;

        default:
            break;
        }

        geis_event_delete(event);
    }
}


// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

QHash<QString, QVariant> GestureCollector::getGestureAttrs(GeisEvent event)
{
    QHash<QString, QVariant> ret;

    GeisAttr attr = geis_event_attr_by_name(event,
            GEIS_EVENT_ATTRIBUTE_GROUPSET);
    GeisGroupSet groupset = (GeisGroupSet)geis_attr_value_to_pointer(attr);

    for (GeisSize i = 0; i < geis_groupset_group_count(groupset); ++i) {
        GeisSize j;
        GeisGroup group = geis_groupset_group(groupset, i);

        for (j = 0; j < geis_group_frame_count(group); ++j) {
            GeisSize k;
            GeisFrame frame = geis_group_frame(group, j);
            GeisSize attr_count = geis_frame_attr_count(frame);

            for (k = 0; k < attr_count; ++k) {
                GeisAttr gestureAttr = geis_frame_attr(frame, k);
                QString attrName = geis_attr_name(gestureAttr);
                QVariant value;

                switch (geis_attr_type(gestureAttr)) {
                case GEIS_ATTR_TYPE_BOOLEAN:
                    value = geis_attr_value_to_boolean(gestureAttr);
                    break;
                case GEIS_ATTR_TYPE_FLOAT:
                    value = geis_attr_value_to_float(gestureAttr);
                    break;
                case GEIS_ATTR_TYPE_INTEGER:
                    value = geis_attr_value_to_integer(gestureAttr);
                    break;
                case GEIS_ATTR_TYPE_STRING:
                    value = geis_attr_value_to_string(gestureAttr);
                    break;
                default:
                    break;
                }

                if (!value.isNull()) {
                    ret.insert(attrName, value);
                }
            }
        }
    }

    return ret;
}

QString GestureCollector::getWindowClass(Window window) const
{
    XClassHint *classHint = XAllocClassHint();
    XGetClassHint(QX11Info::display(), window, classHint);
    QString ret = classHint->res_class;
    XFree(classHint->res_class);
    XFree(classHint->res_name);
    return ret;
}
