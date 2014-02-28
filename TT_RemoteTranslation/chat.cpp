#include "chat.h"


chatDialog::chatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatDialog)
{
    ui->setupUi(this);
    TxtMessage=ui->txtMessage;
    TxtChat =ui->txtMessages;
    this->writer=0;
    this->setWindowFlags(this->windowFlags() | Qt::WindowMinimizeButtonHint);
   // TRANSLATOR.StartTranslatorsChat(writer);
}

chatDialog::~chatDialog()
{

    //TRANSLATOR.StopTranslatorsChat();
    if(writer != 0){
        writer->m_chat = 0;
    }
    delete ui;
  //  delete writer;
}

ChatWriter::ChatWriter(){
    m_chat=0;
}

void ChatWriter::RiseChat(){
    m_chat=new chatDialog();
    m_chat->show();
    m_chat->writer=this;
}

void ChatWriter::ShowUpChatWindow(){
    m_chat->setWindowState(m_chat->windowState() & ~Qt::WindowMinimized | Qt::WindowActive);
    m_chat->show();
    m_chat->raise();
    m_chat->activateWindow();
}

ChatWriter::~ChatWriter(){

}

void ChatWriter::StartWindow(QString str){
     emit StartChat(str);
}

void ChatWriter::Write(std::wstring msg)
{
    QString qmsg=QString::fromStdWString(msg);
    if(m_chat==0||m_chat->isHidden())
    {
        StartWindow(qmsg);
    }
    if(m_chat!=0&&m_chat->TxtChat!=0)
    {
       if(m_chat->isMinimized()){
            emit ActivateChat();
       }
        m_chat->TxtChat->append(qmsg);
    }

}



void chatDialog::on_btnSend_clicked()
{

    if(TxtMessage->toPlainText().length()>0&&TxtMessage->toPlainText().length()<512)
    {

        std::wstring str=TxtMessage->toPlainText().toStdWString();
        TRANSLATOR.SendMessageToTranslators(str);
    }
    TxtMessage->clear();
}
