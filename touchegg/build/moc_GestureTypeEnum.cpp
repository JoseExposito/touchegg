/****************************************************************************
** Meta object code from reading C++ file 'GestureTypeEnum.h'
**
** Created: Thu Sep 22 18:27:43 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/touchegg/gestures/types/GestureTypeEnum.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GestureTypeEnum.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GestureTypeEnum[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
      16, 0x0,    6,   18,

 // enum data: key, value
      28, uint(GestureTypeEnum::TAP),
      32, uint(GestureTypeEnum::DRAG),
      37, uint(GestureTypeEnum::PINCH),
      43, uint(GestureTypeEnum::ROTATE),
      50, uint(GestureTypeEnum::TAP_AND_HOLD),
      63, uint(GestureTypeEnum::DOUBLE_TAP),

       0        // eod
};

static const char qt_meta_stringdata_GestureTypeEnum[] = {
    "GestureTypeEnum\0GestureType\0TAP\0DRAG\0"
    "PINCH\0ROTATE\0TAP_AND_HOLD\0DOUBLE_TAP\0"
};

const QMetaObject GestureTypeEnum::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GestureTypeEnum,
      qt_meta_data_GestureTypeEnum, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GestureTypeEnum::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GestureTypeEnum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GestureTypeEnum::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GestureTypeEnum))
        return static_cast<void*>(const_cast< GestureTypeEnum*>(this));
    return QObject::qt_metacast(_clname);
}

int GestureTypeEnum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
