/****************************************************************************
** Meta object code from reading C++ file 'GestureDirectionEnum.h'
**
** Created: Thu Sep 22 18:27:45 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/touchegg/gestures/types/GestureDirectionEnum.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GestureDirectionEnum.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GestureDirectionEnum[] = {

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
      21, 0x0,    8,   18,

 // enum data: key, value
      38, uint(GestureDirectionEnum::NO_DIRECTION),
      51, uint(GestureDirectionEnum::ALL),
      55, uint(GestureDirectionEnum::UP),
      58, uint(GestureDirectionEnum::DOWN),
      63, uint(GestureDirectionEnum::LEFT),
      68, uint(GestureDirectionEnum::RIGHT),
      74, uint(GestureDirectionEnum::IN),
      77, uint(GestureDirectionEnum::OUT),

       0        // eod
};

static const char qt_meta_stringdata_GestureDirectionEnum[] = {
    "GestureDirectionEnum\0GestureDirection\0"
    "NO_DIRECTION\0ALL\0UP\0DOWN\0LEFT\0RIGHT\0"
    "IN\0OUT\0"
};

const QMetaObject GestureDirectionEnum::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GestureDirectionEnum,
      qt_meta_data_GestureDirectionEnum, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GestureDirectionEnum::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GestureDirectionEnum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GestureDirectionEnum::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GestureDirectionEnum))
        return static_cast<void*>(const_cast< GestureDirectionEnum*>(this));
    return QObject::qt_metacast(_clname);
}

int GestureDirectionEnum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
