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

static void getSoundDevices(GroupType type, std::vector<BB_SoundDevice>& sound_devices)
{
    switch (type)
    {
    case GROUP_TYPE_SOURCES:
        sound_devices = SourcesMgr.getSoundDevices();
        break;
    case GROUP_TYPE_RESTRICTED_SERVERS:
        sound_devices = RestrictedMgr.getSoundDevices();
        break;
    default:
        sound_devices = ReceiversMgr.getSoundDevices();
        break;
    }
}

static void addInstDetail(QString name, QString val, QGridLayout* layout, int row)
{
    QLabel* label = new QLabel(name);
    QLineEdit* server_detail = new QLineEdit;
    server_detail->setText(val);
    layout->addWidget(label, row, 0);
    layout->addWidget(server_detail, row, 1);
}

static void addSoundDevBox(QString box_name, bool is_out, vector<BB_SoundDevice>& sound_devices,
                           BB_GroupElementConfig& inst, QGridLayout* inst_layout, int row)
{
    QLabel* box_label = new QLabel(box_name);
    QComboBox* box = new QComboBox;
    box->clear();
    for (unsigned int i = 0; i < sound_devices.size(); ++i)
    {
        BB_SoundDevice& device = sound_devices[i];
        if ((inst.m_isSoundSystemWin && !device.m_isSoundSystemWin) ||
            (!inst.m_isSoundSystemWin && device.m_isSoundSystemWin))
            continue;
        if ((is_out && !device.m_isOutputDevice) || (!is_out && device.m_isOutputDevice))
            continue;
        QString device_name = QString::fromStdWString(device.m_deviceName.c_str());
        box->addItem(device_name, i);
        if (device.m_deviceId == inst.m_InputSoundDevId)
            box->setCurrentIndex(box->count()-1);
    }
    inst_layout->addWidget(box_label, row, 0);
    inst_layout->addWidget(box, row, 1);
}

static void addSpinBox(QString box_name, int val, QGridLayout* inst_layout, int row)
{
    QLabel* box_label = new QLabel(box_name);
    QSpinBox* box = new QSpinBox;
    box->setValue(val);
    inst_layout->addWidget(box_label, row, 0);
    inst_layout->addWidget(box, row, 1);
}

static void addCheckBox(QString box_name, bool checked, QGridLayout* inst_layout, int row)
{
    QLabel* box_label = new QLabel(box_name);
    QCheckBox* box = new QCheckBox;
    box->setChecked(checked);
    inst_layout->addWidget(box_label, row, 0);
    inst_layout->addWidget(box, row, 1);
}

void InstSettings::createGroupInstsSettings(GroupType type, QString box_name, QGroupBox*& group_box)
{
    BB_GroupConfig config = ConfigMgr.GetGroupConfig(type);
    std::vector<BB_SoundDevice> sound_devices;
    getSoundDevices(type, sound_devices);

    group_box = new QGroupBox(box_name);

    QGridLayout* layout = new QGridLayout;

    map<std::wstring, BB_GroupElementConfig>::iterator it;
    for (it = config.m_groupList.begin(); it != config.m_groupList.end(); ++it)
    {
        QGroupBox* inst_box = new QGroupBox;
        QGridLayout* inst_layout = new QGridLayout;
        BB_GroupElementConfig& inst = it->second;

        addInstDetail("Channel source", QString::fromStdWString(inst.m_name), inst_layout, 0);
        addInstDetail("Nick name", QString::fromStdWString(inst.m_nickName), inst_layout, 1);
        addInstDetail("Channel name", QString::fromStdWString(inst.m_channelName), inst_layout, 2);
        addSoundDevBox("Input device", false, sound_devices, inst, inst_layout, 3);
        addSoundDevBox("Output device", true, sound_devices, inst, inst_layout, 4);
        addSpinBox("Gain level", inst.m_MicGainLevel, inst_layout, 5);
        addCheckBox("Enable denoising", inst.m_noiseCancel, inst_layout, 6);
        addCheckBox("Enable echo cancellation", inst.m_echoCancel, inst_layout, 7);
        addCheckBox("Standard Windows", inst.m_isSoundSystemWin, inst_layout, 8);

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
