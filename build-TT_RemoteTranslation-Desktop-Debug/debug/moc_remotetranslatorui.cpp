/****************************************************************************
** Meta object code from reading C++ file 'remotetranslatorui.h'
**
** Created: Fri May 3 09:52:53 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TT_RemoteTranslation/remotetranslatorui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'remotetranslatorui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RemoteTranslatorUI[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      39,   19,   19,   19, 0x08,
      74,   69,   19,   19, 0x08,
     114,   69,   19,   19, 0x08,
     158,   69,   19,   19, 0x08,
     210,  202,   19,   19, 0x08,
     243,  239,   19,   19, 0x08,
     275,  202,   19,   19, 0x08,
     303,  202,   19,   19, 0x08,
     331,  239,   19,   19, 0x08,
     362,  239,   19,   19, 0x08,
     395,  239,   19,   19, 0x08,
     428,   19,   19,   19, 0x08,
     451,   19,   19,   19, 0x08,
     468,   19,   19,   19, 0x08,
     488,   19,   19,   19, 0x08,
     511,   19,   19,   19, 0x08,
     534,   19,   19,   19, 0x08,
     555,   19,   19,   19, 0x08,
     578,  202,   19,   19, 0x08,
     615,  202,   19,   19, 0x08,
     661,  653,   19,   19, 0x08,
     694,  202,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RemoteTranslatorUI[] = {
    "RemoteTranslatorUI\0\0changeMainConfig()\0"
    "on_NickName_editingFinished()\0arg1\0"
    "on_HapList_currentIndexChanged(QString)\0"
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
    "on_ConlostTimeout()\0ActivateSoundDevices()\0"
    "ActivateAudioFilters()\0ActivateManConnect()\0"
    "RestoreDefaultConfig()\0"
    "on_LocalSelfTestEn_stateChanged(int)\0"
    "on_ServerSelfTestEn_stateChanged(int)\0"
    "clicked\0on_showVideoButton_clicked(bool)\0"
    "on_chooseTransButton_clicked(bool)\0"
};

const QMetaObject RemoteTranslatorUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RemoteTranslatorUI,
      qt_meta_data_RemoteTranslatorUI, 0 }
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
        switch (_id) {
        case 0: changeMainConfig(); break;
        case 1: on_NickName_editingFinished(); break;
        case 2: on_HapList_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: on_SrcLangList_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: on_TrgLangList_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: on_LangConnect_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: on_MicGainSld_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: on_MicMuteBut_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: on_TrgMuteBut_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: on_TrgLvlSld_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: on_SrcLevelSld_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: on_VideoLvlSld_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: on_MicrophoneTimeout(); break;
        case 13: on_UserTimeout(); break;
        case 14: on_ConlostTimeout(); break;
        case 15: ActivateSoundDevices(); break;
        case 16: ActivateAudioFilters(); break;
        case 17: ActivateManConnect(); break;
        case 18: RestoreDefaultConfig(); break;
        case 19: on_LocalSelfTestEn_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: on_ServerSelfTestEn_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: on_showVideoButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: on_chooseTransButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
