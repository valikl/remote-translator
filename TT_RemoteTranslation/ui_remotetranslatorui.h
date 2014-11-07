/********************************************************************************
** Form generated from reading UI file 'remotetranslatorui.ui'
**
** Created: Fri Nov 7 04:31:53 2014
**      by: Qt User Interface Compiler version 4.8.1
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
#include <QtGui/QGridLayout>
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
    QGridLayout *gridLayout;
    QTabWidget *ControlTabs;
    QWidget *connectControl;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *NickName;
    QLabel *label_9;
    QLabel *label_4;
    QComboBox *SrcLangList;
    QLabel *label_5;
    QComboBox *TrgLangList;
    QPushButton *LangConnect;
    QLabel *label_13;
    QCheckBox *ServerSelfTestEn;
    QWidget *translateControl;
    QGridLayout *gridLayout_3;
    QLabel *label_10;
    QLabel *label_11;
    QSlider *MicGainSld;
    QLabel *label_12;
    QProgressBar *MicLevelInd;
    QPushButton *MicMuteBut;
    QLabel *MicStatusLbl;
    QLabel *label_16;
    QListWidget *SrcUsersList;
    QLabel *label_14;
    QSlider *SrcLevelSld;
    QLabel *label_18;
    QLabel *label_20;
    QSlider *TrgLvlSld;
    QLabel *TrgStatusLbl;
    QPushButton *chooseTransButton;
    QPushButton *TrgMuteBut;
    QLabel *label_17;
    QListWidget *TrgUsersList;
    QPushButton *btnBtartTranslatorsChat;
    QPushButton *btnStartAdminChat;
    QLabel *label_19;
    QPushButton *showVideoButton;
    QSlider *VideoLvlSld;
    QMenuBar *menuBar;
    QMenu *menuSound_Settings;
    QMenu *menuManual_TT_connection;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RemoteTranslatorUI)
    {
        if (RemoteTranslatorUI->objectName().isEmpty())
            RemoteTranslatorUI->setObjectName(QString::fromUtf8("RemoteTranslatorUI"));
        RemoteTranslatorUI->resize(408, 690);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RemoteTranslatorUI->sizePolicy().hasHeightForWidth());
        RemoteTranslatorUI->setSizePolicy(sizePolicy);
        RemoteTranslatorUI->setMinimumSize(QSize(408, 690));
        RemoteTranslatorUI->setMaximumSize(QSize(816, 1380));
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
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ControlTabs = new QTabWidget(centralWidget);
        ControlTabs->setObjectName(QString::fromUtf8("ControlTabs"));
        connectControl = new QWidget();
        connectControl->setObjectName(QString::fromUtf8("connectControl"));
        gridLayout_2 = new QGridLayout(connectControl);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(connectControl);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 4);

        label_2 = new QLabel(connectControl);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        NickName = new QLineEdit(connectControl);
        NickName->setObjectName(QString::fromUtf8("NickName"));

        gridLayout_2->addWidget(NickName, 1, 1, 1, 2);

        label_9 = new QLabel(connectControl);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 2, 0, 1, 4);

        label_4 = new QLabel(connectControl);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        SrcLangList = new QComboBox(connectControl);
        SrcLangList->setObjectName(QString::fromUtf8("SrcLangList"));

        gridLayout_2->addWidget(SrcLangList, 3, 1, 1, 3);

        label_5 = new QLabel(connectControl);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        TrgLangList = new QComboBox(connectControl);
        TrgLangList->setObjectName(QString::fromUtf8("TrgLangList"));

        gridLayout_2->addWidget(TrgLangList, 4, 1, 1, 3);

        LangConnect = new QPushButton(connectControl);
        LangConnect->setObjectName(QString::fromUtf8("LangConnect"));

        gridLayout_2->addWidget(LangConnect, 5, 1, 1, 1);

        label_13 = new QLabel(connectControl);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 6, 2, 1, 1);

        ServerSelfTestEn = new QCheckBox(connectControl);
        ServerSelfTestEn->setObjectName(QString::fromUtf8("ServerSelfTestEn"));

        gridLayout_2->addWidget(ServerSelfTestEn, 6, 3, 1, 1);

        ControlTabs->addTab(connectControl, QString());
        translateControl = new QWidget();
        translateControl->setObjectName(QString::fromUtf8("translateControl"));
        gridLayout_3 = new QGridLayout(translateControl);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_10 = new QLabel(translateControl);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_3->addWidget(label_10, 0, 2, 1, 7);

        label_11 = new QLabel(translateControl);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 1, 1, 1, 4);

        MicGainSld = new QSlider(translateControl);
        MicGainSld->setObjectName(QString::fromUtf8("MicGainSld"));
        MicGainSld->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(MicGainSld, 1, 5, 1, 4);

        label_12 = new QLabel(translateControl);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 2, 1, 1, 4);

        MicLevelInd = new QProgressBar(translateControl);
        MicLevelInd->setObjectName(QString::fromUtf8("MicLevelInd"));
        MicLevelInd->setValue(24);

        gridLayout_3->addWidget(MicLevelInd, 2, 5, 1, 4);

        MicMuteBut = new QPushButton(translateControl);
        MicMuteBut->setObjectName(QString::fromUtf8("MicMuteBut"));

        gridLayout_3->addWidget(MicMuteBut, 3, 0, 2, 4);

        MicStatusLbl = new QLabel(translateControl);
        MicStatusLbl->setObjectName(QString::fromUtf8("MicStatusLbl"));

        gridLayout_3->addWidget(MicStatusLbl, 3, 4, 2, 2);

        label_16 = new QLabel(translateControl);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_3->addWidget(label_16, 3, 6, 1, 3);

        SrcUsersList = new QListWidget(translateControl);
        SrcUsersList->setObjectName(QString::fromUtf8("SrcUsersList"));

        gridLayout_3->addWidget(SrcUsersList, 4, 6, 1, 3);

        label_14 = new QLabel(translateControl);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_3->addWidget(label_14, 5, 2, 1, 7);

        SrcLevelSld = new QSlider(translateControl);
        SrcLevelSld->setObjectName(QString::fromUtf8("SrcLevelSld"));
        SrcLevelSld->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(SrcLevelSld, 6, 3, 1, 4);

        label_18 = new QLabel(translateControl);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_3->addWidget(label_18, 7, 2, 1, 7);

        label_20 = new QLabel(translateControl);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_3->addWidget(label_20, 8, 1, 1, 2);

        TrgLvlSld = new QSlider(translateControl);
        TrgLvlSld->setObjectName(QString::fromUtf8("TrgLvlSld"));
        TrgLvlSld->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(TrgLvlSld, 8, 3, 1, 4);

        TrgStatusLbl = new QLabel(translateControl);
        TrgStatusLbl->setObjectName(QString::fromUtf8("TrgStatusLbl"));

        gridLayout_3->addWidget(TrgStatusLbl, 9, 4, 3, 2);

        chooseTransButton = new QPushButton(translateControl);
        chooseTransButton->setObjectName(QString::fromUtf8("chooseTransButton"));

        gridLayout_3->addWidget(chooseTransButton, 9, 7, 1, 2);

        TrgMuteBut = new QPushButton(translateControl);
        TrgMuteBut->setObjectName(QString::fromUtf8("TrgMuteBut"));

        gridLayout_3->addWidget(TrgMuteBut, 10, 0, 2, 4);

        label_17 = new QLabel(translateControl);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_3->addWidget(label_17, 10, 6, 1, 3);

        TrgUsersList = new QListWidget(translateControl);
        TrgUsersList->setObjectName(QString::fromUtf8("TrgUsersList"));

        gridLayout_3->addWidget(TrgUsersList, 11, 6, 2, 3);

        btnBtartTranslatorsChat = new QPushButton(translateControl);
        btnBtartTranslatorsChat->setObjectName(QString::fromUtf8("btnBtartTranslatorsChat"));

        gridLayout_3->addWidget(btnBtartTranslatorsChat, 12, 0, 1, 4);

        btnStartAdminChat = new QPushButton(translateControl);
        btnStartAdminChat->setObjectName(QString::fromUtf8("btnStartAdminChat"));

        gridLayout_3->addWidget(btnStartAdminChat, 12, 4, 1, 2);

        label_19 = new QLabel(translateControl);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_3->addWidget(label_19, 13, 1, 2, 8);

        showVideoButton = new QPushButton(translateControl);
        showVideoButton->setObjectName(QString::fromUtf8("showVideoButton"));

        gridLayout_3->addWidget(showVideoButton, 14, 8, 2, 1);

        VideoLvlSld = new QSlider(translateControl);
        VideoLvlSld->setObjectName(QString::fromUtf8("VideoLvlSld"));
        VideoLvlSld->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(VideoLvlSld, 15, 3, 1, 4);

        ControlTabs->addTab(translateControl, QString());

        gridLayout->addWidget(ControlTabs, 0, 0, 1, 1);

        RemoteTranslatorUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RemoteTranslatorUI);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 408, 21));
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

        ControlTabs->setCurrentIndex(1);


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
        label_13->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Self test</span></p></body></html>", 0, QApplication::UnicodeUTF8));
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
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Source volume</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Other translators:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">volume</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        TrgStatusLbl->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#008000;\"><span style=\" font-size:12pt; font-weight:600; color:#ffffff;\">Listen </span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#008000;\"><span style=\" font-size:12pt; font-weight:600; color:#ffffff;\">translators</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        chooseTransButton->setText(QApplication::translate("RemoteTranslatorUI", "Choose local", 0, QApplication::UnicodeUTF8));
        TrgMuteBut->setText(QApplication::translate("RemoteTranslatorUI", "Translators mute", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Translators</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        btnBtartTranslatorsChat->setText(QApplication::translate("RemoteTranslatorUI", "Translators Chat", 0, QApplication::UnicodeUTF8));
        btnBtartTranslatorsChat->setShortcut(QApplication::translate("RemoteTranslatorUI", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        btnStartAdminChat->setText(QApplication::translate("RemoteTranslatorUI", "Admin Chat", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Video quality</span></p></body></html>", 0, QApplication::UnicodeUTF8));
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
