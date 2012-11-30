#include "common.h"
#include "BBTT/BB_ClientConfigMgr.h"
#include "remotetranslatorui.h"
#include "manconnect.h"
#include "ui_manconnect.h"

#define CHANGE_IF_NEEDED(getval, setval, val, is_changed) \
if ((getval) != (val)) \
{ \
    setval(val); \
    is_changed = true; \
}

ManConnect::ManConnect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManConnect)
{
    ui->setupUi(this);

    // Server data
    ui->ServerIP->setText(QString::fromStdWString(ConfigUI.m_IP));
    ui->ServerPassword->setText(QString::fromStdWString(ConfigUI.m_srvPsw));
    ui->TcpPort->setText(QString::number(ConfigUI.m_TCP));
    ui->UdpPort->setText(QString::number(ConfigUI.m_UDP));

    // User data
    ui->UserName->setText(QString::fromStdWString(ConfigUI.m_srvUser));
    ui->UserPassword->setText(QString::fromStdWString(ConfigUI.m_srvUserPsw));
    ui->NickName->setText(QString::fromStdWString(ConfigUI.m_NickName));

    connect(this, SIGNAL(configChanged()), this->parent(), SLOT(changeMainConfig()));
}

ManConnect::~ManConnect()
{
    delete ui;
}

void ManConnect::on_ConnectAccept_accepted()
{
    bool is_changed = false;

    // Accept server data
    CHANGE_IF_NEEDED(ConfigUI.m_IP, BB_ClientConfigMgr::Instance().SetIP, ui->ServerIP->text().toStdWString(), is_changed);
    CHANGE_IF_NEEDED(ConfigUI.m_srvPsw, BB_ClientConfigMgr::Instance().SetSrvPsw, ui->ServerPassword->text().toStdWString(), is_changed);
    CHANGE_IF_NEEDED(ConfigUI.m_TCP, BB_ClientConfigMgr::Instance().SetTCP, ui->TcpPort->text().toInt(), is_changed);
    CHANGE_IF_NEEDED(ConfigUI.m_UDP, BB_ClientConfigMgr::Instance().SetUDP, ui->UdpPort->text().toInt(), is_changed);

    // Accept user data
    CHANGE_IF_NEEDED(ConfigUI.m_srvUser, BB_ClientConfigMgr::Instance().SetSrvUser, ui->UserName->text().toStdWString(), is_changed);
    CHANGE_IF_NEEDED(ConfigUI.m_srvUserPsw, BB_ClientConfigMgr::Instance().SetSrvUserPsw, ui->UserPassword->text().toStdWString(), is_changed);
    CHANGE_IF_NEEDED(ConfigUI.m_NickName, BB_ClientConfigMgr::Instance().SetNickName, ui->NickName->text().toStdWString(), is_changed);

    if (is_changed)
        emit configChanged();
}
