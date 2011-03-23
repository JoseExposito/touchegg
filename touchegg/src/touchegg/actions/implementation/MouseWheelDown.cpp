/**
 * @file /src/touchegg/actions/implementation/MouseWheelDown.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  MouseWheelDown
 * @author José Expósito
 */
#include "MouseWheelDown.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MouseWheelDown::MouseWheelDown(const QString& settings) : Action(settings) {
    /*this->speedCount = 0;
    this->speed      = 4;

    QStringList strl = settings.split("=");
    if(strl.length() == 2 && strl.at(0) == "SPEED") {
        bool ok;
        int configSpeed = QString(strl.at(1)).toInt(&ok);
        if(ok && configSpeed >= 1 && configSpeed <= 10)
            this->speed = 11 - configSpeed;
        else
            qWarning() << "Error reading MOUSE_WHELL_DOWN settings, using " <<
                    "the default settings";
    } else
        qWarning() << "Error reading MOUSE_WHELL_DOWN settings, using " <<
                "the default settings";*/
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void MouseWheelDown::executeStart(const QHash<QString, QVariant>& /*attrs*/) {
    this->SCROLL_SPACE  = 25;  // "Velocidad" -> Entre 10 (muy rápido) y 40 (muy lento)

    // A mayor velocidad, hay que poner mayor deceleración, por que si no se descontrola
    this->acel          = -0.3;

    this->acumSpace    = 0;
}

void MouseWheelDown::executeUpdate(const QHash<QString, QVariant>& attrs) {
    float deltaY = attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat();
    this->acumSpace += deltaY;

    while(this->acumSpace >= this->SCROLL_SPACE) {
        this->acumSpace -= this->SCROLL_SPACE;

        XTestFakeButtonEvent(QX11Info::display(), Button5, true, 0);
        XTestFakeButtonEvent(QX11Info::display(), Button5, false, 0);
        XFlush(QX11Info::display());
    }
}

void MouseWheelDown::executeFinish(const QHash<QString, QVariant>& attrs) {    
    // Vemos el tiempo que tardará el scroll en pararse:
    // Vf = Vi + a·t => 0 = Vi + a·t => t = -Vi/a
    float velocityY = attrs.value(GEIS_GESTURE_ATTRIBUTE_VELOCITY_Y).toFloat();
    velocityY *= 1;

    //float t = ((-1)*velocityY) / this->acel;
    int t = ((-1)*velocityY) / this->acel;

    // Vemos la distancia que recorrerá hasta pararse:
    // Ef = Vi·t + (a·t**) / 2
    //float Ef = (velocityY*t) + (this->acel * t * t) / 2;
    int Ef = (velocityY*t) + (this->acel * t * t) / 2;

    // Hacemos el scroll enlos momentos en los que correspondería hacerlo, el
    // resto del tiempo dormimos
    int numScrolls = (int) Ef / this->SCROLL_SPACE;


    qDebug() << "Tiempo total " << t;
    qDebug() << "Espacio toal a recorrer " << Ef;
    qDebug() << "Numero de scrolls " << numScrolls;


    float vi = velocityY;
    while(numScrolls > 0) {
        // Hay que resolver unas ecuacioncillas y tal...
        float vScroll = sqrt(2*this->acel*this->SCROLL_SPACE);
        float tScroll = (vScroll - vi) / this->acel;

        qDebug() << tScroll * 1000000;
        usleep(tScroll);

        vi = vScroll;
        numScrolls--;

        XTestFakeButtonEvent(QX11Info::display(), Button5, true, 0);
        XTestFakeButtonEvent(QX11Info::display(), Button5, false, 0);
        XFlush(QX11Info::display());
    }
}
