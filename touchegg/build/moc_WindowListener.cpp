/****************************************************************************
** Meta object code from reading C++ file 'WindowListener.h'
**
** Created: Thu Sep 22 18:27:48 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/touchegg/windows/WindowListener.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WindowListener.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WindowListener[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   16,   15,   15, 0x05,
      40,   16,   15,   15, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_WindowListener[] = {
    "WindowListener\0\0w\0windowCreated(Window)\0"
    "windowDeleted(Window)\0"
};

const QMetaObject WindowListener::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WindowListener,
      qt_meta_data_WindowListener, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WindowListener::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WindowListener::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WindowListener::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WindowListener))
        return static_cast<void*>(const_cast< WindowListener*>(this));
    return QObject::qt_metacast(_clname);
}

int WindowListener::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: windowCreated((*reinterpret_cast< Window(*)>(_a[1]))); break;
        case 1: windowDeleted((*reinterpret_cast< Window(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void WindowListener::windowCreated(Window _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WindowListener::windowDeleted(Window _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
