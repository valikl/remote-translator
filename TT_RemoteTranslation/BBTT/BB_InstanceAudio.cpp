#include "BB_InstanceAudio.h"
#include "Utils/BB_Exception.h"
#include "Utils.h"
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <vector>
#include <ctime>



using namespace std;

BB_InstanceAudio::BB_InstanceAudio(const BB_InstanceContext &context) :
    BB_Instance(context)
{
    m_isMuted = true;
    m_audioLoopThread=NULL;
}

BB_InstanceAudio::~BB_InstanceAudio(void)
{
    if (m_audioLoopThread != NULL)
    {

        StopChatThreads();
    }
}

void BB_InstanceAudio::init()
{
    BB_Instance::init();
    initSoundDevices();
}

void BB_InstanceAudio::finalize()
{
    closeSoundDevices();
    BB_Instance::finalize();
}

void BB_InstanceAudio::closeSoundDevices()
{
    TT_CloseSoundDuplexDevices(m_ttInst);
    TT_CloseSoundOutputDevice(m_ttInst);
    TT_CloseSoundInputDevice(m_ttInst);
}

void BB_InstanceAudio::initSoundDevices()
{
    if (!TT_InitSoundDuplexDevices(m_ttInst, m_context.m_inputSoundDevId,
            m_context.m_outputSoundDevId))
    {
        THROW_EXCEPT("Sound duplex devices initialization failed");
    }

    ClientFlags flags = TT_GetFlags(m_ttInst);
	if (!(flags & CLIENT_SNDINOUTPUT_DUPLEX) && (flags & CLIENT_SNDOUTPUT_READY) &&(flags & CLIENT_SNDINPUT_READY))
    {
        THROW_EXCEPT("Cannot initialize Duplex mode");
    }

    // Init volume level to 0
    if (!TT_SetSoundOutputVolume(m_ttInst, 0))
    {
        THROW_EXCEPT("Volume level initialization failed");
    }
}



void BB_InstanceAudio::MuteMicrophone(bool bMute)
{
    if (!TT_EnableTransmission(m_ttInst, TRANSMIT_AUDIO, !(bMute)))
    {
        THROW_EXCEPT("Mute Microphone failed");
    }
    m_isMuted = bMute;
}

void BB_InstanceAudio::MuteTarget(bool bMute)
{
    if (!TT_SetSoundOutputMute(m_ttInst, bMute))
    {
        THROW_EXCEPT("Mute Target failed");
    }
}

int gainLevel(int ref_volume)
{
    if(ref_volume <= SOUND_VOLUME_MAX)
        return SOUND_GAIN_DEFAULT;

    float gain = ref_volume/(float)SOUND_VOLUME_MAX;
    gain *= SOUND_GAIN_DEFAULT;
    return gain;
}

void BB_InstanceAudio::updateUserGainLevel(int volume)
{
    int gain = gainLevel(volume);

    std::vector<BB_ChannelUser> users;
    getUsers(users);

    for(int i=0;i<users.size();i++)
    {
        BB_ChannelUser user = users[i];
        if(volume <= SOUND_VOLUME_MAX)
            //disable soft gain
            TT_SetUserGainLevel(m_ttInst, user.m_id, SOUND_GAIN_DEFAULT);
        else
            TT_SetUserGainLevel(m_ttInst, user.m_id, gain);
    }
}

void BB_InstanceAudio::UpdateVolumeLevel(int volumeLevel)
{
    if (!TT_SetSoundOutputVolume(m_ttInst, volumeLevel))
    {
        THROW_EXCEPT("Update volume level failed");
    }
    updateUserGainLevel(volumeLevel);
}

void BB_InstanceAudio::UpdateMicrophoneGainLevel(int gainLevel)
{
    if (!TT_SetSoundInputGainLevel(m_ttInst, gainLevel))
    {
        THROW_EXCEPT("Update microphone gain level failed");
    }
}

void BB_InstanceAudio::EnableDenoising(bool bEnable)
{
    if (!TT_EnableDenoising(m_ttInst, bEnable))
    {
        THROW_EXCEPT("Denoising update failed");
    }
}

void BB_InstanceAudio::EnableEchoCancellation(bool bEnable)
{
    if (!TT_EnableEchoCancellation(m_ttInst, bEnable))
    {
        THROW_EXCEPT("Echo cancelation update failed");
    }
}

void BB_InstanceAudio::SetAGCEnable(bool bEnable, const AGC *agc)
{
    if (!TT_EnableAGC(m_ttInst, bEnable))
    {
        THROW_EXCEPT("Enable/disable AGC failed");
    }

    if (bEnable)
    {
        if (!TT_SetAGCSettings(m_ttInst, agc->m_gainLevel, agc->m_maxIncrement,
                agc->m_maxDecrement, agc->m_maxGain))
        {
            THROW_EXCEPT("AGC settings update failed");
        }
    }
}

void BB_InstanceAudio::EnableVoiceActivation(bool bEnable, int voiceactSlider)
{
    if (!TT_EnableVoiceActivation(m_ttInst, bEnable))
    {
        THROW_EXCEPT("Enable/disable voice activation failed");
    }
    if (bEnable)
    {
        if (!TT_SetVoiceActivationLevel(m_ttInst, voiceactSlider))
        {
            THROW_EXCEPT("Set voice activation level failed");
        }
    }
}

void BB_InstanceAudio::GetMicrophoneLevel(INT32 &level)
{
    level = TT_GetSoundInputLevel(m_ttInst);
}

void BB_InstanceAudio::getUsers(std::vector<BB_ChannelUser> &userList)
{
    BB_Instance::getUsers(userList);
    if (!m_isMuted)
    {
        // Set local user Active
        for (unsigned int i = 0; i < userList.size(); i++)
        {
            if (userList[i].m_userName == m_context.m_nickName)
            {
                userList[i].m_isActive = true;
                break;
            }
        }
    }
}



/////////
//Chat functions
//
void BB_InstanceAudio::StopChatThreads()
{
    // Stop all the threads
    if(m_audioLoopThread!=NULL&&m_stopThread){
    m_stopThread = true;
    m_audioLoopThread->Join();
    delete m_audioLoopThread;
    m_audioLoopThread = NULL;
    }

}
void BB_InstanceAudio::StartChat(IWriter *writer, IWriter *adminWriter){
    m_stopThread=false;
    m_writer=writer;
    m_adminWriter=adminWriter;
    SetAdminUser();
    m_audioLoopThread = new Thread(this);

  }

void BB_InstanceAudio::SetAdminUser(){
    INT32* userIDs = NULL;
    INT32 size = 0;

    ClientConfig config = BB_ClientConfigMgr::Instance().getConfig();

    //adminUser=0;

    if (!TT_GetServerUsers(m_ttInst, userIDs, &size) || size == 0)
    {
        THROW_EXCEPT_WITH_ID("Build channel users list failed", EXCEPTION_ID_CONNECTION_LOST);
    }

    if (size == 0)
    {
        cout << "No users!" << endl;
        THROW_EXCEPT("Build server users list failed");
    }

    userIDs = new INT32[size];
    if (!TT_GetServerUsers(m_ttInst, userIDs, &size))
    {
        delete[] userIDs;
        THROW_EXCEPT("Build server users list failed");
    }

    for (int i = 0; i < size; ++i)
    {
        User ttUser;
        if (!TT_GetUser(m_ttInst, userIDs[i], &ttUser))
        {
            continue;
        }
        str=ttUser.szNickname;
        if(config.m_AdminNickName.compare(ttUser.szNickname)==0){
            adminUser=ttUser;
            break;
        }
    }

    delete[] userIDs;
  }


static const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%X", &tstruct);

    return buf;
}

static int StringToWString(std::wstring &ws, const std::string &s)
{
    std::wstring wsTmp(s.begin(), s.end());

    ws = wsTmp;

    return 0;
}

void BB_InstanceAudio::run()
{
    TextMessage textmsg;
    TTMessage msg;
    int wait_ms = 10000;
    wstring str;
    wstring ui_message;
    User user;
     wstring time_str;
    while(!m_stopThread )
    {
        if(TT_GetMessage(m_ttInst, &msg, &wait_ms)){
        if (msg.wmMsg == WM_TEAMTALK_CMD_USER_TEXTMSG)
        {
            if(!TT_GetTextMessage(m_ttInst, msg.lParam, FALSE, &textmsg))
                continue;
            if(!TT_GetUser(m_ttInst, textmsg.nFromUserID, &user))
                   return;
            StringToWString(time_str,currentDateTime());
            str=textmsg.szMessage;
            switch(textmsg.nMsgType)
            {
            case MSGTYPE_CHANNEL :
                if(textmsg.nChannelID != TT_GetMyChannelID(m_ttInst))
                 {
                    TTCHAR chpath[TT_STRLEN] = {0};
                    TT_GetChannelPath(m_ttInst, textmsg.nChannelID, chpath);
                    ui_message=time_str +L": <";
                    ui_message.append(user.szNickname).append(L"->").append(chpath).append(L"> ").append(str);
                }else{

                    ui_message=time_str +L": <";
                    ui_message.append(user.szNickname).append(L"> ").append(str);
                }
                m_writer->Write(ui_message);

                break;
            case MSGTYPE_BROADCAST :
                ui_message=time_str +L": <";
                ui_message.append(user.szNickname).append(L"->BROADCAST> ").append(str);   // line += QString("<%1->BROADCAST> %2").arg(_Q(user.szNickname)).arg(_Q(msg.szMessage));
                m_writer->Write(ui_message);
                break;
            case MSGTYPE_USER :
                ui_message=time_str +L": <";
                ui_message.append(user.szNickname).append(L"> ").append(str);            //QString("<%1> %2").arg(_Q(user.szNickname)).arg(_Q(msg.szMessage));
                m_writer->Write(ui_message);
                break;
            case MSGTYPE_CUSTOM :

                break;
            }
        }
        }
    }
}


static void CopyWSToChar(wstring wstr,TTCHAR* ttstr){

    do {
        wcsncpy(ttstr, wstr.c_str(), 512);
        if(wstr.size() >= 512)
            ttstr[511] = '\0';
    } while(0);
}

//can recieve till 512 characters
void BB_InstanceAudio::SendMessage(wstring &txtmsg){
    if(txtmsg.length()==0||txtmsg.length()>512)
        return;

    int mychanid = TT_GetMyChannelID(m_ttInst);
    if(mychanid<=0)
        return;
    TextMessage msg;
    msg.nFromUserID = TT_GetMyUserID(m_ttInst);
    msg.nChannelID = mychanid;
    msg.nMsgType = MSGTYPE_CHANNEL;
    //txtmsg.copy(msg.szMessage,txtmsg.length());
    CopyWSToChar(txtmsg,msg.szMessage);
    TT_DoTextMessage(m_ttInst, &msg);
}
