/****************************************************************************
** Meta object code from reading C++ file 'GeisLoop.h'
**
** Created: Mon Feb 7 11:25:32 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/touchegg/GeisLoop.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeisLoop.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GeisLoop[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   10,    9,    9, 0x05,
      99,   10,    9,    9, 0x05,
     175,   10,    9,    9, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_GeisLoop[] = {
    "GeisLoop\0\0type,id,attrs\0"
    "executeGestureStart(GeisGestureType,GeisGestureId,QHash<QString,QVaria"
    "nt>)\0"
    "executeGestureUpdate(GeisGestureType,GeisGestureId,QHash<QString,QVari"
    "ant>)\0"
    "executeGestureFinish(GeisGestureType,GeisGestureId,QHash<QString,QVari"
    "ant>)\0"
};

const QMetaObject GeisLoop::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_GeisLoop,
      qt_meta_data_GeisLoop, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GeisLoop::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GeisLoop::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GeisLoop::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GeisLoop))
        return static_cast<void*>(const_cast< GeisLoop*>(this));
    return QThread::qt_metacast(_clname);
}

int GeisLoop::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: executeGestureStart((*reinterpret_cast< GeisGestureType(*)>(_a[1])),(*reinterpret_cast< GeisGestureId(*)>(_a[2])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[3]))); break;
        case 1: executeGestureUpdate((*reinterpret_cast< GeisGestureType(*)>(_a[1])),(*reinterpret_cast< GeisGestureId(*)>(_a[2])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[3]))); break;
        case 2: executeGestureFinish((*reinterpret_cast< GeisGestureType(*)>(_a[1])),(*reinterpret_cast< GeisGestureId(*)>(_a[2])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void GeisLoop::executeGestureStart(GeisGestureType _t1, GeisGestureId _t2, const QHash<QString,QVariant> & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GeisLoop::executeGestureUpdate(GeisGestureType _t1, GeisGestureId _t2, const QHash<QString,QVariant> & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GeisLoop::executeGestureFinish(GeisGestureType _t1, GeisGestureId _t2, const QHash<QString,QVariant> & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
