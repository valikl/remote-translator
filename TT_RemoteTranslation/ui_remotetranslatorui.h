/********************************************************************************
** Form generated from reading UI file 'remotetranslatorui.ui'
**
** Created: Fri Jun 7 04:13:24 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOTETRANSLATORUI_H
#define UI_REMOTETRANSLATORUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RemoteTranslatorUI
{
public:
    QAction *actionConfigure_Audio;
    QAction *actionChange_nickname;
    QAction *actionChange_password;
    QAction *actionTT_server_connection;
    QAction *actionControl_server_connection;
    QAction *actionAudio_Filters;
    QAction *actionRestore_default_configuration;
    QWidget *centralWidget;
    QTabWidget *ControlTabs;
    QWidget *connectControl;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *NickName;
    QLabel *label_3;
    QComboBox *HapList;
    QLabel *label_9;
    QLabel *label_4;
    QComboBox *SrcLangList;
    QLabel *label_5;
    QComboBox *TrgLangList;
    QPushButton *LangConnect;
    QLabel *label_6;
    QLabel *label_8;
    QCheckBox *LocalSelfTestEn;
    QLabel *label_13;
    QCheckBox *ServerSelfTestEn;
    QWidget *translateControl;
    QLabel *label_10;
    QLabel *label_11;
    QSlider *MicGainSld;
    QProgressBar *MicLevelInd;
    QLabel *label_12;
    QPushButton *MicMuteBut;
    QLabel *MicStatusLbl;
    QLabel *label_16;
    QListWidget *SrcUsersList;
    QFrame *line;
    QLabel *label_14;
    QLabel *label_15;
    QSlider *SrcLevelSld;
    QFrame *line_3;
    QLabel *label_18;
    QLabel *label_20;
    QSlider *TrgLvlSld;
    QPushButton *chooseTransButton;
    QPushButton *TrgMuteBut;
    QLabel *TrgStatusLbl;
    QLabel *label_17;
    QListWidget *TrgUsersList;
    QFrame *line_4;
    QLabel *label_19;
    QLabel *label_21;
    QSlider *VideoLvlSld;
    QPushButton *showVideoButton;
    QMenuBar *menuBar;
    QMenu *menuSound_Settings;
    QMenu *menuManual_TT_connection;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RemoteTranslatorUI)
    {
        if (RemoteTranslatorUI->objectName().isEmpty())
            RemoteTranslatorUI->setObjectName(QString::fromUtf8("RemoteTranslatorUI"));
        RemoteTranslatorUI->resize(340, 575);
        actionConfigure_Audio = new QAction(RemoteTranslatorUI);
        actionConfigure_Audio->setObjectName(QString::fromUtf8("actionConfigure_Audio"));
        actionChange_nickname = new QAction(RemoteTranslatorUI);
        actionChange_nickname->setObjectName(QString::fromUtf8("actionChange_nickname"));
        actionChange_password = new QAction(RemoteTranslatorUI);
        actionChange_password->setObjectName(QString::fromUtf8("actionChange_password"));
        actionTT_server_connection = new QAction(RemoteTranslatorUI);
        actionTT_server_connection->setObjectName(QString::fromUtf8("actionTT_server_connection"));
        actionControl_server_connection = new QAction(RemoteTranslatorUI);
        actionControl_server_connection->setObjectName(QString::fromUtf8("actionControl_server_connection"));
        actionAudio_Filters = new QAction(RemoteTranslatorUI);
        actionAudio_Filters->setObjectName(QString::fromUtf8("actionAudio_Filters"));
        actionRestore_default_configuration = new QAction(RemoteTranslatorUI);
        actionRestore_default_configuration->setObjectName(QString::fromUtf8("actionRestore_default_configuration"));
        centralWidget = new QWidget(RemoteTranslatorUI);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ControlTabs = new QTabWidget(centralWidget);
        ControlTabs->setObjectName(QString::fromUtf8("ControlTabs"));
        ControlTabs->setGeometry(QRect(0, 0, 341, 531));
        connectControl = new QWidget();
        connectControl->setObjectName(QString::fromUtf8("connectControl"));
        label = new QLabel(connectControl);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 0, 261, 41));
        label_2 = new QLabel(connectControl);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 50, 71, 20));
        NickName = new QLineEdit(connectControl);
        NickName->setObjectName(QString::fromUtf8("NickName"));
        NickName->setGeometry(QRect(140, 50, 161, 20));
        label_3 = new QLabel(connectControl);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 90, 81, 20));
        HapList = new QComboBox(connectControl);
        HapList->setObjectName(QString::fromUtf8("HapList"));
        HapList->setGeometry(QRect(140, 90, 181, 22));
        label_9 = new QLabel(connectControl);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(50, 120, 261, 41));
        label_4 = new QLabel(connectControl);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 170, 111, 20));
        SrcLangList = new QComboBox(connectControl);
        SrcLangList->setObjectName(QString::fromUtf8("SrcLangList"));
        SrcLangList->setGeometry(QRect(140, 170, 181, 22));
        label_5 = new QLabel(connectControl);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 210, 111, 20));
        TrgLangList = new QComboBox(connectControl);
        TrgLangList->setObjectName(QString::fromUtf8("TrgLangList"));
        TrgLangList->setGeometry(QRect(140, 210, 181, 22));
        LangConnect = new QPushButton(connectControl);
        LangConnect->setObjectName(QString::fromUtf8("LangConnect"));
        LangConnect->setGeometry(QRect(140, 250, 61, 23));
        label_6 = new QLabel(connectControl);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 280, 261, 41));
        label_8 = new QLabel(connectControl);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 330, 91, 20));
        LocalSelfTestEn = new QCheckBox(connectControl);
        LocalSelfTestEn->setObjectName(QString::fromUtf8("LocalSelfTestEn"));
        LocalSelfTestEn->setGeometry(QRect(120, 330, 16, 18));
        label_13 = new QLabel(connectControl);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(170, 330, 111, 20));
        ServerSelfTestEn = new QCheckBox(connectControl);
        ServerSelfTestEn->setObjectName(QString::fromUtf8("ServerSelfTestEn"));
        ServerSelfTestEn->setGeometry(QRect(290, 330, 16, 18));
        ControlTabs->addTab(connectControl, QString());
        translateControl = new QWidget();
        translateControl->setObjectName(QString::fromUtf8("translateControl"));
        label_10 = new QLabel(translateControl);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 0, 261, 41));
        label_11 = new QLabel(translateControl);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 40, 111, 20));
        MicGainSld = new QSlider(translateControl);
        MicGainSld->setObjectName(QString::fromUtf8("MicGainSld"));
        MicGainSld->setGeometry(QRect(140, 40, 160, 16));
        MicGainSld->setOrientation(Qt::Horizontal);
        MicLevelInd = new QProgressBar(translateControl);
        MicLevelInd->setObjectName(QString::fromUtf8("MicLevelInd"));
        MicLevelInd->setGeometry(QRect(140, 70, 191, 23));
        MicLevelInd->setValue(24);
        label_12 = new QLabel(translateControl);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 70, 111, 20));
        MicMuteBut = new QPushButton(translateControl);
        MicMuteBut->setObjectName(QString::fromUtf8("MicMuteBut"));
        MicMuteBut->setGeometry(QRect(10, 100, 91, 41));
        MicStatusLbl = new QLabel(translateControl);
        MicStatusLbl->setObjectName(QString::fromUtf8("MicStatusLbl"));
        MicStatusLbl->setGeometry(QRect(120, 100, 101, 41));
        label_16 = new QLabel(translateControl);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(230, 100, 101, 20));
        SrcUsersList = new QListWidget(translateControl);
        SrcUsersList->setObjectName(QString::fromUtf8("SrcUsersList"));
        SrcUsersList->setGeometry(QRect(230, 120, 101, 71));
        line = new QFrame(translateControl);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 190, 341, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_14 = new QLabel(translateControl);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(30, 200, 261, 31));
        label_15 = new QLabel(translateControl);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 230, 141, 20));
        SrcLevelSld = new QSlider(translateControl);
        SrcLevelSld->setObjectName(QString::fromUtf8("SrcLevelSld"));
        SrcLevelSld->setGeometry(QRect(170, 230, 160, 16));
        SrcLevelSld->setOrientation(Qt::Horizontal);
        line_3 = new QFrame(translateControl);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(0, 250, 341, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        label_18 = new QLabel(translateControl);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(30, 260, 261, 41));
        label_20 = new QLabel(translateControl);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(10, 300, 131, 31));
        TrgLvlSld = new QSlider(translateControl);
        TrgLvlSld->setObjectName(QString::fromUtf8("TrgLvlSld"));
        TrgLvlSld->setGeometry(QRect(170, 300, 160, 16));
        TrgLvlSld->setOrientation(Qt::Horizontal);
        chooseTransButton = new QPushButton(translateControl);
        chooseTransButton->setObjectName(QString::fromUtf8("chooseTransButton"));
        chooseTransButton->setGeometry(QRect(240, 320, 91, 23));
        TrgMuteBut = new QPushButton(translateControl);
        TrgMuteBut->setObjectName(QString::fromUtf8("TrgMuteBut"));
        TrgMuteBut->setGeometry(QRect(10, 350, 101, 41));
        TrgStatusLbl = new QLabel(translateControl);
        TrgStatusLbl->setObjectName(QString::fromUtf8("TrgStatusLbl"));
        TrgStatusLbl->setGeometry(QRect(120, 340, 101, 61));
        label_17 = new QLabel(translateControl);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(230, 350, 91, 21));
        TrgUsersList = new QListWidget(translateControl);
        TrgUsersList->setObjectName(QString::fromUtf8("TrgUsersList"));
        TrgUsersList->setGeometry(QRect(230, 370, 101, 71));
        line_4 = new QFrame(translateControl);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(0, 440, 341, 16));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        label_19 = new QLabel(translateControl);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(20, 450, 291, 31));
        label_21 = new QLabel(translateControl);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(0, 480, 91, 20));
        VideoLvlSld = new QSlider(translateControl);
        VideoLvlSld->setObjectName(QString::fromUtf8("VideoLvlSld"));
        VideoLvlSld->setGeometry(QRect(90, 480, 160, 16));
        VideoLvlSld->setOrientation(Qt::Horizontal);
        showVideoButton = new QPushButton(translateControl);
        showVideoButton->setObjectName(QString::fromUtf8("showVideoButton"));
        showVideoButton->setGeometry(QRect(260, 470, 75, 31));
        ControlTabs->addTab(translateControl, QString());
        RemoteTranslatorUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RemoteTranslatorUI);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 340, 18));
        menuSound_Settings = new QMenu(menuBar);
        menuSound_Settings->setObjectName(QString::fromUtf8("menuSound_Settings"));
        menuManual_TT_connection = new QMenu(menuBar);
        menuManual_TT_connection->setObjectName(QString::fromUtf8("menuManual_TT_connection"));
        RemoteTranslatorUI->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RemoteTranslatorUI);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        RemoteTranslatorUI->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RemoteTranslatorUI);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        RemoteTranslatorUI->setStatusBar(statusBar);

        menuBar->addAction(menuSound_Settings->menuAction());
        menuBar->addAction(menuManual_TT_connection->menuAction());
        menuSound_Settings->addAction(actionConfigure_Audio);
        menuSound_Settings->addAction(actionAudio_Filters);
        menuManual_TT_connection->addAction(actionTT_server_connection);
        menuManual_TT_connection->addAction(actionRestore_default_configuration);

        retranslateUi(RemoteTranslatorUI);

        ControlTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RemoteTranslatorUI);
    } // setupUi

    void retranslateUi(QMainWindow *RemoteTranslatorUI)
    {
        RemoteTranslatorUI->setWindowTitle(QApplication::translate("RemoteTranslatorUI", "RemoteTranslatorUI", 0, QApplication::UnicodeUTF8));
        actionConfigure_Audio->setText(QApplication::translate("RemoteTranslatorUI", "Configure Audio", 0, QApplication::UnicodeUTF8));
        actionChange_nickname->setText(QApplication::translate("RemoteTranslatorUI", "Change nickname", 0, QApplication::UnicodeUTF8));
        actionChange_password->setText(QApplication::translate("RemoteTranslatorUI", "Change password", 0, QApplication::UnicodeUTF8));
        actionTT_server_connection->setText(QApplication::translate("RemoteTranslatorUI", "TT server connection", 0, QApplication::UnicodeUTF8));
        actionControl_server_connection->setText(QApplication::translate("RemoteTranslatorUI", "Control server connection", 0, QApplication::UnicodeUTF8));
        actionAudio_Filters->setText(QApplication::translate("RemoteTranslatorUI", "Audio Filters", 0, QApplication::UnicodeUTF8));
        actionRestore_default_configuration->setText(QApplication::translate("RemoteTranslatorUI", "Restore default configuration", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Global configuration</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">NickName</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Happenings</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Translation connection</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Translate from:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Translate to:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        LangConnect->setText(QApplication::translate("RemoteTranslatorUI", "Connect", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Self Test</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Local self test</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        LocalSelfTestEn->setText(QString());
        label_13->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Server self test</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        ServerSelfTestEn->setText(QString());
        ControlTabs->setTabText(ControlTabs->indexOf(connectControl), QApplication::translate("RemoteTranslatorUI", "Tab 1", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Microphone control</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Microphone gain</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Microphone level</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        MicMuteBut->setText(QApplication::translate("RemoteTranslatorUI", "Microphone mute", 0, QApplication::UnicodeUTF8));
        MicStatusLbl->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#008000;\"><span style=\" font-size:12pt; font-weight:600; color:#ffffff;\">Microphone</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#008000;\"><span style=\" font-size:12pt; font-weight:600; color:#ffffff;\"> ON</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Listeners</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">&quot;From&quot; channel volume</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">&quot;From&quot; channel volume</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Other translators:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Other translators </span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">volume</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        chooseTransButton->setText(QApplication::translate("RemoteTranslatorUI", "Choose local", 0, QApplication::UnicodeUTF8));
        TrgMuteBut->setText(QApplication::translate("RemoteTranslatorUI", "Translators mute", 0, QApplication::UnicodeUTF8));
        TrgStatusLbl->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#008000;\"><span style=\" font-size:12pt; font-weight:600; color:#ffffff;\">Listen </span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#008000;\"><span style=\" font-size:12pt; font-weight:600; color:#ffffff;\">translators</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Translators</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Video control</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Video quality</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        showVideoButton->setText(QApplication::translate("RemoteTranslatorUI", "Show video", 0, QApplication::UnicodeUTF8));
        ControlTabs->setTabText(ControlTabs->indexOf(translateControl), QApplication::translate("RemoteTranslatorUI", "Tab 2", 0, QApplication::UnicodeUTF8));
        menuSound_Settings->setTitle(QApplication::translate("RemoteTranslatorUI", "Sound Settings", 0, QApplication::UnicodeUTF8));
        menuManual_TT_connection->setTitle(QApplication::translate("RemoteTranslatorUI", "Manual connection", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RemoteTranslatorUI: public Ui_RemoteTranslatorUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOTETRANSLATORUI_H
