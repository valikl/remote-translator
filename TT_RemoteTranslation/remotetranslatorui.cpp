#include "remotetranslatorui.h"
#include "ui_remotetranslatorui.h"
#include <QTimer>
#include <time.h>

static ClientConfig ConfigUI;

/*
bool SrcChannelList(int *Nchannels, ChannelData *ChList)
{
    if (ChList == NULL)
    {
        *Nchannels = 3;
        return true;
    }
    else
    {
        ChList[0].ChannelID = 10;
        ChList[1].ChannelID = 20;
        ChList[2].ChannelID = 30;
        wcscpy(ChList[0].ChannelName, L"IntelKozel");
        wcscpy(ChList[1].ChannelName, L"2xIntelKozel");
        wcscpy(ChList[2].ChannelName, L"4xIntelKozel");

        return true;
    }
}
*/

// Configuration Manager functions

static void ChangeChannelMenu(vector<QString>& channels, QComboBox* combo, QString def_val)
{
    combo->clear();
    for (unsigned int i = 0; i < channels.size(); ++i)
    {
        QString channel = channels[i];
        combo->addItem(channel, i);
        if (channel == def_val)
            combo->setCurrentIndex(i);
    }
}

static void InitHapsMenu(vector<HapData>& haps, Ui::RemoteTranslatorUI* ui)
{
    for (unsigned int i = 0; i < haps.size(); ++i)
    {
        HapData hap = haps[i];
        ui->HapList->addItem(hap.m_Happening, i);
        if (hap.m_Happening == ConfigUI.m_Happening)
            ui->HapList->setCurrentIndex(i);
    }
 }

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

    // simulation of config manager
    GetHapsData(haps_from_mgr);

    ui->NickName->setText(ConfigUI.m_NickName);

    ui->MicGainSld->setMinimum(0);
    ui->MicGainSld->setMaximum(SOUND_GAIN_MAX);
    ui->MicGainSld->setValue(ConfigUI.m_MicGainLevel);

    ui->MicMuteBut->setCheckable(true);
    ui->MicLevelInd->setMinimum(0);
//    ui->MicLevelInd->setMaximum(100);

    //Timer for progress bar
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_Timeout()));
    timer->start(100);

    //Initialize ComboBoxes
    InitHapsMenu(haps_from_mgr, ui);

    ui->MicLevelInd->setValue(GetMicLevel());
}

void RemoteTranslatorUI::on_Timeout()
{
//    ui->MicLevelInd->setValue(0);
    ui->MicLevelInd->setValue(GetMicLevel());
}

RemoteTranslatorUI::~RemoteTranslatorUI()
{
    delete ui;
}


void RemoteTranslatorUI::on_NickName_editingFinished()
{
    ConfigUI.m_NickName = ui->NickName->text();
}


void RemoteTranslatorUI::on_HapList_currentIndexChanged(const QString &arg1)
{
    int hap_id = ui->HapList->itemData(ui->HapList->currentIndex()).toInt();
    HapData hap = haps_from_mgr[hap_id];
    ChangeChannelMenu(hap.m_srcList, ui->SrcLangList, ConfigUI.m_SrcChannel);
    ChangeChannelMenu(hap.m_trgList, ui->TrgLangList, ConfigUI.m_TrgChannel);
}

void RemoteTranslatorUI::on_MicGainSld_valueChanged(int val)
{
    ConfigUI.m_MicGainLevel = ui->MicGainSld->value();
}

void RemoteTranslatorUI::on_MicMuteBut_clicked(bool checked)
{
    if (checked)
        ui->MicStatusLbl->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                                          "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                                                          "p, li { white-space: pre-wrap;  background-color:red;}\n"
                                                          "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
                                                          "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600; color:#5500ff;\">Microphone</span></p>\n"
                                                          "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600; color:#5500ff;\"> muted</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    else
        ui->MicStatusLbl->setText(QApplication::translate("RemoteTranslatorUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                                          "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                                                          "p, li { white-space: pre-wrap;  background-color:green;}\n"
                                                          "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
                                                          "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600; color:white;\">Microphone</span></p>\n"
                                                          "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600; color:white;\"> active</span></p></body></html>", 0, QApplication::UnicodeUTF8));
}
