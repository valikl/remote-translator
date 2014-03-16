/********************************************************************************
** Form generated from reading UI file 'chat.ui'
**
** Created: Sun Mar 16 04:48:56 2014
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_H
#define UI_CHAT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_chatDialog
{
public:
    QTextEdit *txtMessages;
    QPlainTextEdit *txtMessage;
    QPushButton *btnSend;
    QLabel *lblHistory;
    QLabel *lblNnewMessage;

    void setupUi(QDialog *chatDialog)
    {
        if (chatDialog->objectName().isEmpty())
            chatDialog->setObjectName(QString::fromUtf8("chatDialog"));
        chatDialog->resize(263, 389);
        txtMessages = new QTextEdit(chatDialog);
        txtMessages->setObjectName(QString::fromUtf8("txtMessages"));
        txtMessages->setEnabled(true);
        txtMessages->setGeometry(QRect(10, 30, 241, 261));
        txtMessages->setReadOnly(true);
        txtMessage = new QPlainTextEdit(chatDialog);
        txtMessage->setObjectName(QString::fromUtf8("txtMessage"));
        txtMessage->setGeometry(QRect(10, 310, 171, 71));
        btnSend = new QPushButton(chatDialog);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));
        btnSend->setGeometry(QRect(190, 310, 61, 71));
        lblHistory = new QLabel(chatDialog);
        lblHistory->setObjectName(QString::fromUtf8("lblHistory"));
        lblHistory->setGeometry(QRect(10, 10, 71, 16));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        lblHistory->setFont(font);
        lblNnewMessage = new QLabel(chatDialog);
        lblNnewMessage->setObjectName(QString::fromUtf8("lblNnewMessage"));
        lblNnewMessage->setGeometry(QRect(10, 290, 111, 16));
        lblNnewMessage->setFont(font);

        retranslateUi(chatDialog);

        QMetaObject::connectSlotsByName(chatDialog);
    } // setupUi

    void retranslateUi(QDialog *chatDialog)
    {
        chatDialog->setWindowTitle(QApplication::translate("chatDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        btnSend->setText(QApplication::translate("chatDialog", "Send", 0, QApplication::UnicodeUTF8));
        lblHistory->setText(QApplication::translate("chatDialog", "History:", 0, QApplication::UnicodeUTF8));
        lblNnewMessage->setText(QApplication::translate("chatDialog", "New Message:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class chatDialog: public Ui_chatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_H
