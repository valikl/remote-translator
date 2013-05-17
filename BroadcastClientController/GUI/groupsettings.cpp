#include "groupsettings.h"
#include "common_gui.h"

GroupSettings::GroupSettings(QWidget *parent) :
    QDialog(parent)
{
    createGroupsSettings();
    setLayout();
}

void GroupSettings::createGroupsSettings()
{
    createGroupSettings(GROUP_TYPE_SOURCES, "Sources", sourcesGroup);
    createGroupSettings(GROUP_TYPE_RECEIVERS, "Receivers", receiversGroup);
    createGroupSettings(GROUP_TYPE_RESTRICTED_SERVERS, "Restricted", restrictedGroup);
}

static void addServerDetail(QString name, QString val, QGridLayout* layout, int row)
{
    QLabel* label = new QLabel(name);
    QLineEdit* server_detail = new QLineEdit;
    server_detail->setText(val);
    layout->addWidget(label, row, 0);
    layout->addWidget(server_detail, row, 1);
}

void GroupSettings::createGroupSettings(GroupType type, QString box_name, QGroupBox*& group_box)
{
    BB_GroupConfig config = ConfigMgr.GetGroupConfig(type);

    group_box = new QGroupBox(box_name);

    QGridLayout* layout = new QGridLayout;

    addServerDetail("IP", QString::fromStdWString(config.m_ConnectionConfig.m_IP), layout, 0);
    addServerDetail("TCP", QString::number(config.m_ConnectionConfig.m_TCP), layout, 1);
    addServerDetail("UDP", QString::number(config.m_ConnectionConfig.m_UDP), layout, 2);
    addServerDetail("Server User", QString::fromStdWString(config.m_ConnectionConfig.m_srvUser), layout, 3);
    addServerDetail("Server User Psw", QString::fromStdWString(config.m_ConnectionConfig.m_srvUserPsw), layout, 4);
    addServerDetail("Server Psw", QString::fromStdWString(config.m_ConnectionConfig.m_srvPsw), layout, 5);
    addServerDetail("Source Path", QString::fromStdWString(config.m_ConnectionConfig.m_srcPath), layout, 6);

    QLabel* inst_num_label = new QLabel("Number of instances");
    QSpinBox* inst_num_box = new QSpinBox;
    inst_num_box->setValue(config.m_groupList.size());
    layout->addWidget(inst_num_label, 7, 0);
    layout->addWidget(inst_num_box, 7, 1);

    group_box->setLayout(layout);
}

void GroupSettings::setLayout()
{
    layout = new QGridLayout;

    GRID(layout)->addWidget(sourcesGroup, 0, 0);
    GRID(layout)->addWidget(receiversGroup, 0, 1);
    GRID(layout)->addWidget(restrictedGroup, 0, 2);

    QWidget::setLayout(layout);
}
