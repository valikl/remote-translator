/****************************************************************************
** Meta object code from reading C++ file 'sounddevices.h'
**
** Created: Fri Mar 14 05:40:17 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sounddevices.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sounddevices.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SoundDevices[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   14,   13,   13, 0x08,
      57,   13,   13,   13, 0x08,
      83,   14,   13,   13, 0x08,
     115,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SoundDevices[] = {
    "SoundDevices\0\0checked\0"
    "on_DirectSoundButton_toggled(bool)\0"
    "on_ActSDButton_accepted()\0"
    "on_SelfTestButton_clicked(bool)\0"
    "on_ActSDButton_rejected()\0"
};

void SoundDevices::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SoundDevices *_t = static_cast<SoundDevices *>(_o);
        switch (_id) {
        case 0: _t->on_DirectSoundButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_ActSDButton_accepted(); break;
        case 2: _t->on_SelfTestButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_ActSDButton_rejected(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SoundDevices::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SoundDevices::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SoundDevices,
      qt_meta_data_SoundDevices, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SoundDevices::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SoundDevices::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SoundDevices::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SoundDevices))
        return static_cast<void*>(const_cast< SoundDevices*>(this));
    return QDialog::qt_metacast(_clname);
}

int SoundDevices::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
