/**
 * @file /src/touchegg-gui/data/transaction_manager/TransactionManager.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Touchégg-GUI, usted puede redistribuirlo
 * y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Touchégg-GUI project, you can redistribute it and/or
 * modify it under the terms of the GNU GPL v3.
 *
 * @class  TransactionManager
 * @author José Expósito
 */
#include "TransactionManager.h"
#include "src/touchegg-gui/data/transaction_manager/TransactionManagerImp.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

TransactionManager* TransactionManager::instance = NULL;

TransactionManager* TransactionManager::getInstance() {
    if(TransactionManager::instance == NULL)
        TransactionManager::instance = new TransactionManagerImp;

    return TransactionManager::instance;
}
