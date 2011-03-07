/****************************************************************************
** Meta object code from reading C++ file 'GestureCollector.h'
**
** Created: Wed Mar 2 21:57:37 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/touchegg/gestures/collector/GestureCollector.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GestureCollector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GestureCollector[] = {

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
      32,   18,   17,   17, 0x05,
     107,   18,   17,   17, 0x05,
     183,   18,   17,   17, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_GestureCollector[] = {
    "GestureCollector\0\0type,id,attrs\0"
    "executeGestureStart(GeisGestureType,GeisGestureId,QHash<QString,QVaria"
    "nt>)\0"
    "executeGestureUpdate(GeisGestureType,GeisGestureId,QHash<QString,QVari"
    "ant>)\0"
    "executeGestureFinish(GeisGestureType,GeisGestureId,QHash<QString,QVari"
    "ant>)\0"
};

const QMetaObject GestureCollector::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_GestureCollector,
      qt_meta_data_GestureCollector, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GestureCollector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GestureCollector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GestureCollector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GestureCollector))
        return static_cast<void*>(const_cast< GestureCollector*>(this));
    return QThread::qt_metacast(_clname);
}

int GestureCollector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void GestureCollector::executeGestureStart(GeisGestureType _t1, GeisGestureId _t2, const QHash<QString,QVariant> & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GestureCollector::executeGestureUpdate(GeisGestureType _t1, GeisGestureId _t2, const QHash<QString,QVariant> & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GestureCollector::executeGestureFinish(GeisGestureType _t1, GeisGestureId _t2, const QHash<QString,QVariant> & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
