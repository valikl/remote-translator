#include "instsettings.h"
#include "common_gui.h"
#include <map>

using namespace std;

InstSettings::InstSettings(QWidget *parent) :
    QDialog(parent)
{
    createInstsSettings();
    setLayout();
}

void InstSettings::createInstsSettings()
{
    createGroupInstsSettings(GROUP_TYPE_SOURCES, "Sources", sourcesGroup);
    createGroupInstsSettings(GROUP_TYPE_RECEIVERS, "Receivers", receiversGroup);
    createGroupInstsSettings(GROUP_TYPE_RESTRICTED_SERVERS, "Restricted", restrictedGroup);
}

static void addInstDetail(QString name, QString val, QGridLayout* layout, int row)
{
    QLabel* label = new QLabel(name);
    QLineEdit* server_detail = new QLineEdit;
    server_detail->setText(val);
    layout->addWidget(label, row, 0);
    layout->addWidget(server_detail, row, 1);
}

void InstSettings::createGroupInstsSettings(GroupType type, QString box_name, QGroupBox*& group_box)
{
    BB_GroupConfig config = ConfigMgr.GetGroupConfig(type);

    group_box = new QGroupBox(box_name);

    QGridLayout* layout = new QGridLayout;

    int i = 0;
    map<std::wstring, BB_GroupElementConfig>::iterator it;
    for (it = config.m_groupList.begin(); it != config.m_groupList.end(); ++it)
    {
        QGroupBox* inst_box = new QGroupBox;
        QGridLayout* inst_layout = new QGridLayout;

        BB_GroupElementConfig& inst = it->second;
        addInstDetail("Channel source", QString::fromStdWString(inst.m_name), inst_layout, 0);
        addInstDetail("Nick name", QString::fromStdWString(inst.m_nickName), inst_layout, 1);
        addInstDetail("Channel name", QString::fromStdWString(inst.m_channelName), inst_layout, 2);

        QLabel* sound_card_label = new QLabel("Sound Card");
        QComboBox* sound_card = new QComboBox;
        inst_layout->addWidget(sound_card_label, 3, 0);
        inst_layout->addWidget(sound_card, 3, 1);

        inst_box->setLayout(inst_layout);
        layout->addWidget(inst_box);
    }

    group_box->setLayout(layout);
}

void InstSettings::setLayout()
{
    layout = new QGridLayout;

    GRID(layout)->addWidget(sourcesGroup, 0, 0);
    GRID(layout)->addWidget(receiversGroup, 0, 1);
    GRID(layout)->addWidget(restrictedGroup, 0, 2);

    QWidget::setLayout(layout);
}
