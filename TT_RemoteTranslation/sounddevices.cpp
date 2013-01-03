#include "common.h"
#include "BBTT/BB_ClientConfigMgr.h"
#include "remotetranslatorui.h"
#include "sounddevices.h"
#include "ui_sounddevices.h"
#include "Utils/BB_Exception.h"

SoundDevices::SoundDevices(QWidget *parent, vector<BB_SoundDevice>& soundDevList) :
    QDialog(parent),
    ui(new Ui::SoundDevices),
    m_soundDevList(soundDevList)
{
    ui->setupUi(this);
    setSystemDevice();
    ui->SelfTestButton->setCheckable(true);
}

SoundDevices::~SoundDevices()
{
    delete ui;
}

void SoundDevices::setSystemDevice()
{
    for (unsigned int i = 0; i < m_soundDevList.size(); ++i)
    {
        BB_SoundDevice& device = m_soundDevList[i];
        if (!device.m_isDefault)
            continue;

        if (device.m_isOutputDevice && ConfigUI.m_OutputSoundDevId.empty())
            BB_ClientConfigMgr::Instance().SetOutputSoundDevId(device.m_deviceId);

        if (!device.m_isOutputDevice && ConfigUI.m_InputSoundDevId.empty())
            BB_ClientConfigMgr::Instance().SetInputSoundDevId(device.m_deviceId);
    }

    if (ConfigUI.m_isSoundSystemWin)
        ui->WindowsStandardButton->setChecked(true);
    else
        ui->DirectSoundButton->setChecked(true);

    drawDevices();
}

void SoundDevices::drawDevices()
{
    ui->InputDevicesBox->clear();
    ui->OutputDevicesBox->clear();
    for (unsigned int i = 0; i < m_soundDevList.size(); ++i)
    {
        BB_SoundDevice& device = m_soundDevList[i];
        if ((ConfigUI.m_isSoundSystemWin && !device.m_isSoundSystemWin) ||
            (!ConfigUI.m_isSoundSystemWin && device.m_isSoundSystemWin))
            continue;

        QString device_name = _Q(device.m_deviceName.c_str());
        if (device.m_isOutputDevice)
        {
            ui->OutputDevicesBox->addItem(device_name, i);
            if (device.m_deviceId == ConfigUI.m_OutputSoundDevId)
                ui->OutputDevicesBox->setCurrentIndex(ui->OutputDevicesBox->count()-1);
        }
        else
        {
            ui->InputDevicesBox->addItem(device_name, i);
            if (device.m_deviceId == ConfigUI.m_InputSoundDevId)
                ui->InputDevicesBox->setCurrentIndex(ui->InputDevicesBox->count()-1);
        }
    }
}

void SoundDevices::on_DirectSoundButton_toggled(bool checked)
{
    if (checked)
        BB_ClientConfigMgr::Instance().SetSoundSystemWin(false);
    else
        BB_ClientConfigMgr::Instance().SetSoundSystemWin(true);

    drawDevices();
}

void SoundDevices::on_ActSDButton_accepted()
{
    int id;
    BB_SoundDevice device;

    id = ui->InputDevicesBox->itemData(ui->InputDevicesBox->currentIndex()).toInt();
    device = m_soundDevList[id];
    BB_ClientConfigMgr::Instance().SetInputSoundDevId(device.m_deviceId);

    id = ui->OutputDevicesBox->itemData(ui->OutputDevicesBox->currentIndex()).toInt();
    device = m_soundDevList[id];
    BB_ClientConfigMgr::Instance().SetOutputSoundDevId(device.m_deviceId);
    BB_ClientConfigMgr::Instance().SetSoundSystemWin(!(ui->DirectSoundButton->isChecked()));
    if (ui->SelfTestButton->isChecked())
    {
        TRY_FUNC(TRANSLATOR.StopSoundLoopbackTest());
    }
}

void SoundDevices::on_ActSDButton_rejected()
{
    if (ui->SelfTestButton->isChecked())
    {
        TRY_FUNC(TRANSLATOR.StopSoundLoopbackTest());
    }
}

void SoundDevices::on_SelfTestButton_clicked(bool checked)
{
    if (checked)
    {
        int in_id = ui->InputDevicesBox->itemData(ui->InputDevicesBox->currentIndex()).toInt();
        BB_SoundDevice in_device = m_soundDevList[in_id];
        int out_id = ui->OutputDevicesBox->itemData(ui->OutputDevicesBox->currentIndex()).toInt();
        BB_SoundDevice out_device = m_soundDevList[out_id];

        bool sound_system = !(ui->DirectSoundButton->isChecked());

        TRY_FUNC(TRANSLATOR.StartSoundLoopbackTest(in_device.m_deviceId, out_device.m_deviceId, sound_system));
    }
    else
    {
        TRY_FUNC(TRANSLATOR.StopSoundLoopbackTest());
    }
}
