/****************************************************************************
** Meta object code from reading C++ file 'ActionTypeEnum.h'
**
** Created: Wed Mar 2 21:57:39 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/touchegg/actions/types/ActionTypeEnum.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ActionTypeEnum.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ActionTypeEnum[] = {

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
      15, 0x0,   16,   18,

 // enum data: key, value
      26, uint(ActionTypeEnum::MOUSE_MOVE),
      37, uint(ActionTypeEnum::RIGHT_BUTTON_CLICK),
      56, uint(ActionTypeEnum::MIDDLE_BUTTON_CLICK),
      76, uint(ActionTypeEnum::MOUSE_WHEEL_UP),
      91, uint(ActionTypeEnum::MOUSE_WHEEL_DOWN),
     108, uint(ActionTypeEnum::MINIMIZE_WINDOW),
     124, uint(ActionTypeEnum::MAXIMIZE_RESTORE_WINDOW),
     148, uint(ActionTypeEnum::CLOSE_WINDOW),
     161, uint(ActionTypeEnum::RESIZE_WINDOW),
     175, uint(ActionTypeEnum::SHOW_DESKTOP),
     188, uint(ActionTypeEnum::CHANGE_DESKTOP),
     203, uint(ActionTypeEnum::SEND_KEYS),
     213, uint(ActionTypeEnum::MOVE_WINDOW),
     225, uint(ActionTypeEnum::RUN_COMMAND),
     237, uint(ActionTypeEnum::DRAG_AND_DROP),
     251, uint(ActionTypeEnum::LEFT_BUTTON_CLICK),

       0        // eod
};

static const char qt_meta_stringdata_ActionTypeEnum[] = {
    "ActionTypeEnum\0ActionType\0MOUSE_MOVE\0"
    "RIGHT_BUTTON_CLICK\0MIDDLE_BUTTON_CLICK\0"
    "MOUSE_WHEEL_UP\0MOUSE_WHEEL_DOWN\0"
    "MINIMIZE_WINDOW\0MAXIMIZE_RESTORE_WINDOW\0"
    "CLOSE_WINDOW\0RESIZE_WINDOW\0SHOW_DESKTOP\0"
    "CHANGE_DESKTOP\0SEND_KEYS\0MOVE_WINDOW\0"
    "RUN_COMMAND\0DRAG_AND_DROP\0LEFT_BUTTON_CLICK\0"
};

const QMetaObject ActionTypeEnum::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ActionTypeEnum,
      qt_meta_data_ActionTypeEnum, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ActionTypeEnum::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ActionTypeEnum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ActionTypeEnum::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ActionTypeEnum))
        return static_cast<void*>(const_cast< ActionTypeEnum*>(this));
    return QObject::qt_metacast(_clname);
}

int ActionTypeEnum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
