#include "remotetranslatorui.h"
#include "sounddevices.h"
#include "BBTT/BB_ClientConfigMgr.h"
#include "ui_remotetranslatorui.h"
#include <QTimer>
#include <time.h>

// Configuration Manager functions

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

static void InitHapsMenu(vector<Happening>& haps, Ui::RemoteTranslatorUI* ui)
{
    for (unsigned int i = 0; i < haps.size(); ++i)
    {
        Happening hap = haps[i];
        ui->HapList->addItem(QString::fromStdWString(hap.m_hapName), i);
        if (hap.m_hapName == ConfigUI.m_Happening)
            ui->HapList->setCurrentIndex(i);
    }
 }

/*
// simulation of config manager
static vector<HapData> haps_from_mgr;
static void GetHapsData(vector<HapData>& haps)
{
    HapData hap1;
    hap1.m_Happening = "HAP_lesson";
    hap1.m_srcList.push_back("Hebrew");
    hap1.m_srcList.push_back("Russian");
    hap1.m_trgList.push_back("Spanish");
    hap1.m_trgList.push_back("French");
    haps.push_back(hap1);

    HapData hap2;
    hap2.m_Happening = "HAP_congress";
    hap2.m_srcList.push_back("English");
    hap2.m_srcList.push_back("German");
    hap2.m_trgList.push_back("Turkish");
    hap2.m_trgList.push_back("Hungarian");
    haps.push_back(hap2);

    HapData hap3;
    hap3.m_Happening = "HAP_lecture";
    hap3.m_srcList.push_back("Amharian");
    hap3.m_srcList.push_back("Armenian");
    hap3.m_srcList.push_back("German");
    hap3.m_trgList.push_back("Hindu");
    hap3.m_trgList.push_back("Arabic");
    haps.push_back(hap3);

    ConfigUI.m_NickName = "Lev Volovik";
    ConfigUI.m_Happening = "HAP_congress";
    ConfigUI.m_SrcChannel = "German";
    ConfigUI.m_TrgChannel = "Hungarian";
    ConfigUI.m_MicGainLevel = SOUND_GAIN_DEFAULT;
}
*/

//Dummy function for Mic level return

static int GetMicLevel()
{
    static INT32 i,f;
    INT32 xx;
    //int i;/* initialize random seed: */
//    srand ( time(NULL) );
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

    BB_ClientConfigMgr::Instance().init("C:\\Projects\\work\\config.xml");

    translator.init();
    haps_from_mgr = translator.getHappenings();

    ui->NickName->setText(QString::fromStdWString(ConfigUI.m_NickName));

    ui->MicGainSld->setMinimum(0);
    ui->MicGainSld->setMaximum(SOUND_GAIN_MAX);
    ui->MicGainSld->setValue(ConfigUI.m_MicGainLevel);


    ui->TrgLvlSld->setMinimum(0);
    ui->TrgLvlSld->setMaximum(SOUND_VOLUME_MAX);
    ui->TrgLvlSld->setValue(ConfigUI.m_trgVolumeLevel);

    ui->SrcLevelSld->setMinimum(0);
    ui->SrcLevelSld->setMaximum(SOUND_VOLUME_MAX);
    ui->SrcLevelSld->setValue(ConfigUI.m_SrcVolumeLevel);

    BB_ClientConfigMgr::Instance().SetVideoQuality(100);
    ui->VideoLvlSld->setMinimum(0);
    ui->VideoLvlSld->setMaximum(100);
    ui->VideoLvlSld->setValue(ConfigUI.m_VideoQuality);


    ui->MicMuteBut->setCheckable(true);
    ui->MicLevelInd->setMinimum(0);
    ui->MicLevelInd->setMaximum(20);
    ui->MicLevelInd->setTextVisible(false);

    ui->TrgMuteBut->setCheckable(true);

    //Timer for progress bar
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_Timeout()));
    timer->start(100);

    // Timer for user detection
    user_timer = new QTimer(this);
    connect(user_timer, SIGNAL(timeout()), this, SLOT(on_UserTimeout()));
    user_timer->start(1000);

    //Initialize ComboBoxes
    InitHapsMenu(haps_from_mgr, ui);

    ui->MicLevelInd->setValue(GetMicLevel());

    connect(ui->actionConfigure_Audio, SIGNAL(triggered()), this, SLOT(ActivateSoundDevices()));
}

void RemoteTranslatorUI::ActivateSoundDevices()
{
    vector<BB_SoundDevice> soundDevList = translator.getSoundDevices();
    SoundDevices sound_devices(this, soundDevList);
    sound_devices.exec();
}

void RemoteTranslatorUI::on_Timeout()
{
//    ui->MicLevelInd->setValue(0);
    ui->MicLevelInd->setValue(GetMicLevel());
}

void getSrcUsers(vector<string>& users, string& active_user)
{
    users.clear();
    users.push_back("Valik");
    users.push_back("Valik1");

    active_user = "Valik1";
}

void getTrgUsers(vector<string>& users, string& active_user)
{
    users.clear();
    users.push_back("Huyalik");
    users.push_back("Huyalik1");

    active_user = "Huyalik1";
}

static void setUserItems(QListWidget* users_list, vector<string>& users, string& active_user)
{
    users_list->clear();
    for (unsigned int i = 0; i < users.size(); ++i)
    {
        string user = users[i];
        if (users[i] != active_user)
            users_list->addItem(user.c_str());
        else
        {
            QListWidgetItem* active_item = new QListWidgetItem(user.c_str());
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
    vector<string> users;
    string active_user;

    getSrcUsers(users, active_user);
    setUserItems(ui->SrcUsersList, users, active_user);

    getTrgUsers(users, active_user);
    setUserItems(ui->TrgUsersList, users, active_user);
}

RemoteTranslatorUI::~RemoteTranslatorUI()
{
    delete ui;
}


void RemoteTranslatorUI::on_NickName_editingFinished()
{
    BB_ClientConfigMgr::Instance().SetNickName(ui->NickName->text().toStdWString());
}


void RemoteTranslatorUI::on_HapList_currentIndexChanged(const QString &arg1)
{
    int hap_id = ui->HapList->itemData(ui->HapList->currentIndex()).toInt();
    Happening hap = haps_from_mgr[hap_id];
    ChangeChannelMenu(hap.m_srcChannels, ui->SrcLangList, ConfigUI.m_SrcChannel);
    ChangeChannelMenu(hap.m_dstChannels, ui->TrgLangList, ConfigUI.m_TrgChannel);
}

void RemoteTranslatorUI::on_MicGainSld_valueChanged(int val)
{
    BB_ClientConfigMgr::Instance().SetMicGainLevel(ui->MicGainSld->value());
}

void RemoteTranslatorUI::on_TrgLvlSld_valueChanged(int val)
{
    BB_ClientConfigMgr::Instance().SetTrgVolumeLevel(ui->TrgLvlSld->value());
}

void RemoteTranslatorUI::on_SrcLevelSld_valueChanged(int val)
{
    BB_ClientConfigMgr::Instance().SetSrcVolumeLevel(ui->SrcLevelSld->value());

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
    }
    else
    {
        setStatusLabel(ui->MicStatusLbl, "Microphone", "active", "green", "white");
        BB_ClientConfigMgr::Instance().SetMicMute(false);
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
}
