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
}

void SoundDevices::drawDevices()
{
    for (unsigned int i = 0; i < m_soundDevList.size(); ++i)
    {
        BB_SoundDevice& device = m_soundDevList[i];
        if ((ConfigUI.m_isSoundSystemWin && !device.m_isSoundSystemWin) ||
            (!ConfigUI.m_isSoundSystemWin && device.m_isSoundSystemWin))
            continue;

        QString device_name = _Q(device.m_deviceName.c_str());
        if (device.m_isOutputDevice)
            ui->OutputDevicesBox->addItem(device_name, i);
        else
            ui->InputDevicesBox->addItem(device_name, i);
    }
}
