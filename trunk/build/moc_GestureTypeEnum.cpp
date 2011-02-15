/****************************************************************************
** Meta object code from reading C++ file 'GestureTypeEnum.h'
**
** Created: Sun Feb 13 15:16:27 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/touchegg/gestures/types/GestureTypeEnum.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GestureTypeEnum.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
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
      16, 0x0,   21,   18,

 // enum data: key, value
      28, uint(GestureTypeEnum::TWO_FINGERS_TAP),
      44, uint(GestureTypeEnum::THREE_FINGERS_TAP),
      62, uint(GestureTypeEnum::FOUR_FINGERS_TAP),
      79, uint(GestureTypeEnum::FIVE_FINGERS_TAP),
      96, uint(GestureTypeEnum::THREE_FINGERS_PINCH),
     116, uint(GestureTypeEnum::TWO_FINGERS_DRAG_UP),
     136, uint(GestureTypeEnum::TWO_FINGERS_DRAG_DOWN),
     158, uint(GestureTypeEnum::TWO_FINGERS_DRAG_LEFT),
     180, uint(GestureTypeEnum::TWO_FINGERS_DRAG_RIGHT),
     203, uint(GestureTypeEnum::THREE_FINGERS_DRAG_UP),
     225, uint(GestureTypeEnum::THREE_FINGERS_DRAG_DOWN),
     249, uint(GestureTypeEnum::THREE_FINGERS_DRAG_LEFT),
     273, uint(GestureTypeEnum::THREE_FINGERS_DRAG_RIGHT),
     298, uint(GestureTypeEnum::FOUR_FINGERS_DRAG_UP),
     319, uint(GestureTypeEnum::FOUR_FINGERS_DRAG_DOWN),
     342, uint(GestureTypeEnum::FOUR_FINGERS_DRAG_LEFT),
     365, uint(GestureTypeEnum::FOUR_FINGERS_DRAG_RIGHT),
     389, uint(GestureTypeEnum::TWO_FINGERS_TAP_AND_HOLD),
     414, uint(GestureTypeEnum::THREE_FINGERS_TAP_AND_HOLD),
     441, uint(GestureTypeEnum::FOUR_FINGERS_TAP_AND_HOLD),
     467, uint(GestureTypeEnum::FIVE_FINGERS_TAP_AND_HOLD),

       0        // eod
};

static const char qt_meta_stringdata_GestureTypeEnum[] = {
    "GestureTypeEnum\0GestureType\0TWO_FINGERS_TAP\0"
    "THREE_FINGERS_TAP\0FOUR_FINGERS_TAP\0"
    "FIVE_FINGERS_TAP\0THREE_FINGERS_PINCH\0"
    "TWO_FINGERS_DRAG_UP\0TWO_FINGERS_DRAG_DOWN\0"
    "TWO_FINGERS_DRAG_LEFT\0TWO_FINGERS_DRAG_RIGHT\0"
    "THREE_FINGERS_DRAG_UP\0THREE_FINGERS_DRAG_DOWN\0"
    "THREE_FINGERS_DRAG_LEFT\0"
    "THREE_FINGERS_DRAG_RIGHT\0FOUR_FINGERS_DRAG_UP\0"
    "FOUR_FINGERS_DRAG_DOWN\0FOUR_FINGERS_DRAG_LEFT\0"
    "FOUR_FINGERS_DRAG_RIGHT\0"
    "TWO_FINGERS_TAP_AND_HOLD\0"
    "THREE_FINGERS_TAP_AND_HOLD\0"
    "FOUR_FINGERS_TAP_AND_HOLD\0"
    "FIVE_FINGERS_TAP_AND_HOLD\0"
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
