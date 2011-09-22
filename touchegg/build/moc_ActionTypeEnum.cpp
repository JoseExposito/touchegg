/****************************************************************************
** Meta object code from reading C++ file 'ActionTypeEnum.h'
**
** Created: Thu Sep 22 18:27:46 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/touchegg/actions/types/ActionTypeEnum.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ActionTypeEnum.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
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
      15, 0x0,   14,   18,

 // enum data: key, value
      26, uint(ActionTypeEnum::NO_ACTION),
      36, uint(ActionTypeEnum::MOUSE_CLICK),
      48, uint(ActionTypeEnum::SCROLL),
      55, uint(ActionTypeEnum::MINIMIZE_WINDOW),
      71, uint(ActionTypeEnum::MAXIMIZE_RESTORE_WINDOW),
      95, uint(ActionTypeEnum::CLOSE_WINDOW),
     108, uint(ActionTypeEnum::RESIZE_WINDOW),
     122, uint(ActionTypeEnum::SHOW_DESKTOP),
     135, uint(ActionTypeEnum::CHANGE_DESKTOP),
     150, uint(ActionTypeEnum::CHANGE_VIEWPORT),
     166, uint(ActionTypeEnum::SEND_KEYS),
     176, uint(ActionTypeEnum::MOVE_WINDOW),
     188, uint(ActionTypeEnum::RUN_COMMAND),
     200, uint(ActionTypeEnum::DRAG_AND_DROP),

       0        // eod
};

static const char qt_meta_stringdata_ActionTypeEnum[] = {
    "ActionTypeEnum\0ActionType\0NO_ACTION\0"
    "MOUSE_CLICK\0SCROLL\0MINIMIZE_WINDOW\0"
    "MAXIMIZE_RESTORE_WINDOW\0CLOSE_WINDOW\0"
    "RESIZE_WINDOW\0SHOW_DESKTOP\0CHANGE_DESKTOP\0"
    "CHANGE_VIEWPORT\0SEND_KEYS\0MOVE_WINDOW\0"
    "RUN_COMMAND\0DRAG_AND_DROP\0"
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
