/****************************************************************************
** Meta object code from reading C++ file 'channelstree.h'
**
** Created: Fri Aug 23 05:06:36 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../channelstree.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'channelstree.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChannelsTree[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      37,   13,   13,   13, 0x05,
      63,   13,   13,   13, 0x05,
      88,   84,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     152,  140,   13,   13, 0x08,
     196,  140,   13,   13, 0x08,
     239,  234,   13,   13, 0x08,
     282,   13,   13,   13, 0x0a,
     311,  301,   13,   13, 0x0a,
     331,  301,   13,   13, 0x0a,
     354,  301,   13,   13, 0x0a,
     394,  377,   13,   13, 0x0a,
     416,  377,   13,   13, 0x0a,
     440,  377,   13,   13, 0x0a,
     479,  464,   13,   13, 0x0a,
     524,  505,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ChannelsTree[] = {
    "ChannelsTree\0\0userDoubleClicked(int)\0"
    "channelDoubleClicked(int)\0"
    "fileDropped(QString)\0,,,\0"
    "classroomChanged(int,QSet<int>,QSet<int>,QSet<int>)\0"
    "item,column\0slotItemDoubleClicked(QTreeWidgetItem*,int)\0"
    "slotItemChanged(QTreeWidgetItem*,int)\0"
    "item\0slotUpdateTreeWidgetItem(QTreeWidgetItem*)\0"
    "slotServerUpdate()\0channelid\0"
    "slotAddChannel(int)\0slotUpdateChannel(int)\0"
    "slotRemoveChannel(int)\0userid,channelid\0"
    "slotUserJoin(int,int)\0slotUserUpdate(int,int)\0"
    "slotUserRemove(int,int)\0userid,talking\0"
    "slotUserTalking(int,bool)\0userid,frame_count\0"
    "slotUserVideoFrame(int,int)\0"
};

void ChannelsTree::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ChannelsTree *_t = static_cast<ChannelsTree *>(_o);
        switch (_id) {
        case 0: _t->userDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->channelDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->fileDropped((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->classroomChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QSet<int>(*)>(_a[2])),(*reinterpret_cast< const QSet<int>(*)>(_a[3])),(*reinterpret_cast< const QSet<int>(*)>(_a[4]))); break;
        case 4: _t->slotItemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->slotItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->slotUpdateTreeWidgetItem((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->slotServerUpdate(); break;
        case 8: _t->slotAddChannel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slotUpdateChannel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slotRemoveChannel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slotUserJoin((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->slotUserUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->slotUserRemove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->slotUserTalking((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 15: _t->slotUserVideoFrame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ChannelsTree::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ChannelsTree::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_ChannelsTree,
      qt_meta_data_ChannelsTree, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChannelsTree::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChannelsTree::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChannelsTree::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChannelsTree))
        return static_cast<void*>(const_cast< ChannelsTree*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int ChannelsTree::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ChannelsTree::userDoubleClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ChannelsTree::channelDoubleClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ChannelsTree::fileDropped(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ChannelsTree::classroomChanged(int _t1, const QSet<int> & _t2, const QSet<int> & _t3, const QSet<int> & _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
