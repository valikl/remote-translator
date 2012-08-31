#include "common.h"
#include "BBTT/BB_ClientConfigMgr.h"
#include "remotetranslatorui.h"
#include "sounddevices.h"
#include "ui_sounddevices.h"

extern ClientConfig ConfigUI;

static void getSoundDevices(vector<BB_SoundDevice>& soundDevList)
{
    BB_SoundDevice device1, device2, device3, device4;

    device1.m_deviceName = L"in_dsound";
    device1.m_id = 0;
    device1.m_isOutputDevice = false;
    device1.m_isSoundSystemWin = false;
    soundDevList.push_back(device1);


    device2.m_deviceName = L"out_dsound";
    device2.m_id = 1;
    device2.m_isOutputDevice = true;
    device2.m_isSoundSystemWin = false;
    soundDevList.push_back(device2);

    device3.m_deviceName = L"in_winmm";
    device3.m_id = 2;
    device3.m_isOutputDevice = false;
    device3.m_isSoundSystemWin = true;
    soundDevList.push_back(device3);

    device4.m_deviceName = L"out_winmm";
    device4.m_id = 3;
    device4.m_isOutputDevice = true;
    device4.m_isSoundSystemWin = true;
    soundDevList.push_back(device4);
}

SoundDevices::SoundDevices(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoundDevices)
{
    ui->setupUi(this);
    setSystemDevice();

    getSoundDevices(m_soundDevList);
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
