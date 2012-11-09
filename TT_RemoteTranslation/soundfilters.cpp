#include "BBTT/BB_ClientConfigMgr.h"
#include "BBTT/BB_Instance.h"
#include "remotetranslatorui.h"
#include "soundfilters.h"
#include "ui_soundfilters.h"
#include "Utils/BB_Exception.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>


SoundFilters::SoundFilters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoundFilters)
{
    ui->setupUi(this);


    //Setting up default values for AGC filter
    ui->AGCDecLvl->setMaximum(0);
    ui->AGCDecLvl->setMinimum(-80);
    ui->AGCDecLvl->setValue(ConfigUI.m_AGC.m_maxDecrement);

    ui->AGCGainLvl->setMaximum(32000);
    ui->AGCGainLvl->setMinimum(0);
    ui->AGCGainLvl->setValue(ConfigUI.m_AGC.m_gainLevel);

    ui->AGCMaxGain->setMaximum(10);
    ui->AGCMaxGain->setMinimum(-10);
    ui->AGCMaxGain->setValue(ConfigUI.m_AGC.m_maxGain);

    ui->AGCIncLvl->setMaximum(80);
    ui->AGCIncLvl->setMinimum(0);
    ui->AGCIncLvl->setValue(ConfigUI.m_AGC.m_maxIncrement);

    ui->AGCEn->setChecked(ConfigUI.m_AGC.m_enable);

    //Setting up Noise acitivation level filter
    //to merge with Dima
    ui->VoiceActLvl->setMinimum(0);
    ui->VoiceActLvl->setMaximum(20);
    ui->VoiceActLvl->setValue(ConfigUI.m_VoiceActivationLevel);

    ui->DenoiseEn->setChecked(ConfigUI.m_noiseCancel);
    ui->EchoEn->setChecked(ConfigUI.m_echoCancel);
    ui->VoiceActEn->setChecked(ConfigUI.m_EnableVoiceActivation);

}

SoundFilters::~SoundFilters()
{
    delete ui;
}

void SoundFilters::on_FiltersOK_accepted()
{
    AGC AGC_tmp;
    AGC_tmp.m_enable = ui->AGCEn->isChecked();
    AGC_tmp.m_gainLevel = ui->AGCGainLvl->value();
    AGC_tmp.m_maxDecrement = ui->AGCDecLvl->value();
    AGC_tmp.m_maxGain = ui->AGCMaxGain->value();
    AGC_tmp.m_maxIncrement = ui->AGCIncLvl->value();

    BB_ClientConfigMgr::Instance().SetAGC(AGC_tmp);
    BB_ClientConfigMgr::Instance().SetEchoCancel(ui->EchoEn->isChecked());
    BB_ClientConfigMgr::Instance().SetNoiseCancel(ui->DenoiseEn->isChecked());
    BB_ClientConfigMgr::Instance().SetVoiceActivationLevel(ui->VoiceActLvl->value());
    BB_ClientConfigMgr::Instance().SetEnableVoiceActivation(ui->VoiceActEn->isChecked());

    //To add Noise activation functions
    //Enable all activated filters
    TRY_FUNC(TRANSLATOR.SetAGCEnable(ConfigUI.m_AGC.m_enable, &(ConfigUI.m_AGC)));
    TRY_FUNC(TRANSLATOR.EnableEchoCancellation(ConfigUI.m_echoCancel));
    TRY_FUNC(TRANSLATOR.EnableDenoising(ConfigUI.m_noiseCancel));
    TRY_FUNC(TRANSLATOR.EnableVoiceActivation(ConfigUI.m_EnableVoiceActivation, ConfigUI.m_VoiceActivationLevel));
}
