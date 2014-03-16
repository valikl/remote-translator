/********************************************************************************
** Form generated from reading UI file 'remotetranslatorui.ui'
**
** Created: Fri May 3 10:10:05 2013
**      by: Qt User Interface Compiler version 4.7.4
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
    QLabel *label;
    QComboBox *HapList;
    QComboBox *SrcLangList;
    QComboBox *TrgLangList;
    QLabel *label_2;
    QLineEdit *NickName;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QCheckBox *LocalSelfTestEn;
    QLabel *label_8;
    QPushButton *LangConnect;
    QLabel *label_9;
    QLabel *label_10;
    QSlider *MicGainSld;
    QLabel *label_11;
    QFrame *line_2;
    QProgressBar *MicLevelInd;
    QLabel *label_12;
    QPushButton *MicMuteBut;
    QLabel *MicStatusLbl;
    QFrame *line;
    QLabel *label_14;
    QLabel *label_15;
    QSlider *SrcLevelSld;
    QListWidget *SrcUsersList;
    QLabel *label_16;
    QLabel *label_17;
    QListWidget *TrgUsersList;
    QFrame *line_3;
    QLabel *label_18;
    QLabel *TrgStatusLbl;
    QSlider *TrgLvlSld;
    QLabel *label_20;
    QPushButton *TrgMuteBut;
    QSlider *VideoLvlSld;
    QLabel *label_21;
    QPushButton *showVideoButton;
    QLabel *label_13;
    QCheckBox *ServerSelfTestEn;
    QFrame *line_4;
    QLabel *label_19;
    QPushButton *chooseTransButton;
    QMenuBar *menuBar;
    QMenu *menuSound_Settings;
    QMenu *menuManual_TT_connection;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RemoteTranslatorUI)
    {
        if (RemoteTranslatorUI->objectName().isEmpty())
            RemoteTranslatorUI->setObjectName(QString::fromUtf8("RemoteTranslatorUI"));
        RemoteTranslatorUI->resize(776, 663);
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
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 16, 261, 41));
        HapList = new QComboBox(centralWidget);
        HapList->setObjectName(QString::fromUtf8("HapList"));
        HapList->setGeometry(QRect(130, 210, 161, 22));
        SrcLangList = new QComboBox(centralWidget);
        SrcLangList->setObjectName(QString::fromUtf8("SrcLangList"));
        SrcLangList->setGeometry(QRect(130, 330, 161, 22));
        TrgLangList = new QComboBox(centralWidget);
        TrgLangList->setObjectName(QString::fromUtf8("TrgLangList"));
        TrgLangList->setGeometry(QRect(130, 380, 161, 22));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 140, 71, 20));
        NickName = new QLineEdit(centralWidget);
        NickName->setObjectName(QString::fromUtf8("NickName"));
        NickName->setGeometry(QRect(130, 140, 161, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 210, 81, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 330, 111, 20));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 380, 111, 20));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 510, 261, 41));
        LocalSelfTestEn = new QCheckBox(centralWidget);
        LocalSelfTestEn->setObjectName(QString::fromUtf8("LocalSelfTestEn"));
        LocalSelfTestEn->setGeometry(QRect(120, 560, 16, 18));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 560, 91, 20));
        LangConnect = new QPushButton(centralWidget);
        LangConnect->setObjectName(QString::fromUtf8("LangConnect"));
        LangConnect->setGeometry(QRect(140, 460, 61, 23));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 270, 261, 41));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(420, 20, 261, 41));
        MicGainSld = new QSlider(centralWidget);
        MicGainSld->setObjectName(QString::fromUtf8("MicGainSld"));
        MicGainSld->setGeometry(QRect(460, 60, 160, 16));
        MicGainSld->setOrientation(Qt::Horizontal);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(350, 60, 111, 20));
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(330, 0, 20, 631));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        MicLevelInd = new QProgressBar(centralWidget);
        MicLevelInd->setObjectName(QString::fromUtf8("MicLevelInd"));
        MicLevelInd->setGeometry(QRect(460, 100, 191, 23));
        MicLevelInd->setValue(24);
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(350, 100, 111, 20));
        MicMuteBut = new QPushButton(centralWidget);
        MicMuteBut->setObjectName(QString::fromUtf8("MicMuteBut"));
        MicMuteBut->setGeometry(QRect(350, 160, 101, 71));
        MicStatusLbl = new QLabel(centralWidget);
        MicStatusLbl->setObjectName(QString::fromUtf8("MicStatusLbl"));
        MicStatusLbl->setGeometry(QRect(500, 150, 101, 61));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(340, 240, 441, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(420, 250, 261, 41));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(350, 300, 141, 20));
        SrcLevelSld = new QSlider(centralWidget);
        SrcLevelSld->setObjectName(QString::fromUtf8("SrcLevelSld"));
        SrcLevelSld->setGeometry(QRect(510, 300, 160, 16));
        SrcLevelSld->setOrientation(Qt::Horizontal);
        SrcUsersList = new QListWidget(centralWidget);
        SrcUsersList->setObjectName(QString::fromUtf8("SrcUsersList"));
        SrcUsersList->setGeometry(QRect(650, 160, 101, 71));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(650, 120, 111, 31));
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(650, 410, 111, 31));
        TrgUsersList = new QListWidget(centralWidget);
        TrgUsersList->setObjectName(QString::fromUtf8("TrgUsersList"));
        TrgUsersList->setGeometry(QRect(660, 450, 101, 71));
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(340, 360, 441, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(350, 370, 261, 41));
        TrgStatusLbl = new QLabel(centralWidget);
        TrgStatusLbl->setObjectName(QString::fromUtf8("TrgStatusLbl"));
        TrgStatusLbl->setGeometry(QRect(500, 450, 101, 61));
        TrgLvlSld = new QSlider(centralWidget);
        TrgLvlSld->setObjectName(QString::fromUtf8("TrgLvlSld"));
        TrgLvlSld->setGeometry(QRect(490, 420, 160, 16));
        TrgLvlSld->setOrientation(Qt::Horizontal);
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(360, 420, 131, 31));
        TrgMuteBut = new QPushButton(centralWidget);
        TrgMuteBut->setObjectName(QString::fromUtf8("TrgMuteBut"));
        TrgMuteBut->setGeometry(QRect(350, 460, 101, 51));
        VideoLvlSld = new QSlider(centralWidget);
        VideoLvlSld->setObjectName(QString::fromUtf8("VideoLvlSld"));
        VideoLvlSld->setGeometry(QRect(480, 580, 160, 16));
        VideoLvlSld->setOrientation(Qt::Horizontal);
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(360, 580, 111, 20));
        showVideoButton = new QPushButton(centralWidget);
        showVideoButton->setObjectName(QString::fromUtf8("showVideoButton"));
        showVideoButton->setGeometry(QRect(680, 570, 75, 31));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(170, 560, 111, 20));
        ServerSelfTestEn = new QCheckBox(centralWidget);
        ServerSelfTestEn->setObjectName(QString::fromUtf8("ServerSelfTestEn"));
        ServerSelfTestEn->setGeometry(QRect(280, 560, 16, 18));
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(340, 520, 441, 16));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(410, 530, 291, 41));
        chooseTransButton = new QPushButton(centralWidget);
        chooseTransButton->setObjectName(QString::fromUtf8("chooseTransButton"));
        chooseTransButton->setGeometry(QRect(660, 380, 91, 23));
        RemoteTranslatorUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RemoteTranslatorUI);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 776, 18));
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
        label_6->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Self Test</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        LocalSelfTestEn->setText(QString());
        label_8->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Local self test</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        LangConnect->setText(QApplication::translate("RemoteTranslatorUI", "Connect", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Translation connection</span></p></body></html>", 0, QApplication::UnicodeUTF8));
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
        label_16->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Listeners</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Translators</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Other translators:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        TrgStatusLbl->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#008000;\"><span style=\" font-size:12pt; font-weight:600; color:#ffffff;\">Listen </span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#008000;\"><span style=\" font-size:12pt; font-weight:600; color:#ffffff;\">translators</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Other translators </span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">volume</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        TrgMuteBut->setText(QApplication::translate("RemoteTranslatorUI", "Translators mute", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Video quality</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        showVideoButton->setText(QApplication::translate("RemoteTranslatorUI", "Show video", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Server self test</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        ServerSelfTestEn->setText(QString());
        label_19->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Video control</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        chooseTransButton->setText(QApplication::translate("RemoteTranslatorUI", "Choose local", 0, QApplication::UnicodeUTF8));
        menuSound_Settings->setTitle(QApplication::translate("RemoteTranslatorUI", "Sound Settings", 0, QApplication::UnicodeUTF8));
        menuManual_TT_connection->setTitle(QApplication::translate("RemoteTranslatorUI", "Manual connection", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RemoteTranslatorUI: public Ui_RemoteTranslatorUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOTETRANSLATORUI_H
