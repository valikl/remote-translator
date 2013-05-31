#ifndef COMMON_GUI_H
#define COMMON_GUI_H

#include <QtGui>
#include "BBTT/BB_ConfigMgr.h"
#include "BBTT/BB_GroupMgrSource.h"
#include "BBTT/BB_GroupMgrReceiver.h"

#define GRID(layout) ((QGridLayout*)(layout))
#define ConfigMgr (BB_ConfigMgr::Instance())
#define SourcesMgr (BB_GroupMgrSource::Instance(GROUP_TYPE_SOURCES))
#define RestrictedMgr (BB_GroupMgrSource::Instance(GROUP_TYPE_RESTRICTED_SERVERS))
#define ReceiversMgr (BB_GroupMgrReceiver::Instance())

#define CHANGE_IF_NEEDED(getval, setval, val) \
if ((getval) != (val)) \
{ \
    setval(type, val); \
    is_changed = true; \
}

#endif
