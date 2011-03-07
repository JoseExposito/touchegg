/****************************************************************************
** Meta object code from reading C++ file 'GestureHandler.h'
**
** Created: Wed Mar 2 21:57:38 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/touchegg/gestures/handler/GestureHandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GestureHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GestureHandler[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      43,   29,   15,   15, 0x0a,
     118,   29,   15,   15, 0x0a,
     194,   29,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GestureHandler[] = {
    "GestureHandler\0\0executeTap()\0type,id,attrs\0"
    "executeGestureStart(GeisGestureType,GeisGestureId,QHash<QString,QVaria"
    "nt>)\0"
    "executeGestureUpdate(GeisGestureType,GeisGestureId,QHash<QString,QVari"
    "ant>)\0"
    "executeGestureFinish(GeisGestureType,GeisGestureId,QHash<QString,QVari"
    "ant>)\0"
};

const QMetaObject GestureHandler::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_GestureHandler,
      qt_meta_data_GestureHandler, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GestureHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GestureHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GestureHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GestureHandler))
        return static_cast<void*>(const_cast< GestureHandler*>(this));
    return QThread::qt_metacast(_clname);
}

int GestureHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: executeTap(); break;
        case 1: executeGestureStart((*reinterpret_cast< GeisGestureType(*)>(_a[1])),(*reinterpret_cast< GeisGestureId(*)>(_a[2])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[3]))); break;
        case 2: executeGestureUpdate((*reinterpret_cast< GeisGestureType(*)>(_a[1])),(*reinterpret_cast< GeisGestureId(*)>(_a[2])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[3]))); break;
        case 3: executeGestureFinish((*reinterpret_cast< GeisGestureType(*)>(_a[1])),(*reinterpret_cast< GeisGestureId(*)>(_a[2])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
