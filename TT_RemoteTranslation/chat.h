
#ifndef CHAT_H
#define CHAT_H
#include "ui_chat.h"
#include <QDialog>
#include "BBTT/IWriter.h"
#include "BBTT/BB_Translator.h"

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

public:
   ChatWriter();
   virtual void Write(wstring msg);
   void RiseChat();
   ~ChatWriter();
    chatDialog *m_chat;
private:
    void StartWindow(QString str);
};
#endif // CHAT_H
