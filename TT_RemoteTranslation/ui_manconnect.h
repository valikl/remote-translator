/********************************************************************************
** Form generated from reading UI file 'manconnect.ui'
**
** Created: Mon Oct 15 04:06:39 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANCONNECT_H
#define UI_MANCONNECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_ManConnect
{
public:
    QDialogButtonBox *ConnectAccept;
    QLineEdit *ServerIP;
    QLabel *label;
    QLineEdit *TcpPort;
    QLabel *label_2;
    QLineEdit *UdpPort;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *UserName;
    QLabel *label_6;
    QLineEdit *ServerPassword;
    QLabel *label_7;
    QLineEdit *UserPassword;
    QLabel *label_8;
    QLineEdit *NickName;
    QLabel *label_9;

    void setupUi(QDialog *ManConnect)
    {
        if (ManConnect->objectName().isEmpty())
            ManConnect->setObjectName(QString::fromUtf8("ManConnect"));
        ManConnect->resize(430, 484);
        ConnectAccept = new QDialogButtonBox(ManConnect);
        ConnectAccept->setObjectName(QString::fromUtf8("ConnectAccept"));
        ConnectAccept->setGeometry(QRect(60, 430, 341, 32));
        ConnectAccept->setOrientation(Qt::Horizontal);
        ConnectAccept->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        ServerIP = new QLineEdit(ManConnect);
        ServerIP->setObjectName(QString::fromUtf8("ServerIP"));
        ServerIP->setGeometry(QRect(170, 30, 141, 20));
        label = new QLabel(ManConnect);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 111, 20));
        TcpPort = new QLineEdit(ManConnect);
        TcpPort->setObjectName(QString::fromUtf8("TcpPort"));
        TcpPort->setGeometry(QRect(170, 110, 140, 20));
        label_2 = new QLabel(ManConnect);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 110, 111, 20));
        UdpPort = new QLineEdit(ManConnect);
        UdpPort->setObjectName(QString::fromUtf8("UdpPort"));
        UdpPort->setGeometry(QRect(170, 150, 140, 20));
        label_3 = new QLabel(ManConnect);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 150, 111, 20));
        label_4 = new QLabel(ManConnect);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(160, 3, 111, 20));
        label_5 = new QLabel(ManConnect);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(170, 190, 111, 20));
        UserName = new QLineEdit(ManConnect);
        UserName->setObjectName(QString::fromUtf8("UserName"));
        UserName->setGeometry(QRect(160, 220, 141, 20));
        label_6 = new QLabel(ManConnect);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 220, 111, 20));
        ServerPassword = new QLineEdit(ManConnect);
        ServerPassword->setObjectName(QString::fromUtf8("ServerPassword"));
        ServerPassword->setGeometry(QRect(170, 70, 141, 20));
        label_7 = new QLabel(ManConnect);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 70, 111, 20));
        UserPassword = new QLineEdit(ManConnect);
        UserPassword->setObjectName(QString::fromUtf8("UserPassword"));
        UserPassword->setGeometry(QRect(160, 260, 141, 20));
        label_8 = new QLabel(ManConnect);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 260, 111, 20));
        NickName = new QLineEdit(ManConnect);
        NickName->setObjectName(QString::fromUtf8("NickName"));
        NickName->setGeometry(QRect(160, 300, 141, 20));
        label_9 = new QLabel(ManConnect);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 300, 111, 20));

        retranslateUi(ManConnect);
        QObject::connect(ConnectAccept, SIGNAL(accepted()), ManConnect, SLOT(accept()));
        QObject::connect(ConnectAccept, SIGNAL(rejected()), ManConnect, SLOT(reject()));

        QMetaObject::connectSlotsByName(ManConnect);
    } // setupUi

    void retranslateUi(QDialog *ManConnect)
    {
        ManConnect->setWindowTitle(QApplication::translate("ManConnect", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ManConnect", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Server IP</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ManConnect", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">TCP Port</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ManConnect", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">UDP Port</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ManConnect", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Server details</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ManConnect", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Account details</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ManConnect", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">User name</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ManConnect", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Server password</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ManConnect", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">User password</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ManConnect", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Nick name</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ManConnect: public Ui_ManConnect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANCONNECT_H
