#include "remotetranslatorui.h"
#include "sounddevices.h"
#include "soundfilters.h"
#include "manconnect.h"
#include "BBTT/BB_ClientConfigMgr.h"
#include "BBTT/Utils.h"
#include "Utils/BB_Exception.h"
#include "ui_remotetranslatorui.h"
#include <QTimer>
#include <time.h>

//Dummy function for Mic level return

static int GetMicLevel()
{
    static INT32 i,f;
    INT32 xx;
    if (i==0)
    {
        i=3;
        f=7;
    }
    i = abs(i*f);

    xx = i % 19;
    return xx;
}

RemoteTranslatorUI::RemoteTranslatorUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemoteTranslatorUI)
{
    ui->setupUi(this);
}

void RemoteTranslatorUI::initHapsMenu()
{
    // get list of happenings
    TRY_BLOCK(
        happenings = TRANSLATOR.getHappenings();
    );

    for (unsigned int i = 0; i < happenings.size(); ++i)
    {
        Happening hap = happenings[i];
        ui->HapList->addItem(QString::fromStdWString(hap.m_hapName), i);
        if (hap.m_hapName == ConfigUI.m_Happening)
            ui->HapList->setCurrentIndex(i);
    }
}

void RemoteTranslatorUI::setSliders()
{
    ui->MicGainSld->setMinimum(0);
    ui->MicGainSld->setMaximum(SOUND_GAIN_MAX);
    ui->MicGainSld->setValue(ConfigUI.m_MicGainLevel);

    ui->TrgLvlSld->setMinimum(0);
    ui->TrgLvlSld->setMaximum(SOUND_VOLUME_MAX);
    ui->TrgLvlSld->setValue(ConfigUI.m_TrgVolumeLevel);

    ui->SrcLevelSld->setMinimum(0);
    ui->SrcLevelSld->setMaximum(SOUND_VOLUME_MAX);
    ui->SrcLevelSld->setValue(ConfigUI.m_SrcVolumeLevel);

    ui->VideoLvlSld->setMinimum(0);
    ui->VideoLvlSld->setMaximum(100);
    ui->VideoLvlSld->setValue(ConfigUI.m_VideoQuality);

    ui->MicLevelInd->setMinimum(0);
    ui->MicLevelInd->setMaximum(20);
    ui->MicLevelInd->setTextVisible(false);
    ui->MicLevelInd->setValue(0);
}

void RemoteTranslatorUI::initMainConfig()
{
    //Initialize ComboBoxes
    initHapsMenu();

    // set nick name
    ui->NickName->setText(QString::fromStdWString(ConfigUI.m_NickName));
}

void RemoteTranslatorUI::changeMainConfig()
{
    initMainConfig();
}

void RemoteTranslatorUI::init()
{
    TRY_FUNC(BB_ClientConfigMgr::Instance().init(false));
    TRY_FUNC(TRANSLATOR.init());

    // init main configuration
    initMainConfig();

    // activate sound devices
    connect(ui->actionConfigure_Audio, SIGNAL(triggered()), this, SLOT(ActivateSoundDevices()));
    connect(ui->actionAudio_Filters, SIGNAL(triggered()), this, SLOT(ActivateAudioFilters()));
    connect(ui->actionTT_server_connection, SIGNAL(triggered()), this, SLOT(ActivateManConnect()));
    connect(ui->actionRestore_default_configuration, SIGNAL(triggered()), this, SLOT(RestoreDefaultConfig()));

    //Activate Audio filters
    enableAudioFilters();

    // set buttons checkable
    ui->LangConnect->setCheckable(true);
    ui->MicMuteBut->setCheckable(true);
    ui->TrgMuteBut->setCheckable(true);

    // set slider values
    setSliders();

    //Timer for progress bar
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_Timeout()));
    timer->start(100);

    // Timer for user detection
    user_timer = new QTimer(this);
    connect(user_timer, SIGNAL(timeout()), this, SLOT(on_UserTimeout()));
    user_timer->start(1000);
}

void RemoteTranslatorUI::enableAudioFilters()
{
    TRY_FUNC(TRANSLATOR.SetAGCEnable(ConfigUI.m_AGC.m_enable, &(ConfigUI.m_AGC)));
    TRY_FUNC(TRANSLATOR.EnableEchoCancellation(ConfigUI.m_echoCancel));
    TRY_FUNC(TRANSLATOR.EnableDenoising(ConfigUI.m_noiseCancel));
}

// Activate sound devices
void RemoteTranslatorUI::ActivateSoundDevices()
{
    TRY_BLOCK(
        vector<BB_SoundDevice> soundDevList = TRANSLATOR.getSoundDevices();
        SoundDevices sound_devices(this, soundDevList);
        sound_devices.exec();
    );
}

void RemoteTranslatorUI::on_Timeout()
{
    int level;
    TRY_FUNC(TRANSLATOR.GetMicrophoneLevel(level));
    ui->MicLevelInd->setValue(level);
}

void RemoteTranslatorUI::ActivateAudioFilters()
{
    SoundFilters sound_filters(this);
    sound_filters.exec();
}

void RemoteTranslatorUI::ActivateManConnect()
{
    ManConnect man_connect(this);
    man_connect.exec();
}

void RemoteTranslatorUI::RestoreDefaultConfig()
{
    TRY_FUNC(TRANSLATOR.finalize());
    TRY_FUNC(BB_ClientConfigMgr::Instance().init(true));
    init();
}

void RemoteTranslatorUI::setUserItems(bool is_source)
{
    if (!TRANSLATOR.isConnected())
        return;

    vector<BB_ChannelUser> users;
    TRY_FUNC(TRANSLATOR.getUsers(users, is_source));

    QListWidget* users_list = is_source ? ui->SrcUsersList : ui->TrgUsersList;
    users_list->clear();
    for (unsigned int i = 0; i < users.size(); ++i)
    {
        wstring user = users[i].m_userName;
        if (!users[i].m_isActive)
            users_list->addItem(QString::fromStdWString(user));
        else
        {
            QListWidgetItem* active_item = new QListWidgetItem(QString::fromStdWString(user));
            active_item->setBackgroundColor("green");
            QFont font;
            font.setBold(true);
            active_item->setFont(font);
            users_list->addItem(active_item);
        }
    }
}

void RemoteTranslatorUI::on_UserTimeout()
{
    setUserItems(true);
    setUserItems(false);
}

RemoteTranslatorUI::~RemoteTranslatorUI()
{
    if (TRANSLATOR.isConnected())
    {
        TRY_FUNC(BB_ClientConfigMgr::Instance().saveConfig());
    }
    TRY_FUNC(TRANSLATOR.finalize());
    delete ui;
}

void RemoteTranslatorUI::on_NickName_editingFinished()
{
    BB_ClientConfigMgr::Instance().SetNickName(ui->NickName->text().toStdWString());

}

//////////////////////////////
// Happenings and languages //
//////////////////////////////

static void ChangeChannelMenu(vector<wstring>& channels, QComboBox* combo, wstring def_val)
{
    combo->clear();
    for (unsigned int i = 0; i < channels.size(); ++i)
    {
        wstring channel = channels[i];
        combo->addItem(QString::fromStdWString(channel), i);
        if (channel == def_val)
            combo->setCurrentIndex(i);
    }
}

// Change happening
void RemoteTranslatorUI::on_HapList_currentIndexChanged(const QString &arg1)
{
    int hap_id = ui->HapList->itemData(ui->HapList->currentIndex()).toInt();
    Happening hap = happenings[hap_id];
    ChangeChannelMenu(hap.m_srcChannels, ui->SrcLangList, ConfigUI.m_SrcChannel);
    ChangeChannelMenu(hap.m_dstChannels, ui->TrgLangList, ConfigUI.m_TrgChannel);
}

// Change source language
void RemoteTranslatorUI::on_SrcLangList_currentIndexChanged(const QString &arg1)
{
    int hap_id = ui->HapList->itemData(ui->HapList->currentIndex()).toInt();
    Happening hap = happenings[hap_id];

    int lang_id = ui->SrcLangList->itemData(ui->SrcLangList->currentIndex()).toInt();
    BB_ClientConfigMgr::Instance().SetSrcChannel(hap.m_srcChannels[lang_id]);
}

// Change target language
void RemoteTranslatorUI::on_TrgLangList_currentIndexChanged(const QString &arg1)
{
    int hap_id = ui->HapList->itemData(ui->HapList->currentIndex()).toInt();
    Happening hap = happenings[hap_id];

    int lang_id = ui->TrgLangList->itemData(ui->TrgLangList->currentIndex()).toInt();
    BB_ClientConfigMgr::Instance().SetTrgChannel(hap.m_dstChannels[lang_id]);
}

// Connect to choosen languages
void RemoteTranslatorUI::on_LangConnect_clicked(bool checked)
{
    if (TRANSLATOR.isConnected())
    {
        TRY_FUNC(TRANSLATOR.disconnectHap());
    }

    if (ConfigUI.m_InputSoundDevId.empty() || ConfigUI.m_OutputSoundDevId.empty())
        QMessageBox::critical(this,"Connecting error","Sound devices are not defined");
    else
    {
        TRY_FUNC(TRANSLATOR.connectHap(HAPPENING_CHANNEL_DEFAULT_NAME, ConfigUI.m_NickName,
                                       ConfigUI.m_SrcChannel, ConfigUI.m_TrgChannel,
                                       ConfigUI.m_InputSoundDevId, ConfigUI.m_OutputSoundDevId));
    }

    if (checked)
        ui->LangConnect->setChecked(false);
}

/////////////////////////////////

void RemoteTranslatorUI::on_MicGainSld_valueChanged(int val)
{
    BB_ClientConfigMgr::Instance().SetMicGainLevel(ui->MicGainSld->value());
    TRY_FUNC(TRANSLATOR.UpdateMicrophoneGainLevel(ConfigUI.m_MicGainLevel));
}

void RemoteTranslatorUI::on_TrgLvlSld_valueChanged(int val)
{
    BB_ClientConfigMgr::Instance().SetTrgVolumeLevel(ui->TrgLvlSld->value());
    TRY_FUNC(TRANSLATOR.UpdateVolumeLevel(ConfigUI.m_TrgVolumeLevel, false));
}

void RemoteTranslatorUI::on_SrcLevelSld_valueChanged(int val)
{
    BB_ClientConfigMgr::Instance().SetSrcVolumeLevel(ui->SrcLevelSld->value());
    TRY_FUNC(TRANSLATOR.UpdateVolumeLevel(ConfigUI.m_SrcVolumeLevel, true));
}

void RemoteTranslatorUI::on_VideoQualitylSld_valueChanged(int val)
{
    BB_ClientConfigMgr::Instance().SetVideoQuality(ui->VideoLvlSld->value());
    TRY_FUNC(TRANSLATOR.UpdateVideoQuality(ConfigUI.m_VideoQuality));
}

static QString getMuteButtonFormat(QString name, QString status, QString bg_color, QString fg_color)
{
    return "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
            "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
            "p, li { white-space: pre-wrap;  background-color:" + bg_color + ";}\n"
            "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
            "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600; color:" + fg_color + ";\">" + name + "</span></p>\n"
            "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600; color:" + fg_color + ";\">" + status+ "</span></p></body></html>";
}

static void setStatusLabel(QLabel* label, QString name, QString status, QString bg_color, QString fg_color)
{
    QString button_text = getMuteButtonFormat(name, status, bg_color, fg_color);
    label->setText(QApplication::translate("RemoteTranslatorUI", button_text.toStdString().c_str(), 0, QApplication::UnicodeUTF8));
}

void RemoteTranslatorUI::on_MicMuteBut_clicked(bool checked)
{
    if (checked)
    {
        setStatusLabel(ui->MicStatusLbl, "Microphone", "muted", "red", "#5500ff");
        BB_ClientConfigMgr::Instance().SetMicMute(true);
        TRY_FUNC(TRANSLATOR.MuteMicrophone(true));
    }
    else
    {
        setStatusLabel(ui->MicStatusLbl, "Microphone", "active", "green", "white");
        BB_ClientConfigMgr::Instance().SetMicMute(false);
        TRY_FUNC(TRANSLATOR.MuteMicrophone(false));
    }
}

void RemoteTranslatorUI::on_TrgMuteBut_clicked(bool checked)
{
    if (checked)
    {
        setStatusLabel(ui->TrgStatusLbl, "Target", "muted", "red", "#5500ff");
        BB_ClientConfigMgr::Instance().SetTrgMute(true);
    }
    else
    {
        setStatusLabel(ui->TrgStatusLbl, "Target", "active", "green", "white");
        BB_ClientConfigMgr::Instance().SetTrgMute(false);
    }
    TRY_FUNC(TRANSLATOR.MuteTarget(ConfigUI.m_TrgMute));
}

void RemoteTranslatorUI::on_LocalSelfTestEn_stateChanged(int checked)
{
    if (checked)
    {
        try
        {
            TRANSLATOR.StartTargetSoundLoopbackTest(ConfigUI.m_AGC, ConfigUI.m_noiseCancel, -30, ConfigUI.m_echoCancel);
        }
        catch(BB_Exception excp)
        {
            QMessageBox::critical(this, "Error:", QString::fromStdWString(excp.GetInfo()));
            ui->LocalSelfTestEn->setChecked(false);
        }
    }
    else
    {
        TRY_FUNC(TRANSLATOR.StopTargetSoundLoopbackTest());
    }
}

void RemoteTranslatorUI::on_ServerSelfTestEn_stateChanged(int checked)
{
    if (checked)
    {
        try
        {
            TRANSLATOR.StartTargetSoundLoopbackTest(ConfigUI.m_AGC, ConfigUI.m_noiseCancel, -30, ConfigUI.m_echoCancel);
        }
        catch(BB_Exception excp)
        {
            QMessageBox::critical(this, "Error:", QString::fromStdWString(excp.GetInfo()));
            ui->LocalSelfTestEn->setChecked(false);
        }
    }
    else
    {
        TRY_FUNC(TRANSLATOR.StopTargetSoundLoopbackTest());
    }
}

void RemoteTranslatorUI::on_showVideoButton_clicked(bool clicked)
{
    TRY_FUNC(TRANSLATOR.OpenVideoWindow(effectiveWinId()));
}
