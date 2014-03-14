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

ChatWriter::ChatWriter(bool isAdminChat){
    m_chat=0;
    m_IsAdminChat=isAdminChat;
}

void ChatWriter::RiseChat(){
    m_chat=new chatDialog();
    m_chat->IsAdminChat=m_IsAdminChat;
    if(m_IsAdminChat)
    m_chat->setWindowTitle(QString::fromStdWString(L"Administrator chat"));
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

static const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%X", &tstruct);

    return buf;
}

static int StringToWString(std::wstring &ws, const std::string &s)
{
    std::wstring wsTmp(s.begin(), s.end());

    ws = wsTmp;

    return 0;
}

void chatDialog::on_btnSend_clicked()
{

    if(TxtMessage->toPlainText().length()>0&&TxtMessage->toPlainText().length()<512)
    {

        std::wstring str=TxtMessage->toPlainText().toStdWString();
        TRANSLATOR.SendMessageToTranslators(str,IsAdminChat);

        if(IsAdminChat){
            wstring ui_message;
            wstring time_str;
            StringToWString(time_str,currentDateTime());
            ui_message=time_str+L": <Me> "+TxtMessage->toPlainText().toStdWString();
            TxtChat->append(QString::fromStdWString(ui_message));
        }
    }
    TxtMessage->clear();
}
