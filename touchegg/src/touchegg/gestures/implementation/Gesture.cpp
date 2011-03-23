/**
 * @file /src/touchegg/gestures/implementations/Gesture.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg, usted puede redistribuirlo y/o
 * modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  Gesture
 * @author José Expósito
 */
#include "Gesture.h"


// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

Gesture::Gesture(GestureTypeEnum::GestureType type, GeisGestureId id,
        const QHash<QString, QVariant>& attrs) {
    this->type   = type;
    this->id     = id;
    this->attrs  = attrs;
}

Gesture::~Gesture() {
    if(this->action != NULL)
        delete this->action;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void Gesture::start() const {
    if(this->action != NULL)
        this->action->executeStart(this->attrs);
}

void Gesture::update() const {
    if(this->action != NULL)
        this->action->executeUpdate(this->attrs);
}

void Gesture::finish() const  {
    if(this->action != NULL)
        this->action->executeFinish(this->attrs);
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

GestureTypeEnum::GestureType Gesture::getType() const {
    return this->type;
}

GeisGestureId Gesture::getId() const {
    return this->id;
}

const QHash<QString, QVariant>& Gesture::getAttrs() const {
    return this->attrs;
}

const Action* Gesture::getAction() const {
    return this->action;
}

void Gesture::setType(GestureTypeEnum::GestureType type) {
    this->type = type;
}

void Gesture::setId(GeisGestureId id) {
    this->id = id;
}

void Gesture::setAttrs(const QHash<QString, QVariant>& attrs) {
    this->attrs = attrs;
}

void Gesture::setAction(Action* action) {
    this->action = action;
}
