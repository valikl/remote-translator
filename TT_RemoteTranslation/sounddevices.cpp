#include "common.h"
#include "BBTT/BB_ClientConfigMgr.h"
#include "remotetranslatorui.h"
#include "sounddevices.h"
#include "ui_sounddevices.h"

SoundDevices::SoundDevices(QWidget *parent, vector<BB_SoundDevice>& soundDevList) :
    QDialog(parent),
    ui(new Ui::SoundDevices),
    m_soundDevList(soundDevList)
{
    ui->setupUi(this);
    setSystemDevice();

    drawDevices();
}

SoundDevices::~SoundDevices()
{
    delete ui;
}

void SoundDevices::setSystemDevice()
{
    if (ConfigUI.m_isSoundSystemWin)
        ui->WindowsStandardButton->setChecked(true);
    else
        ui->DirectSoundButton->setChecked(true);

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
                ui->OutputDevicesBox->setCurrentIndex(i);
        }
        else
        {
            ui->InputDevicesBox->addItem(device_name, i);
            if (device.m_deviceId == ConfigUI.m_InputSoundDevId)
                ui->InputDevicesBox->setCurrentIndex(i);
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
}
