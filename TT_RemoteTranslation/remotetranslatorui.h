#ifndef REMOTETRANSLATORUI_H
#define REMOTETRANSLATORUI_H

#include "common.h"

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>

#include <QMainWindow>

using namespace std;

struct HapTemplate
{
    string m_hapRegexp;
    string m_srcRegexp;
    string m_dstRegexp;
    string m_videoRegexp;
};

struct AGC
{
    bool m_enable;
    int  m_gainLevel;
    int  m_maxIncrement;
    int  m_maxDecrement;
    int  m_maxGain;
};

// Client configuration
struct ClientConfig
{
    string m_IP;
    int    m_TCP;
    int    m_UDP;
    string m_srvUser;
    string m_srvUserPsw;
    string m_srvPsw;

    // Regexp for happening
    HapTemplate m_hapTemplate;

    // Struct AGC
    AGC m_AGC;
    // Struct De-noise
    int m_noiseCancel;
    // Boolean echo cancelation function
    bool m_echoCancel;
    // Percentage of frames to show 100% - All frames shown, 0% - No frames shown
    int m_framesPerSec;

    //Structure fields for GUI intitialization
    QString m_NickName;
    QString m_Happening;
    QString m_SrcChannel;
    QString m_TrgChannel;
    int m_MicGainLevel;
    int m_SrcVolumeLevel;
    int m_trgVolumeLevel;
    int m_VideoQuality;

    bool m_MicMute;
    bool m_TrgMute;
 };

/* It was decided with Dima that GUI need not channel IDs, it need only names,
   and BBTranslator will calculate appropriate ID
struct ChannelData
{
    INT32 ChannelID;
    QString ChannelName;

    ChannelData() {}
    ChannelData(INT32 id, QString name) : ChannelID(id), ChannelName(name) {}
    void init(INT32 id, QString name)
    {
        ChannelID = id;
        ChannelName = name;
    }
};

struct HapData
{
    ChannelData m_Happening;
    vector<ChannelData> m_srcList;
    vector<ChannelData> m_trgList;
    ChannelData m_video;
};
*/

struct HapData
{
    QString m_Happening;
    vector<QString> m_srcList;
    vector<QString> m_trgList;
    QString m_Video;
};


namespace Ui {
class RemoteTranslatorUI;
}

class RemoteTranslatorUI : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit RemoteTranslatorUI(QWidget *parent = 0);
    ~RemoteTranslatorUI();
    
private slots:

    void on_NickName_editingFinished();
    void on_HapList_currentIndexChanged(const QString &arg1);
    void on_MicGainSld_valueChanged(int val);
    void on_MicMuteBut_clicked(bool checked);
    void on_TrgMuteBut_clicked(bool checked);
    void on_TrgLvlSld_valueChanged(int val);
    void on_SrcLevelSld_valueChanged(int val);


    void on_Timeout();
    void on_UserTimeout();

    void ActivateSoundDevices();

private:

    Ui::RemoteTranslatorUI *ui;
    QTimer *timer;
    QTimer *user_timer;
};

#endif // REMOTETRANSLATORUI_H
