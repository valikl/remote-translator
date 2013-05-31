#include "groupsettings.h"
#include "common_gui.h"

GroupSettings::GroupSettings(QWidget *parent) :
    QDialog(parent)
{
    createGroupsSettings();
    createSaveButton();
    setLayout();
}

static bool saveDetail(GroupType type, QString name, QString val)
{
    bool is_changed = false;
    ConnectionConfig config = ConfigMgr.GetGroupConfig(type).m_ConnectionConfig;

    if (name == "IP")
    {
        CHANGE_IF_NEEDED(config.m_IP, ConfigMgr.SetIP, val.toStdWString());
    }
    else if (name == "TCP")
    {
        CHANGE_IF_NEEDED(config.m_TCP, ConfigMgr.SetTCP, val.toInt());
    }
    else if (name == "UDP")
    {
        CHANGE_IF_NEEDED(config.m_UDP, ConfigMgr.SetUDP, val.toInt());
    }
    else if (name == "Server User")
    {
        CHANGE_IF_NEEDED(config.m_srvUser, ConfigMgr.SetSrvUser, val.toStdWString());
    }
    else if (name == "Server User Psw")
    {
        CHANGE_IF_NEEDED(config.m_srvUserPsw, ConfigMgr.SetSrvUserPsw, val.toStdWString());
    }
    else if (name == "Server Psw")
    {
        CHANGE_IF_NEEDED(config.m_srvPsw, ConfigMgr.SetSrvPsw, val.toStdWString());
    }
    else if (name == "Source Path")
    {
        CHANGE_IF_NEEDED(config.m_srcPath, ConfigMgr.SetPath, val.toStdWString());
    }

    return is_changed;
}

bool GroupSettings::saveGroupDetails(GroupType type)
{
    bool is_changed = false;
    GroupDetailMap& dmap = detail_map[type];
    for (GroupDetailMap::iterator it = dmap.begin(); it != dmap.end(); ++it)
    {
        QString name = it->first;
        QLineEdit* server_detail = it->second;
        is_changed |= saveDetail(type, name, server_detail->text());
    }
    return is_changed;
}

void GroupSettings::saveDetails()
{
    bool is_changed = false;
    is_changed |= saveGroupDetails(GROUP_TYPE_SOURCES);
    is_changed |= saveGroupDetails(GROUP_TYPE_RECEIVERS);
    is_changed |= saveGroupDetails(GROUP_TYPE_RESTRICTED_SERVERS);

    if (is_changed)
        ConfigMgr.saveConfig();

    accept();
}

void GroupSettings::createSaveButton()
{
    saveButton = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(saveButton, SIGNAL(accepted()), this, SLOT(saveDetails()));
    connect(saveButton, SIGNAL(rejected()), this, SLOT(reject()));
}

void GroupSettings::createGroupsSettings()
{
    createGroupSettings(GROUP_TYPE_SOURCES, "Sources", sourcesGroup);
    createGroupSettings(GROUP_TYPE_RECEIVERS, "Receivers", receiversGroup);
    createGroupSettings(GROUP_TYPE_RESTRICTED_SERVERS, "Restricted", restrictedGroup);
}

static void addServerDetail(QString name, QString val, QGridLayout* layout, int row, GroupDetailMap& dmap)
{
    QLabel* label = new QLabel(name);
    QLineEdit* server_detail = new QLineEdit;
    server_detail->setText(val);
    layout->addWidget(label, row, 0);
    layout->addWidget(server_detail, row, 1);
    dmap[name] = server_detail;
}

void GroupSettings::createGroupSettings(GroupType type, QString box_name, QGroupBox*& group_box)
{
    BB_GroupConfig group_config = ConfigMgr.GetGroupConfig(type);
    ConnectionConfig config = group_config.m_ConnectionConfig;
    group_box = new QGroupBox(box_name);
    QGridLayout* layout = new QGridLayout;

    GroupDetailMap& dmap = detail_map[type];

    addServerDetail("IP", QString::fromStdWString(config.m_IP), layout, 0, dmap);
    addServerDetail("TCP", QString::number(config.m_TCP), layout, 1, dmap);
    addServerDetail("UDP", QString::number(config.m_UDP), layout, 2, dmap);
    addServerDetail("Server User", QString::fromStdWString(config.m_srvUser), layout, 3, dmap);
    addServerDetail("Server User Psw", QString::fromStdWString(config.m_srvUserPsw), layout, 4, dmap);
    addServerDetail("Server Psw", QString::fromStdWString(config.m_srvPsw), layout, 5, dmap);
    addServerDetail("Source Path", QString::fromStdWString(config.m_srcPath), layout, 6, dmap);

    QLabel* inst_num_label = new QLabel("Number of instances");
    QSpinBox* inst_num_box = new QSpinBox;
    inst_num_box->setValue(group_config.m_groupList.size());
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
    GRID(layout)->addWidget(saveButton, 1, 0);

    QWidget::setLayout(layout);
}
