#include "instsettings.h"
#include "common_gui.h"
#include <map>

using namespace std;

#define CHANGE_IF_NEEDED(getval, setval, val)   \
if ((getval) != (val))                          \
{                                               \
    setval(type, inst_name, val);               \
    is_changed = true;                          \
}

InstSettings::InstSettings(QWidget *parent) :
    QDialog(parent)
{
    createInstsSettings();
    createSaveButton();
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

static void addTextLine(QString name, QString val, QGridLayout* layout, int row, InstDetailMap& dmap)
{
    QLabel* label = new QLabel(name);
    QLineEdit* server_detail = new QLineEdit;
    server_detail->setText(val);
    layout->addWidget(label, row, 0);
    layout->addWidget(server_detail, row, 1);
    dmap[name] = server_detail;
}

static void addSoundDevBox(QString name, bool is_out, vector<BB_SoundDevice>& sound_devices,
                           BB_GroupElementConfig& inst, QGridLayout* inst_layout, int row, InstDetailMap& dmap)
{
    QLabel* box_label = new QLabel(name);
    QComboBox* box = new QComboBox;
    box->clear();
    wstring dev_id = is_out ? inst.m_OutputSoundDevId : inst.m_InputSoundDevId;
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
        if (device.m_deviceId == dev_id)
            box->setCurrentIndex(box->count()-1);
    }
    inst_layout->addWidget(box_label, row, 0);
    inst_layout->addWidget(box, row, 1);
    dmap[name] = box;
}

static void addSliderBox(QString name, int val, int min, int max, QGridLayout* inst_layout, int row, InstDetailMap& dmap)
{
    QLabel* slider_label = new QLabel(name);
    QSlider* slider = new QSlider;
    slider->setEnabled(true);
    slider->setRange(min, max);
    slider->setValue(val);
    slider->setOrientation(Qt::Horizontal);
    inst_layout->addWidget(slider_label, row, 0);
    inst_layout->addWidget(slider, row, 1);
    dmap[name] = slider;
}

static void addCheckBox(QString name, bool checked, QGridLayout* inst_layout, int row, InstDetailMap& dmap)
{
    QLabel* box_label = new QLabel(name);
    QCheckBox* box = new QCheckBox;
    box->setChecked(checked);
    inst_layout->addWidget(box_label, row, 0);
    inst_layout->addWidget(box, row, 1);
    dmap[name] = box;
}

void InstSettings::createGroupInstsSettings(GroupType type, QString box_name, QGroupBox*& group_box)
{
    BB_GroupConfig config = ConfigMgr.GetGroupConfig(type);
    std::vector<BB_SoundDevice> sound_devices;
    getSoundDevices(type, sound_devices);

    group_box = new QGroupBox(box_name);
    QGridLayout* layout = new QGridLayout;

    InstsDetailMap& inst_detail_map = detail_map[type];

    map<std::wstring, BB_GroupElementConfig>::iterator it;
    for (it = config.m_groupList.begin(); it != config.m_groupList.end(); ++it)
    {
        BB_GroupElementConfig& inst = it->second;
        QString iname = QString::fromStdWString(inst.m_name);
        InstSettingsView* iview = new InstSettingsView(iname, type);
        layout->addWidget(iview);
        layout->setAlignment(iview, Qt::AlignTop);
        inst_detail_map[inst.m_name] = iview->getDetailMap();
    }

    group_box->setLayout(layout);
}

void InstSettings::setLayout()
{
    layout = new QGridLayout;

    GRID(layout)->addWidget(sourcesGroup, 0, 0);
    GRID(layout)->addWidget(receiversGroup, 0, 1);
    GRID(layout)->addWidget(restrictedGroup, 0, 2);
    GRID(layout)->addWidget(saveButton, 1, 0);

    QWidget::setLayout(layout);
}

static bool saveDetail(GroupType type, wstring inst_name, QString name, void* container)
{
    bool is_changed = false;
    BB_GroupElementConfig inst = ConfigMgr.GetGroupElementConfig(type, inst_name);

    if (name == "Channel source")
    {
        QString val = ((QLineEdit*)container)->text();
        CHANGE_IF_NEEDED(inst.m_name, ConfigMgr.SetGroupElementName, val.toStdWString());
    }
    else if (name == "Nick name")
    {
        QString val = ((QLineEdit*)container)->text();
        CHANGE_IF_NEEDED(inst.m_nickName, ConfigMgr.SetGroupElementNickName, val.toStdWString());
    }
    else if (name == "Channel name")
    {
        QString val = ((QLineEdit*)container)->text();
        CHANGE_IF_NEEDED(inst.m_channelName, ConfigMgr.SetGroupElementChannel, val.toStdWString());
    }
    else if (name == "Input device")
    {
        QString val = ((QComboBox*)container)->currentText();
        CHANGE_IF_NEEDED(inst.m_InputSoundDevId, ConfigMgr.SetGroupElementInputSoundDevId, val.toStdWString());
    }
    else if (name == "Output device")
    {
        QString val = ((QComboBox*)container)->currentText();
        CHANGE_IF_NEEDED(inst.m_OutputSoundDevId, ConfigMgr.SetGroupElementOutputSoundDevId, val.toStdWString());
    }
    else if (name == "Volume level")
    {
        int val = ((QSlider*)container)->value();
        CHANGE_IF_NEEDED(inst.m_SrcVolumeLevel, ConfigMgr.SetGroupElementSrcVolumeLevel, val);
    }
    else if (name == "Gain level")
    {
        int val = ((QSlider*)container)->value();
        CHANGE_IF_NEEDED(inst.m_MicGainLevel, ConfigMgr.SetGroupElementMicGainLevel, val);
    }
    else if (name == "Enable denoising")
    {
        Qt::CheckState val = ((QCheckBox*)container)->checkState();
        CHANGE_IF_NEEDED(inst.m_noiseCancel, ConfigMgr.SetGroupElementNoiseCancel, val == Qt::Checked);
    }
    else if (name == "Enable echo cancellation")
    {
        Qt::CheckState val = ((QCheckBox*)container)->checkState();
        CHANGE_IF_NEEDED(inst.m_echoCancel, ConfigMgr.SetGroupElementEchoCancel, val == Qt::Checked);
    }
    else if (name == "Standard Windows")
    {
        Qt::CheckState val = ((QCheckBox*)container)->checkState();
        CHANGE_IF_NEEDED(inst.m_isSoundSystemWin, ConfigMgr.SetGroupElementSoundSystemWin, val == Qt::Checked);
    }

    return is_changed;
}

static bool saveInstDetails(GroupType type, wstring inst_name, InstDetailMap& dmap)
{
    bool is_changed = false;

    InstDetailMap::iterator it;
    for (it = dmap.begin(); it != dmap.end(); ++it)
    {
        QString name = it->first;
        void* container = it->second;
        is_changed |= saveDetail(type, inst_name, name, container);
    }

    return is_changed;
}

bool InstSettings::saveGroupInstsDetails(GroupType type)
{
    bool is_changed = false;
    BB_GroupConfig config = ConfigMgr.GetGroupConfig(type);
    InstsDetailMap& inst_detail_map = detail_map[type];

    map<std::wstring, BB_GroupElementConfig>::iterator it;
    for (it = config.m_groupList.begin(); it != config.m_groupList.end(); ++it)
    {
        BB_GroupElementConfig& inst = it->second;
        InstDetailMap& dmap = inst_detail_map[inst.m_name];
        is_changed |= saveInstDetails(type, inst.m_name, dmap);
    }

    return is_changed;
}

void InstSettings::saveDetails()
{
    bool is_changed = false;
    is_changed |= saveGroupInstsDetails(GROUP_TYPE_SOURCES);
    is_changed |= saveGroupInstsDetails(GROUP_TYPE_RECEIVERS);
    is_changed |= saveGroupInstsDetails(GROUP_TYPE_RESTRICTED_SERVERS);

    if (is_changed)
        ConfigMgr.saveConfig();

    accept();
}

void InstSettings::createSaveButton()
{
    saveButton = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(saveButton, SIGNAL(accepted()), this, SLOT(saveDetails()));
    connect(saveButton, SIGNAL(rejected()), this, SLOT(reject()));
}

void InstSettingsView::setLayout()
{
    wstring wname = getName().toStdWString();
    BB_GroupElementConfig config = ConfigMgr.GetGroupElementConfig(getType(), wname);
    std::vector<BB_SoundDevice> sound_devices;
    getSoundDevices(type, sound_devices);

    layout = new QGridLayout;

    int gainMax = 4000; /* real max: SOUND_LEVEL_MAX but it's too much */

    addTextLine("Channel source", QString::fromStdWString(config.m_name), GRID(layout), 0, dmap);
    addTextLine("Nick name", QString::fromStdWString(config.m_nickName), GRID(layout), 1, dmap);
    addTextLine("Channel name", QString::fromStdWString(config.m_channelName), GRID(layout), 2, dmap);
    addSoundDevBox("Input device", false, sound_devices, config, GRID(layout), 3, dmap);
    addSoundDevBox("Output device", true, sound_devices, config, GRID(layout), 4, dmap);
    if (type == GROUP_TYPE_RECEIVERS)
    {
        addSliderBox("Volume level", config.m_SrcVolumeLevel, SOUND_VOLUME_MIN, SOUND_VOLUME_MAX*(gainMax/SOUND_GAIN_DEFAULT), GRID(layout), 5, dmap);
    }
    else
    {
        addSliderBox("Gain level", config.m_MicGainLevel, SOUND_GAIN_MIN, gainMax, GRID(layout), 5, dmap);
        addCheckBox("Enable denoising", config.m_noiseCancel, GRID(layout), 6, dmap);
        addCheckBox("Enable echo cancellation", config.m_echoCancel, GRID(layout), 7, dmap);
        addCheckBox("Standard Windows", config.m_isSoundSystemWin, GRID(layout), 8, dmap);
    }

    QWidget::setLayout(layout);
}

bool InstSettingsView::saveDetails()
{
    return saveInstDetails(type, getName().toStdWString(), dmap);
}
