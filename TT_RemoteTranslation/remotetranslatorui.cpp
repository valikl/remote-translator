#include "remotetranslatorui.h"
#include "sounddevices.h"
#include "soundfilters.h"
#include "manconnect.h"
#include "BBTT/BB_ClientConfigMgr.h"
#include "BBTT/Utils.h"
#include "Utils/BB_Exception.h"
#include "ui_remotetranslatorui.h"
#include <QTimer>

RemoteTranslatorUI::RemoteTranslatorUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemoteTranslatorUI),
    first_connect(true)
{
    ui->setupUi(this);
}

void RemoteTranslatorUI::initHapsMenu()
{
    ui->HapList->clear();

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
    int gainMax = 4000; /* real max: SOUND_LEVEL_MAX but it's too much */

    ui->MicGainSld->setRange(SOUND_GAIN_MIN, gainMax);
    ui->MicGainSld->setValue(ConfigUI.m_MicGainLevel);

    ui->TrgLvlSld->setRange(SOUND_VOLUME_MIN, SOUND_VOLUME_MAX);
    ui->TrgLvlSld->setValue(ConfigUI.m_TrgVolumeLevel);

    ui->SrcLevelSld->setRange(SOUND_VOLUME_MIN, SOUND_VOLUME_MAX);
    ui->SrcLevelSld->setValue(ConfigUI.m_SrcVolumeLevel);

    // some mystical bug, configuration video quality is affected by setRange
    int video_quality = ConfigUI.m_VideoQuality;
    ui->VideoLvlSld->setRange(50, 100);
    BB_ClientConfigMgr::Instance().SetVideoQuality(video_quality);
    ui->VideoLvlSld->setValue(ConfigUI.m_VideoQuality);

    ui->MicLevelInd->setMinimum(0);
    ui->MicLevelInd->setMaximum(20);
    ui->MicLevelInd->setTextVisible(false);
    ui->MicLevelInd->setValue(0);
}

void RemoteTranslatorUI::activateSliders()
{
    InstType inst_type = ui->chooseTransButton->isChecked() ? INSTANCE_TYPE_DST_LOCAL : INSTANCE_TYPE_DST;
    TRY_FUNC(TRANSLATOR.UpdateVolumeLevel(ConfigUI.m_TrgVolumeLevel, false, inst_type));
    TRY_FUNC(TRANSLATOR.UpdateVolumeLevel(ConfigUI.m_SrcVolumeLevel, true));
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
    if (TRANSLATOR.isConnected())
        disconnectTranslator();

    // stop translator
    TRY_FUNC(TRANSLATOR.finalize());

    // try to activate translator with new configuration
    try
    {
        TRANSLATOR.init();
    }
    catch(BB_Exception excp)
    {
        QMessageBox::critical(this, "Error:", QString::fromStdWString(excp.GetInfo()));

        // restore default configuration
        TRY_FUNC_WITH_RETURN(BB_ClientConfigMgr::Instance().init(false));

        // activate translator
        TRY_FUNC_WITH_RETURN(initTranslator());
    }

    // set configuration
    initMainConfig();
}

void RemoteTranslatorUI::initTranslator()
{
    try
    {
        TRANSLATOR.init();
    }
    catch(BB_Exception excp)
    {
        QMessageBox::critical(this, "Error:", QString::fromStdWString(excp.GetInfo()));
    }
}

void RemoteTranslatorUI::activateButtons()
{
    // activate sound devices
    connect(ui->actionConfigure_Audio, SIGNAL(triggered()), this, SLOT(ActivateSoundDevices()));
    connect(ui->actionAudio_Filters, SIGNAL(triggered()), this, SLOT(ActivateAudioFilters()));
    connect(ui->actionTT_server_connection, SIGNAL(triggered()), this, SLOT(ActivateManConnect()));
    connect(ui->actionRestore_default_configuration, SIGNAL(triggered()), this, SLOT(RestoreDefaultConfig()));

    // set buttons checkable
    ui->LangConnect->setCheckable(true);

    // disable buttons and sliders until connect
    ui->HapList->setEnabled(false);
    ui->MicGainSld->setEnabled(false);
    ui->MicLevelInd->setEnabled(false);
    ui->SrcLevelSld->setEnabled(false);
    ui->TrgLvlSld->setEnabled(false);
    ui->MicMuteBut->setEnabled(false);
    ui->TrgMuteBut->setEnabled(false);
    ui->showVideoButton->setEnabled(false);
    ui->VideoLvlSld->setEnabled(false);
    ui->ServerSelfTestEn->setEnabled(false);
    ui->chooseTransButton->setEnabled(false);

    //Timer for micophone progress bar
    microphone_timer = new QTimer(this);
    connect(microphone_timer, SIGNAL(timeout()), this, SLOT(on_MicrophoneTimeout()));
    microphone_timer->start(100);

    // Timer for user detection
    user_timer = new QTimer(this);
    connect(user_timer, SIGNAL(timeout()), this, SLOT(on_UserTimeout()));
    user_timer->start(2000);

    //Timer for micophone progress bar
    conlost_timer = new QTimer(this);
    connect(conlost_timer, SIGNAL(timeout()), this, SLOT(on_ConlostTimeout()));
    conlost_timer->start(100);
}

void RemoteTranslatorUI::init()
{
    TRY_FUNC_WITH_RETURN(BB_ClientConfigMgr::Instance().init(false));

    // activate translator
    TRY_FUNC_WITH_RETURN(initTranslator());

    // set configuration
    initMainConfig();

    // activate buttons and devices
    activateButtons();

    // set sliders
    setSliders();
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

void RemoteTranslatorUI::on_MicrophoneTimeout()
{
    if (TRANSLATOR.isConnected())
    {
        int level;
        TRY_FUNC(TRANSLATOR.GetMicrophoneLevel(level));
        ui->MicLevelInd->setValue(level);
    }
    else
        ui->MicLevelInd->setValue(0);
}

void RemoteTranslatorUI::on_ConlostTimeout()
{
    if (!TRANSLATOR.isConnected() || !TRANSLATOR.isConnectionLost())
        return;

    QMessageBox::critical(this,"Connecting error","Internet connection lost");

    // stop translator
    disconnectTranslator();
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
    QMessageBox msgBox;
    msgBox.addButton("OK", QMessageBox::AcceptRole);
    msgBox.addButton("Cancel", QMessageBox::RejectRole);
    msgBox.setText("Your configuration will be changed to default. Are you sure?");
    int ret = msgBox.exec();

    if (ret != QMessageBox::AcceptRole)
        return;

    if (TRANSLATOR.isConnected())
        disconnectTranslator();

    // stop translator
    TRY_FUNC(TRANSLATOR.finalize());

    // restore default coinfiguration
    TRY_FUNC(BB_ClientConfigMgr::Instance().init(true));

    // activate translator
    TRY_FUNC(initTranslator());

    // init main configuration
    initMainConfig();
}

void RemoteTranslatorUI::setUserItems(InstType inst_type)
{
    if (!TRANSLATOR.isConnected())
        return;

    vector<BB_ChannelUser> users;
    TRY_FUNC_WITH_RETURN(TRANSLATOR.getUsers(users, inst_type));

    if (inst_type == INSTANCE_TYPE_VIDEO)
        return;

    QListWidget* users_list = inst_type == INSTANCE_TYPE_SRC ? ui->SrcUsersList : ui->TrgUsersList;
    users_list->clear();
    for (unsigned int i = 0; i < users.size(); ++i)
    {
        wstring user = users[i].m_userName;
        users_list->addItem(QString::fromStdWString(user));
        if (users[i].m_isActive)
        {
            QListWidgetItem* active_item = users_list->item(users_list->count()-1);
            active_item->setBackgroundColor("green");
            QFont font;
            font.setBold(true);
            active_item->setFont(font);
        }
    }
}

void RemoteTranslatorUI::on_UserTimeout()
{
    setUserItems(INSTANCE_TYPE_SRC);
    setUserItems(INSTANCE_TYPE_DST);
}

RemoteTranslatorUI::~RemoteTranslatorUI()
{
    TRY_FUNC(BB_ClientConfigMgr::Instance().saveConfig());
    TRY_FUNC(TRANSLATOR.finalize());
    delete microphone_timer;
    delete user_timer;
    delete conlost_timer;
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

    if (TRANSLATOR.isConnected())
    {
        TRY_FUNC(TRANSLATOR.ReconnectSrcChannel(hap.m_hapName, hap.m_srcChannels[lang_id]));
        TRY_FUNC(TRANSLATOR.UpdateVolumeLevel(ConfigUI.m_SrcVolumeLevel, true));
    }

}

// Change target language
void RemoteTranslatorUI::on_TrgLangList_currentIndexChanged(const QString &arg1)
{
    int hap_id = ui->HapList->itemData(ui->HapList->currentIndex()).toInt();
    Happening hap = happenings[hap_id];

    int lang_id = ui->TrgLangList->itemData(ui->TrgLangList->currentIndex()).toInt();
    BB_ClientConfigMgr::Instance().SetTrgChannel(hap.m_dstChannels[lang_id]);
}

// Connect translator
void RemoteTranslatorUI::connectTranslator()
{
    TRY_FUNC(TRANSLATOR.connectHap(HAPPENING_CHANNEL_DEFAULT_NAME, ConfigUI.m_NickName,
                                   ConfigUI.m_SrcChannel, ConfigUI.m_TrgChannel,
                                   ConfigUI.m_InputSoundDevId, ConfigUI.m_OutputSoundDevId));

    //Activate Audio filters
    enableAudioFilters();

    // set slider values
    activateSliders();

    ui->LangConnect->setCheckable(true);
    ui->MicGainSld->setEnabled(true);
    ui->MicLevelInd->setEnabled(true);
    ui->SrcLevelSld->setEnabled(true);
    ui->TrgLvlSld->setEnabled(true);
    ui->MicMuteBut->setEnabled(true);
    ui->TrgMuteBut->setEnabled(true);
    ui->showVideoButton->setEnabled(true);
    ui->VideoLvlSld->setEnabled(true);
    ui->ServerSelfTestEn->setEnabled(true);

    ui->MicMuteBut->setCheckable(true);
    ui->TrgMuteBut->setCheckable(true);

    if (TRANSLATOR.isLocalDstConnected())
    {
        ui->chooseTransButton->setEnabled(true);
        ui->chooseTransButton->setCheckable(true);
    }
    else
        ui->chooseTransButton->setEnabled(false);

    if (!ui->MicMuteBut->isChecked())
    {
        if (first_connect)
            ui->MicMuteBut->click();
        else
            TRY_FUNC(TRANSLATOR.MuteMicrophone(false));
    }
    else
    {
        TRY_FUNC(TRANSLATOR.UpdateMicrophoneGainLevel(SOUND_GAIN_MIN));
    }

    if (!ui->TrgMuteBut->isChecked())
    {
        if (first_connect)
            ui->TrgMuteBut->click();
    }
    else
    {
        InstType inst_type = ui->chooseTransButton->isChecked() ? INSTANCE_TYPE_DST_LOCAL : INSTANCE_TYPE_DST;
        TRY_FUNC(TRANSLATOR.MuteTarget(ConfigUI.m_TrgMute, inst_type));
    }

    ui->TrgLangList->setEnabled(false);
    ui->NickName->setEnabled(false);

    ui->LangConnect->setText("Disconnect");

    first_connect = false;
}

// Disconnect translator
void RemoteTranslatorUI::disconnectTranslator()
{
    if (ui->ServerSelfTestEn->isChecked())
        ui->ServerSelfTestEn->click();

    // disable buttons and sliders until connect
    ui->MicGainSld->setEnabled(false);
    ui->MicLevelInd->setEnabled(false);
    ui->SrcLevelSld->setEnabled(false);
    ui->TrgLvlSld->setEnabled(false);
    ui->MicMuteBut->setEnabled(false);
    ui->TrgMuteBut->setEnabled(false);
    ui->showVideoButton->setEnabled(false);
    ui->VideoLvlSld->setEnabled(false);
    ui->ServerSelfTestEn->setEnabled(false);
    ui->chooseTransButton->setEnabled(false);

    TRY_FUNC(TRANSLATOR.disconnectHap());

    ui->SrcUsersList->clear();
    ui->TrgUsersList->clear();

    ui->TrgLangList->setEnabled(true);
    ui->NickName->setEnabled(true);

    ui->LangConnect->setText("Connect");
}

// Connect to choosen languages
void RemoteTranslatorUI::on_LangConnect_clicked(bool checked)
{
    if (TRANSLATOR.isConnected())
        disconnectTranslator();
    else if (ConfigUI.m_InputSoundDevId.empty() || ConfigUI.m_OutputSoundDevId.empty())
        QMessageBox::critical(this,"Connecting error","Sound devices are not defined");
    else
        connectTranslator();

    if (checked)
        ui->LangConnect->setChecked(false);
}

/////////////////////////////////

void RemoteTranslatorUI::on_MicGainSld_valueChanged(int val)
{
    BB_ClientConfigMgr::Instance().SetMicGainLevel(ui->MicGainSld->value());
    if (!TRANSLATOR.isConnected())
        return;
    TRY_FUNC(TRANSLATOR.UpdateMicrophoneGainLevel(ConfigUI.m_MicGainLevel));
}

void RemoteTranslatorUI::on_TrgLvlSld_valueChanged(int val)
{
    BB_ClientConfigMgr::Instance().SetTrgVolumeLevel(ui->TrgLvlSld->value());
    if (!TRANSLATOR.isConnected())
        return;
    InstType inst_type = ui->chooseTransButton->isChecked() ? INSTANCE_TYPE_DST_LOCAL : INSTANCE_TYPE_DST;
    TRY_FUNC(TRANSLATOR.UpdateVolumeLevel(ConfigUI.m_TrgVolumeLevel, false, inst_type));
}

void RemoteTranslatorUI::on_SrcLevelSld_valueChanged(int val)
{
    BB_ClientConfigMgr::Instance().SetSrcVolumeLevel(ui->SrcLevelSld->value());
    if (!TRANSLATOR.isConnected())
        return;
    TRY_FUNC(TRANSLATOR.UpdateVolumeLevel(ConfigUI.m_SrcVolumeLevel, true));
}

void RemoteTranslatorUI::on_VideoLvlSld_valueChanged(int val)
{
    BB_ClientConfigMgr::Instance().SetVideoQuality(ui->VideoLvlSld->value());
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
    if (!TRANSLATOR.isConnected())
    {
        QMessageBox::critical(this, "Error:", "You aren't connected!");
        return;
    }

    if (checked)
    {
        TRY_FUNC(TRANSLATOR.UpdateMicrophoneGainLevel(SOUND_GAIN_MIN));
        setStatusLabel(ui->MicStatusLbl, "Microphone", "muted", "red", "#5500ff");
        BB_ClientConfigMgr::Instance().SetMicMute(true);
        TRY_FUNC(TRANSLATOR.MuteMicrophone(true));
    }
    else
    {
        TRY_FUNC(TRANSLATOR.UpdateMicrophoneGainLevel(ConfigUI.m_MicGainLevel));
        setStatusLabel(ui->MicStatusLbl, "Microphone", "active", "green", "white");
        BB_ClientConfigMgr::Instance().SetMicMute(false);
        TRY_FUNC(TRANSLATOR.MuteMicrophone(false));
    }
}

void RemoteTranslatorUI::on_TrgMuteBut_clicked(bool checked)
{
    if (!TRANSLATOR.isConnected())
    {
        QMessageBox::critical(this, "Error:", "You aren't connected!");
        return;
    }

    if (checked)
    {
        setStatusLabel(ui->TrgStatusLbl, "Mute", "translators", "red", "#5500ff");
        BB_ClientConfigMgr::Instance().SetTrgMute(true);
    }
    else
    {
        setStatusLabel(ui->TrgStatusLbl, "Listen", "translators", "green", "white");
        BB_ClientConfigMgr::Instance().SetTrgMute(false);
    }
    InstType inst_type = ui->chooseTransButton->isChecked() ? INSTANCE_TYPE_DST_LOCAL : INSTANCE_TYPE_DST;
    TRY_FUNC(TRANSLATOR.MuteTarget(ConfigUI.m_TrgMute, inst_type));
}

// Choose translator: local or remote
void RemoteTranslatorUI::on_chooseTransButton_clicked(bool checked)
{
    if (ui->chooseTransButton->isChecked())
    {
        ui->chooseTransButton->setChecked(true);
        ui->chooseTransButton->setText("Local");
        TRY_FUNC(TRANSLATOR.MuteTarget(true, INSTANCE_TYPE_DST));
        TRY_FUNC(TRANSLATOR.MuteTarget(ConfigUI.m_TrgMute, INSTANCE_TYPE_DST_LOCAL));
        TRY_FUNC(TRANSLATOR.UpdateVolumeLevel(ConfigUI.m_TrgVolumeLevel, false, INSTANCE_TYPE_DST_LOCAL));
    }
    else
    {
        ui->chooseTransButton->setChecked(false);
        ui->chooseTransButton->setText("Choose local");
        TRY_FUNC(TRANSLATOR.MuteTarget(true, INSTANCE_TYPE_DST_LOCAL));
        TRY_FUNC(TRANSLATOR.MuteTarget(ConfigUI.m_TrgMute, INSTANCE_TYPE_DST));
        TRY_FUNC(TRANSLATOR.UpdateVolumeLevel(ConfigUI.m_TrgVolumeLevel, false, INSTANCE_TYPE_DST));
    }
}

void RemoteTranslatorUI::on_LocalSelfTestEn_stateChanged(int checked)
{
    if (checked)
    {
        try
        {
            TRANSLATOR.StartTargetSoundLoopbackTest(ConfigUI.m_AGC, ConfigUI.m_noiseCancel, -30,
                                                    ConfigUI.m_echoCancel, ConfigUI.m_InputSoundDevId,
                                                    ConfigUI.m_OutputSoundDevId, ConfigUI.m_isSoundSystemWin);
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
            TRANSLATOR.StartDstSoundTest();
        }
        catch(BB_Exception excp)
        {
            QMessageBox::critical(this, "Error:", QString::fromStdWString(excp.GetInfo()));
            ui->ServerSelfTestEn->setChecked(false);
        }
    }
    else
    {
        TRY_FUNC(TRANSLATOR.StopDstSoundTest());
    }
}

void RemoteTranslatorUI::on_showVideoButton_clicked(bool clicked)
{
    if (!TRANSLATOR.isConnected())
    {
        QMessageBox::critical(this, "Error:", "You aren't connected!");
        return;
    }

    TRY_FUNC(TRANSLATOR.OpenVideoWindow(effectiveWinId()));
}
