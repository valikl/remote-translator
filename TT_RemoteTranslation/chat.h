
#ifndef CHAT_H
#define CHAT_H
#include "ui_chat.h"
#include <QDialog>
#include "BBTT/IWriter.h"
#include "BBTT/BB_Translator.h"
#include <time.h>

#define TRANSLATOR (BB_Translator::Instance())

using namespace std;

namespace Ui {
class chatDialog;
}
class ChatWriter;
class chatDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit chatDialog(QWidget *parent = 0);
    ~chatDialog();
    QPlainTextEdit *TxtMessage;
    QTextEdit *TxtChat;
    ChatWriter  *writer;
    bool IsAdminChat;
private slots:
    void on_btnSend_clicked();

private:
    Ui::chatDialog *ui;
};

class ChatWriter : public QObject,public IWriter
{
Q_OBJECT

signals:
    void StartChat(QString str);
    void ActivateChat();

public:
   ChatWriter(bool isAdminChat);
   virtual void Write(wstring msg);
   void RiseChat();
   ~ChatWriter();
    chatDialog *m_chat;
    void ShowUpChatWindow();
private:
    void StartWindow(QString str);
    bool m_IsAdminChat;
};
#endif // CHAT_H
