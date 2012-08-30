#include "remotetranslatorui.h"
#include "sounddevices.h"
#include "ui_sounddevices.h"

extern ClientConfig ConfigUI;

SoundDevices::SoundDevices(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoundDevices)
{
    ui->setupUi(this);
}

SoundDevices::~SoundDevices()
{
    delete ui;
}
