#-------------------------------------------------
#
# Project created by QtCreator 2012-07-09T04:52:52
#
#-------------------------------------------------

QT       += core gui

TARGET = TT_RemoteTranslation
TEMPLATE = app


SOURCES += main.cpp\
    remotetranslatorui.cpp \
    BBTT/BB_Translator.cpp \
    BBTT/BB_Instance.cpp \
    BBTT/BB_ClientConfigMgr.cpp \
    Ticpp/tinyxmlerror.cpp \
    Ticpp/tinyxml.cpp \
    Ticpp/tinystr.cpp \
    Ticpp/ticpp.cpp \
    Ticpp/tinyxmlparser.cpp \
    sounddevices.cpp \
    soundfilters.cpp \
    BBTT/BB_Thread.cpp \
    manconnect.cpp \
    Utils/BB_Window.cpp \
    Utils/Lock.cpp \
    Utils/CriticalSection.cpp \
    Utils/Lockable.cpp

HEADERS  += \
    common.h \
    TeamTalk/TeamTalk4.h \
    remotetranslatorui.h \
    BBTT/targetver.h \
    BBTT/BB_Translator.h \
    BBTT/BB_Instance.h \
    BBTT/BB_ClientConfigMgr.h \
    BBTT/Utils.h \
    Ticpp/tinyxml.h \
    Ticpp/tinystr.h \
    Ticpp/ticpprc.h \
    Ticpp/ticpp.h \
    sounddevices.h \
    soundfilters.h \
    BBTT/IRunnable.h \
    BBTT/BB_Thread.h \
    manconnect.h \
    Utils/BB_Exception.h \
    Utils/BB_Window.h \
    Utils/Lockable.h \
    Utils/Lock.h \
    Utils/CriticalSection.h

FORMS    += remotetranslatorui.ui \
    sounddevices.ui \
    soundfilters.ui \
    manconnect.ui

OTHER_FILES += \
    images/webcam_stop.png \
    images/webcam_start.png \
    images/webcam.png \
    images/vumeter.png \
    images/voiceact.png \
    images/user_female.png \
    images/user.png \
    images/upload.png \
    images/tvframe.png \
    images/teamtalky.png \
    images/teamtalkg.png \
    images/teamtalk.png \
    images/teamtalk.ico \
    images/teamtalk.icns \
    images/stopsign.png \
    images/speaker.png \
    images/root_open.png \
    images/root.png \
    images/record.png \
    images/plus.png \
    images/op.png \
    images/oksign.png \
    images/muteall.png \
    images/msg.png \
    images/minus.png \
    images/mike.png \
    images/lock.png \
    images/hotkey.png \
    images/hand.png \
    images/echo_cancel.png \
    images/download.png \
    images/detach.png \
    images/desktoptx.png \
    images/desktopbg.png \
    images/delete.png \
    images/connect.png \
    images/channel_open.png \
    images/channel.png \
    images/admin.png

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lTeamTalk4
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lTeamTalk4

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/TeamTalk4.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/TeamTalk4.lib

win32:DEFINES += TIXML_USE_TICPP

CONFIG += static
