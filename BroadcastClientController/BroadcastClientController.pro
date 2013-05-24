#-------------------------------------------------
#
# Project created by QtCreator 2012-07-09T04:52:52
#
#-------------------------------------------------

QT       += core gui

TARGET = BroadcastClientController
TEMPLATE = app


SOURCES += main.cpp\
    BBTT/BB_InstanceSource.cpp \
    BBTT/BB_InstanceReceiver.cpp \
    BBTT/BB_ConfigMgr.cpp \
    BBTT/BB_GroupMgr.cpp \
    BBTT/BB_GroupMgrSource.cpp \
    BBTT/BB_GroupMgrReceiver.cpp \
    ../Utils/Lockable.cpp \
    ../Utils/Lock.cpp \
    ../Utils/CriticalSection.cpp \
    ../Utils/BB_Window.cpp \
    ../Utils/BB_Thread.cpp \
    ../Interfaces/BB_Instance.cpp \
    ../Ticpp/tinyxmlparser.cpp \
    ../Ticpp/tinyxmlerror.cpp \
    ../Ticpp/tinyxml.cpp \
    ../Ticpp/tinystr.cpp \
    ../Ticpp/ticpp.cpp \
    GUI/ttinstview.cpp \
    GUI/controlpanel.cpp \
    GUI/audiosettings.cpp \
    GUI/groupsettings.cpp \
    GUI/instsettings.cpp

HEADERS  += \
    common.h \
    BBTT/targetver.h \
    BBTT/BB_InstanceSource.h \
    BBTT/BB_InstanceReceiver.h \
    BBTT/BB_ConfigMgr.h \
    BBTT/BB_GroupMgr.h \
    BBTT/BB_GroupMgrSource.h \
    BBTT/BB_GroupMgrReceiver.h \
    ../Interfaces/BB_Instance.h \
    ../Ticpp/tinyxml.h \
    ../Ticpp/tinystr.h \
    ../Ticpp/ticpprc.h \
    ../Ticpp/ticpp.h \
    ../TT_Include/TeamTalk4.h \
    ../Utils/Utils.h \
    ../Utils/Lockable.h \
    ../Utils/Lock.h \
    ../Utils/IRunnable.h \
    ../Utils/CriticalSection.h \
    ../Utils/BB_Window.h \
    ../Utils/BB_Thread.h \
    ../Utils/BB_Exception.h \
    GUI/controlpanel.h \
    GUI/ttinstview.h \
    GUI/common_gui.h \
    GUI/audiosettings.h \
    GUI/groupsettings.h \
    GUI/instsettings.h



win32:CONFIG(release, debug|release): LIBS += -L../$$PWD/TT_Lib/ -lTeamTalk4
else:win32:CONFIG(debug, debug|release): LIBS += -L../$$PWD/TT_Lib/ -lTeamTalk4

INCLUDEPATH += $$PWD/
INCLUDEPATH += ../
INCLUDEPATH += ../Interfaces/
INCLUDEPATH += ../Ticpp/
DEPENDPATH += $$PWD/

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += ../$$PWD/TT_Lib/TeamTalk4.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += ../$$PWD/TT_Lib/TeamTalk4.lib

win32:DEFINES += TIXML_USE_TICPP

CONFIG += static
