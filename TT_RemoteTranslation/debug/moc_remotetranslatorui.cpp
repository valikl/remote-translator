/****************************************************************************
** Meta object code from reading C++ file 'remotetranslatorui.h'
**
** Created: Fri Mar 14 05:40:16 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../remotetranslatorui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'remotetranslatorui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RemoteTranslatorUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      39,   19,   19,   19, 0x08,
      74,   69,   19,   19, 0x08,
     118,   69,   19,   19, 0x08,
     170,  162,   19,   19, 0x08,
     203,  199,   19,   19, 0x08,
     235,  162,   19,   19, 0x08,
     263,  162,   19,   19, 0x08,
     291,  199,   19,   19, 0x08,
     322,  199,   19,   19, 0x08,
     355,  199,   19,   19, 0x08,
     388,   19,   19,   19, 0x08,
     411,   19,   19,   19, 0x08,
     428,   19,   19,   19, 0x08,
     448,   19,   19,   19, 0x08,
     475,   19,   19,   19, 0x08,
     498,   19,   19,   19, 0x08,
     521,   19,   19,   19, 0x08,
     542,   19,   19,   19, 0x08,
     565,  162,   19,   19, 0x08,
     611,  603,   19,   19, 0x08,
     644,  162,   19,   19, 0x08,
     683,  679,   19,   19, 0x08,
     727,   19,   19,   19, 0x28,
     764,   19,   19,   19, 0x08,
     785,   19,   19,   19, 0x08,
     811,  679,   19,   19, 0x08,
     849,   19,   19,   19, 0x28,

       0        // eod
};

static const char qt_meta_stringdata_RemoteTranslatorUI[] = {
    "RemoteTranslatorUI\0\0changeMainConfig()\0"
    "on_NickName_editingFinished()\0arg1\0"
    "on_SrcLangList_currentIndexChanged(QString)\0"
    "on_TrgLangList_currentIndexChanged(QString)\0"
    "checked\0on_LangConnect_clicked(bool)\0"
    "val\0on_MicGainSld_valueChanged(int)\0"
    "on_MicMuteBut_clicked(bool)\0"
    "on_TrgMuteBut_clicked(bool)\0"
    "on_TrgLvlSld_valueChanged(int)\0"
    "on_SrcLevelSld_valueChanged(int)\0"
    "on_VideoLvlSld_valueChanged(int)\0"
    "on_MicrophoneTimeout()\0on_UserTimeout()\0"
    "on_ConlostTimeout()\0ActivateAdminChatButtons()\0"
    "ActivateSoundDevices()\0ActivateAudioFilters()\0"
    "ActivateManConnect()\0RestoreDefaultConfig()\0"
    "on_ServerSelfTestEn_stateChanged(int)\0"
    "clicked\0on_showVideoButton_clicked(bool)\0"
    "on_chooseTransButton_clicked(bool)\0"
    "str\0on_btnBtartTranslatorsChat_clicked(QString)\0"
    "on_btnBtartTranslatorsChat_clicked()\0"
    "ActivateChatWindow()\0ActivateAdminChatWindow()\0"
    "on_btnStartAdminChat_clicked(QString)\0"
    "on_btnStartAdminChat_clicked()\0"
};

void RemoteTranslatorUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RemoteTranslatorUI *_t = static_cast<RemoteTranslatorUI *>(_o);
        switch (_id) {
        case 0: _t->changeMainConfig(); break;
        case 1: _t->on_NickName_editingFinished(); break;
        case 2: _t->on_SrcLangList_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_TrgLangList_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_LangConnect_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_MicGainSld_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_MicMuteBut_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_TrgMuteBut_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_TrgLvlSld_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_SrcLevelSld_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_VideoLvlSld_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_MicrophoneTimeout(); break;
        case 12: _t->on_UserTimeout(); break;
        case 13: _t->on_ConlostTimeout(); break;
        case 14: _t->ActivateAdminChatButtons(); break;
        case 15: _t->ActivateSoundDevices(); break;
        case 16: _t->ActivateAudioFilters(); break;
        case 17: _t->ActivateManConnect(); break;
        case 18: _t->RestoreDefaultConfig(); break;
        case 19: _t->on_ServerSelfTestEn_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->on_showVideoButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->on_chooseTransButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->on_btnBtartTranslatorsChat_clicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: _t->on_btnBtartTranslatorsChat_clicked(); break;
        case 24: _t->ActivateChatWindow(); break;
        case 25: _t->ActivateAdminChatWindow(); break;
        case 26: _t->on_btnStartAdminChat_clicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 27: _t->on_btnStartAdminChat_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RemoteTranslatorUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RemoteTranslatorUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RemoteTranslatorUI,
      qt_meta_data_RemoteTranslatorUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RemoteTranslatorUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RemoteTranslatorUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RemoteTranslatorUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RemoteTranslatorUI))
        return static_cast<void*>(const_cast< RemoteTranslatorUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RemoteTranslatorUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
