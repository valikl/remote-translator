#include "common.h"
#include "BBTT/BB_ClientConfigMgr.h"
#include "remotetranslatorui.h"
#include "manconnect.h"
#include "ui_manconnect.h"

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
}

ManConnect::~ManConnect()
{
    delete ui;
}

void ManConnect::on_ConnectAccept_accepted()
{
    // Accept server data
    BB_ClientConfigMgr::Instance().SetIP(ui->ServerIP->text().toStdWString());
    BB_ClientConfigMgr::Instance().SetSrvPsw(ui->ServerPassword->text().toStdWString());
    BB_ClientConfigMgr::Instance().SetTCP(ui->TcpPort->text().toInt());
    BB_ClientConfigMgr::Instance().SetUDP(ui->UdpPort->text().toInt());

    // Accept user data
    BB_ClientConfigMgr::Instance().SetSrvUser(ui->UserName->text().toStdWString());
    BB_ClientConfigMgr::Instance().SetSrvUserPsw(ui->UserPassword->text().toStdWString());
    BB_ClientConfigMgr::Instance().SetNickName(ui->NickName->text().toStdWString());
}
