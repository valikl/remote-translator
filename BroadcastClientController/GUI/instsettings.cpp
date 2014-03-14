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

static void addLabel(QString name, QGridLayout* layout, int row, int col, bool is_bold)
{
    QLabel* label = new QLabel(name);
    QFont font;
    font.setBold(true);
    label->setFont(font);
    layout->addWidget(label, row, col);
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

static void showSoundDevList(QComboBox* box, bool is_out, bool is_win,
                             vector<BB_SoundDevice>& sound_devices, wstring curr_dev_id)
{
    box->clear();
    for (unsigned int i = 0; i < sound_devices.size(); ++i)
    {
        BB_SoundDevice& device = sound_devices[i];
        if ((is_win && !device.m_isSoundSystemWin) || (!is_win && device.m_isSoundSystemWin))
            continue;
        if ((is_out && !device.m_isOutputDevice) || (!is_out && device.m_isOutputDevice))
            continue;
        QString device_name = QString::fromStdWString(device.m_deviceName.c_str());
        box->addItem(device_name, i);
        if (device.m_deviceId == curr_dev_id)
            box->setCurrentIndex(box->count()-1);
    }
}

static void addSoundDevBox(QString name, bool is_out, vector<BB_SoundDevice>& sound_devices,
                           BB_GroupElementConfig& inst, QGridLayout* inst_layout, int row, InstDetailMap& dmap)
{
    QLabel* box_label = new QLabel(name);
    QComboBox* box = new QComboBox;
    wstring curr_dev_id = is_out ? inst.m_OutputSoundDevId : inst.m_InputSoundDevId;
    showSoundDevList(box, is_out, inst.m_isSoundSystemWin, sound_devices, curr_dev_id);
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

static void addCheckBox(QString name, bool checked, QGridLayout* inst_layout, int row, int col, InstDetailMap& dmap)
{
    QCheckBox* box = new QCheckBox;
    box->setText(name);
    box->setChecked(checked);
    inst_layout->addWidget(box, row, col);
    dmap[name] = box;
}

static void addSpinBox(QString name, int val, QGridLayout* inst_layout, int row, int col, InstDetailMap& dmap)
{
    QGroupBox* spin_box = new QGroupBox;
    QGridLayout* spin_layout = new QGridLayout;

    QLabel* box_label = new QLabel(name);
    QSpinBox* box = new QSpinBox;
    box->setValue(val);

    spin_layout->setSpacing(0);
    spin_layout->addWidget(box_label, 0, 0);
    spin_layout->addWidget(box, 0, 1);
    spin_box->setStyleSheet("QGroupBox { border-style: inset; border-width: 0px; }");
    spin_box->setLayout(spin_layout);

    inst_layout->addWidget(spin_box, row, col);

    dmap[name] = box;
}

static void addRadioButtonBox(QString name, bool checked, QGridLayout* inst_layout, int row, int col, InstDetailMap& dmap)
{
    QRadioButton* button = new QRadioButton;
    button->setText(name);
    button->setChecked(checked);
    inst_layout->addWidget(button, row, col);
    dmap[name] = button;
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

/*************** Update functions ******************/

static void updateNickName(GroupType type, wstring inst_name, wstring nick_name)
{
    switch (type)
    {
    case GROUP_TYPE_SOURCES:
        TRY_FUNC(SourcesMgr.UpdateNickName(inst_name, nick_name));
        break;
    case GROUP_TYPE_RESTRICTED_SERVERS:
        TRY_FUNC(RestrictedMgr.UpdateNickName(inst_name, nick_name));
        break;
    default:
        TRY_FUNC(ReceiversMgr.UpdateNickName(inst_name, nick_name));
        break;
    }
}

static void updateVolumeLevel(GroupType type, wstring inst_name, int volumeLevel)
{
    TRY_FUNC(ReceiversMgr.UpdateVolumeLevel(inst_name, volumeLevel));
}

static void updateMicrophoneGainLevel(GroupType type, wstring inst_name, int gainLevel)
{
    BB_GroupMgrSource& mgr = type == GROUP_TYPE_SOURCES ? SourcesMgr : RestrictedMgr;
    TRY_FUNC(mgr.UpdateMicrophoneGainLevel(inst_name, gainLevel));
}

static void enableDenoising(GroupType type, wstring inst_name, bool bEnable)
{
    BB_GroupMgrSource& mgr = type == GROUP_TYPE_SOURCES ? SourcesMgr : RestrictedMgr;
    TRY_FUNC(mgr.EnableDenoising(inst_name, bEnable));
}

static void enableEchoCancellation(GroupType type, wstring inst_name, bool bEnable)
{
    BB_GroupMgrSource& mgr = type == GROUP_TYPE_SOURCES ? SourcesMgr : RestrictedMgr;
    TRY_FUNC(mgr.EnableEchoCancellation(inst_name, bEnable));
}

static void updateSoundDev(GroupType type, wstring inst_name, wstring id, bool isInput)
{
    BB_GroupElementConfig inst = ConfigMgr.GetGroupElementConfig(type, inst_name);

    switch (type)
    {
    case GROUP_TYPE_SOURCES:
        TRY_FUNC(SourcesMgr.UpdateSoundDev(inst_name, id, inst.m_isSoundSystemWin, isInput));
        break;
    case GROUP_TYPE_RESTRICTED_SERVERS:
        TRY_FUNC(RestrictedMgr.UpdateSoundDev(inst_name, id, inst.m_isSoundSystemWin, isInput));
        break;
    default:
        TRY_FUNC(ReceiversMgr.UpdateSoundDev(inst_name, id, inst.m_isSoundSystemWin, isInput));
        break;
    }
}

static void updateInputSoundDev(GroupType type, wstring inst_name, wstring id)
{
    updateSoundDev(type, inst_name, id, true);
}

static void updateOutputSoundDev(GroupType type, wstring inst_name, wstring id)
{
    updateSoundDev(type, inst_name, id, false);
}

/*************** Save instance details functions ******************/

static bool saveDetail(GroupType type, wstring inst_name, QString name, void* container, InstDetailMap& dmap)
{
    bool is_changed = false;
    BB_GroupElementConfig inst = ConfigMgr.GetGroupElementConfig(type, inst_name);

    if (name == "Nick name")
    {
        QString val = ((QLineEdit*)container)->text();
        CHANGE_IF_NEEDED(inst.m_nickName, updateNickName, val.toStdWString());
    }
    else if (name == "Input device")
    {
        bool is_win = ((QRadioButton*)dmap["Windows Standard"])->isChecked();
        CHANGE_IF_NEEDED(inst.m_isSoundSystemWin, ConfigMgr.SetGroupElementSoundSystemWin, is_win);

        QString val = ((QComboBox*)container)->currentText();
        CHANGE_IF_NEEDED(inst.m_InputSoundDevId, updateInputSoundDev, val.toStdWString());
    }
    else if (name == "Output device")
    {
        bool is_win = ((QRadioButton*)dmap["Windows Standard"])->isChecked();
        CHANGE_IF_NEEDED(inst.m_isSoundSystemWin, ConfigMgr.SetGroupElementSoundSystemWin, is_win);

        QString val = ((QComboBox*)container)->currentText();
        CHANGE_IF_NEEDED(inst.m_OutputSoundDevId, updateOutputSoundDev, val.toStdWString());
    }
    else if (name == "Volume level")
    {
        int val = ((QSlider*)container)->value();
        CHANGE_IF_NEEDED(inst.m_SrcVolumeLevel, updateVolumeLevel, val);
    }
    else if (name == "Gain level")
    {
        int val = ((QSlider*)container)->value();
        CHANGE_IF_NEEDED(inst.m_MicGainLevel, updateMicrophoneGainLevel, val);
    }
    else if (name == "Enable denoising")
    {
        Qt::CheckState val = ((QCheckBox*)container)->checkState();
        CHANGE_IF_NEEDED(inst.m_noiseCancel, enableDenoising, val == Qt::Checked);
    }
    else if (name == "Enable echo cancellation")
    {
        Qt::CheckState val = ((QCheckBox*)container)->checkState();
        CHANGE_IF_NEEDED(inst.m_echoCancel, enableEchoCancellation, val == Qt::Checked);
    }
    else if (name == "Standard Windows")
    {
        bool val = ((QRadioButton*)container)->isChecked();
        CHANGE_IF_NEEDED(inst.m_isSoundSystemWin, ConfigMgr.SetGroupElementSoundSystemWin, val);
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
        is_changed |= saveDetail(type, inst_name, name, container, dmap);
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

    //  instance name
    QLabel* nameLabel = new QLabel;
    nameLabel->setText(getName());
    QFont font;
    font.setBold(true);
    nameLabel->setFont(font);
    layout->addWidget(nameLabel);

    addTextLine("Nick name", QString::fromStdWString(config.m_nickName), GRID(layout), 1, dmap);

    addSoundDevBox("Input device", false, sound_devices, config, GRID(layout), 3, dmap);
    addSoundDevBox("Output device", true, sound_devices, config, GRID(layout), 4, dmap);
    addRadioButtonBox("Sound system", !config.m_isSoundSystemWin, GRID(layout), 5, 0, dmap);
    addRadioButtonBox("Windows Standard", config.m_isSoundSystemWin, GRID(layout), 5, 1, dmap);

    if (type == GROUP_TYPE_RECEIVERS)
    {
        addSliderBox("Volume level", config.m_SrcVolumeLevel, SOUND_VOLUME_MIN, SOUND_VOLUME_MAX*(gainMax/SOUND_GAIN_DEFAULT), GRID(layout), 6, dmap);
    }
    else
    {
        addSliderBox("Gain level", config.m_MicGainLevel, SOUND_GAIN_MIN, gainMax, GRID(layout), 6, dmap);
        addCheckBox("Enable denoising", config.m_noiseCancel, GRID(layout), 7, 0, dmap);
        addCheckBox("Enable echo cancellation", config.m_echoCancel, GRID(layout), 7, 1, dmap);
        addCheckBox("Enable voice activation", config.m_EnableVoiceActivation, GRID(layout), 8, 0, dmap);
        addSpinBox("Voice activation level", config.m_VoiceActivationLevel, GRID(layout), 8, 1, dmap);
        addLabel("AGC settings:", GRID(layout), 9, 0, true);
        addCheckBox("enable", config.m_AGC.m_enable, GRID(layout), 10, 0, dmap);
        addSpinBox("gain level", config.m_AGC.m_gainLevel, GRID(layout), 11, 0, dmap);
        addSpinBox("max gain", config.m_AGC.m_maxGain, GRID(layout), 11, 1, dmap);
        addSpinBox("max increment", config.m_AGC.m_maxIncrement, GRID(layout), 12, 0, dmap);
        addSpinBox("max decrement", config.m_AGC.m_maxDecrement, GRID(layout), 12, 1, dmap);
    }

    QRadioButton* button = (QRadioButton*)dmap["Windows Standard"];
    QObject::connect(button, SIGNAL(toggled(bool)), this, SLOT(changeDevices(bool)));

    QWidget::setLayout(layout);
}

void InstSettingsView::changeDevices(bool is_win)
{
    std::vector<BB_SoundDevice> sound_devices;
    getSoundDevices(type, sound_devices);

    wstring wname = getName().toStdWString();
    BB_GroupElementConfig inst = ConfigMgr.GetGroupElementConfig(getType(), wname);

    QComboBox* in_box = (QComboBox*)dmap["Input device"];
    QComboBox* out_box = (QComboBox*)dmap["Output device"];
    showSoundDevList(in_box, false, is_win, sound_devices, inst.m_InputSoundDevId);
    showSoundDevList(out_box, true, is_win, sound_devices, inst.m_OutputSoundDevId);
}

bool InstSettingsView::saveDetails()
{
    return saveInstDetails(type, getName().toStdWString(), dmap);
}
