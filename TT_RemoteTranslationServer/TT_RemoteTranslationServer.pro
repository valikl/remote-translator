#-------------------------------------------------
#
# Project created by QtCreator 2013-08-22T03:41:18
#
#-------------------------------------------------

QT       += core gui

TARGET = TT_RemoteTranslationServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
   ../Utils/Lockable.cpp \
   ../Utils/Lock.cpp \
   ../Utils/CriticalSection.cpp \
   ../Utils/BB_Window.cpp \
   ../Utils/BB_Thread.cpp \
   ../Ticpp/tinyxml.cpp \
   ../Ticpp/tinystr.cpp \
   ../Ticpp/ticpp.cpp \
   ../Ticpp/tinyxmlparser.cpp \
   ../Ticpp/tinyxmlerror.cpp \
   ../Interfaces/BB_Instance.cpp \
    BB_TTRTS/controller.cpp \
    BB_TTRTS/maininstance.cpp \
    BB_TTRTS/configmanager.cpp

HEADERS  += mainwindow.h \
   ../Utils/Utils.h \
   ../Utils/Lockable.h \
   ../Utils/Lock.h \
   ../Utils/IRunnable.h \
   ../Utils/CriticalSection.h \
   ../Utils/BB_Window.h \
   ../Utils/BB_Thread.h \
   ../Utils/BB_Exception.h \
   ../Ticpp/tinystr.h \
   ../Ticpp/ticpprc.h \
   ../Ticpp/ticpp.h \
   ../Ticpp/tinyxml.h \
   ../TT_Include/TeamTalk4.h \
   ../Interfaces/BB_Instance.h \
    BB_TTRTS/controller.h \
    BB_TTRTS/maininstance.h \
    BB_TTRTS/configmanager.h

FORMS    += mainwindow.ui


win32:CONFIG(release, debug|release): LIBS += -L../TT_Lib/ -lTeamTalk4
else:win32:CONFIG(debug, debug|release): LIBS += -L../TT_Lib/ -lTeamTalk4

INCLUDEPATH += $$PWD/
INCLUDEPATH += ../
INCLUDEPATH += ../Interfaces/
INCLUDEPATH += ../Ticpp/
DEPENDPATH += $$PWD/

win32:CONFIG(release, debug|release): PRE_TARGETDEPS +=../TT_Lib/TeamTalk4.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS +=../TT_Lib/TeamTalk4.lib

win32:DEFINES += TIXML_USE_TICPP

CONFIG += static

