#include "BB_Instance.h"
#include "../Utils/BB_Exception.h"
#include "../Utils/Utils.h"
#include <tchar.h>

using namespace std;

BB_Instance::BB_Instance(const BB_InstanceContext &context) :
    m_context(context), m_channelId(context.channelId)
{
	// We don't want to call TT functions in Ctor
	// Caller must call init()
}

BB_Instance::~BB_Instance(void)
{
}

void BB_Instance::init()
{
    login();
    joinChannel();
    setInstProp();
}

void BB_Instance::finalize()
{
    TT_Disconnect(m_ttInst);
    //TT_DoLogout(m_ttInst);
    //TT_DoQuit(m_ttInst);
}

void BB_Instance::login()
{
    TTMessage msg;
    int wait_ms, cmd_id;

	m_ttInst = TT_InitTeamTalkPoll();

    //now that we got all the information we needed we can connect and logon
    if (!TT_Connect(m_ttInst, m_context.m_IP.c_str(), m_context.m_TCP, m_context.m_UDP, 0, 0))
    {
        THROW_EXCEPT("Connection to the server failed");
    }
     
    //wait for connect event
    wait_ms = 10000;
    if (!TT_GetMessage(m_ttInst, &msg, &wait_ms) || msg.wmMsg == WM_TEAMTALK_CON_FAILED)
    {
        THROW_EXCEPT("Connection to the server failed");
    }

    //now that we're connected log on
	cmd_id = TT_DoLogin(m_ttInst, _T(""), m_context.m_srvPsw.c_str(), m_context.m_srvUser.c_str(), m_context.m_srvUserPsw.c_str());
    if(cmd_id < 0)
    {
        THROW_EXCEPT("Connection to the server failed");
    }

    //wait for server reply
    if (!TT_GetMessage(m_ttInst, &msg, &wait_ms) || msg.wmMsg != WM_TEAMTALK_CMD_PROCESSING)
    {
        THROW_EXCEPT("Log on to the server failed");
    }

	//get response
    if (!TT_GetMessage(m_ttInst, &msg, &wait_ms) || msg.wmMsg == WM_TEAMTALK_CMD_ERROR)
    {
        THROW_EXCEPT("Log on to the server failed");
    }

    //wait for login command to complete
    //client will now post all the server information
    while(TT_GetMessage(m_ttInst, &msg, &wait_ms) &&
        msg.wmMsg != WM_TEAMTALK_CMD_PROCESSING)
    {
        processTTMessage(msg);
    }
}

void BB_Instance::joinChannel()
{
    TTMessage msg;
    int wait_ms = 10000;

	if (TT_DoJoinChannelByID(m_ttInst, m_channelId, _T("")) == -1) 	
	{
        THROW_EXCEPT("Cannot join the channel");
	}

	while(TT_GetMessage(m_ttInst, &msg, &wait_ms) &&  msg.wmMsg != WM_TEAMTALK_CMD_MYSELF_JOINED)
 		processTTMessage(msg);
}

void BB_Instance::setInstProp()
{
    TTMessage msg;
    int wait_ms = 10000;

    if (TT_DoChangeNickname(m_ttInst, m_context.m_nickName.c_str()) == -1)
    {
        THROW_EXCEPT("Set nickname failed");
    }

	while(TT_GetMessage(m_ttInst, &msg, &wait_ms) &&  msg.wmMsg != WM_TEAMTALK_CMD_PROCESSING)
 		processTTMessage(msg);

	if (msg.wmMsg == CMDERR_NOT_LOGGEDIN)
    {
        THROW_EXCEPT("Set nickname failed");
    }
}

void BB_Instance::processTTMessage(const TTMessage& msg)
{
    User user = {0};
    if (msg.wmMsg == WM_TEAMTALK_CMD_USER_LOGGEDIN)
    {
        if(TT_GetUser(m_ttInst, msg.wParam, &user))
        {
            TT_SetUserAudioFolder(m_ttInst, msg.wParam, m_context.m_audioDir.c_str(), NULL, AFF_WAVE_FORMAT);
        }
    }
}

void BB_Instance::getUsers(std::vector<BB_ChannelUser> &userList)
{
    INT32* userIDs = NULL;
    INT32 size = 0;

    // Always rebuild list
    m_UserList.clear();

    if (!TT_GetChannelUsers(m_ttInst, m_channelId, userIDs, &size) || size == 0)
    {
        THROW_EXCEPT_WITH_ID("Build channel users list failed", EXCEPTION_ID_CONNECTION_LOST);
    }

    if (size == 0)
    {
        THROW_EXCEPT("Build channel users list failed");
    }

    userIDs = new INT32[size];
    if (!TT_GetChannelUsers(m_ttInst, m_channelId, userIDs, &size))
    {
        delete[] userIDs;
        THROW_EXCEPT("Build channel users list failed");
    }

    for (int i = 0; i < size; ++i)
    {
        User ttUser;
        if (!TT_GetUser(m_ttInst, userIDs[i], &ttUser))
        {
            continue;
        }

        BB_ChannelUser user;
        // TODO ask Valik, do we need szNickname or szUsername
        // What happen if name is changed or new user connected/disconnected
        user.m_userName = ttUser.szNickname;
        user.m_isActive = (ttUser.uUserState & USERSTATE_TALKING) ==  USERSTATE_TALKING;
        user.m_isVideo = (ttUser.uUserState & USERSTATE_VIDEO) ==  USERSTATE_VIDEO;
        user.m_id = userIDs[i];
        m_UserList.push_back(user);
    }

    userList = m_UserList;
    delete[] userIDs;
}

void BB_Instance::getChannels(std::vector<BB_Channel> &channels)
{
    INT32* channelIDs = NULL;
    INT32 size = 0;

    if (!TT_GetServerChannels(m_ttInst, channelIDs, &size) || size == 0)
    {
        THROW_EXCEPT("Cannot get channels list");
    }

    if (size == 0)
    {
        THROW_EXCEPT("Cannot get channels list");
    }

    channelIDs = new INT32[size];
    if (!TT_GetServerChannels(m_ttInst, channelIDs, &size))
    {
        delete[] channelIDs;
        THROW_EXCEPT("Cannot get channels list");
    }

    Channel channel;
    for (int i = 0; i < size; ++i)
    {
        BB_Channel channelToList;
        channelToList.id = channelIDs[i];
        if (!TT_GetChannel(m_ttInst, channelIDs[i], &channel))
        {
            continue;
        }
        channelToList.name = channel.szName;
        channelToList.parentId = channel.nParentID;

        TTCHAR szChannelPath[TT_STRLEN];
        if (TT_GetChannelPath(m_ttInst, channelIDs[i], szChannelPath))
        {
            channelToList.path = szChannelPath;
        }

        channels.push_back(channelToList);
    }

    delete[] channelIDs;
}


void BB_Instance::getSoundDevices(vector<BB_SoundDevice> &soundDevs)
{
    SoundDevice* soundDevices = NULL;
    INT32 size = 0;

    INT32 inputDeviceId;
    INT32 outputDeviceId;
    if (!TT_GetDefaultSoundDevices(m_ttInst, &inputDeviceId, &outputDeviceId))
    {
        THROW_EXCEPT("Cannot build sound devices list");
    }

    if (!TT_GetSoundInputDevices(m_ttInst, soundDevices, &size) || size == 0)
    {
        THROW_EXCEPT("Cannot build sound devices list");
    }

    soundDevices = new SoundDevice[size];
    if (!TT_GetSoundInputDevices(m_ttInst, soundDevices, &size))
    {
        delete[] soundDevices;
        THROW_EXCEPT("Cannot build sound devices list");
    }

    // Create Input Devices List
    for (int i = 0; i < size; ++i)
    {
        BB_SoundDevice soundDev;
        switch (soundDevices[i].nSoundSystem)
        {
            case SOUNDSYSTEM_WINMM:
            {
                soundDev.m_isSoundSystemWin = true;
                break;
            }
            case SOUNDSYSTEM_DSOUND:
            {
                soundDev.m_isSoundSystemWin = false;
                break;
            }
            default: // SOUNDSYSTEM_ALSA etc.
            {
                // We don't support other types
                continue;
            }
        }
        soundDev.m_id = soundDevices[i].nDeviceID;
        soundDev.m_isOutputDevice = false;
        soundDev.m_deviceName = soundDevices[i].szDeviceName;
        soundDev.m_deviceId = soundDevices[i].szDeviceName;
        soundDev.m_isDefault = (soundDevices[i].nDeviceID == inputDeviceId);
        soundDevs.push_back(soundDev);
    }

    delete[] soundDevices;

    size = 0;
    soundDevices = NULL;
    if (!TT_GetSoundOutputDevices(m_ttInst, soundDevices, &size) || size == 0)
    {
        THROW_EXCEPT("Cannot build sound devices list");
    }

    soundDevices = new SoundDevice[size];
    if (!TT_GetSoundOutputDevices(m_ttInst, soundDevices, &size))
    {
        delete[] soundDevices;
        THROW_EXCEPT("Cannot build sound devices list");
    }

    // Create Output Devices List
    for (int i = 0; i < size; ++i)
    {
        BB_SoundDevice soundDev;
        switch (soundDevices[i].nSoundSystem)
        {
            case SOUNDSYSTEM_WINMM:
            {
                soundDev.m_isSoundSystemWin = true;
                break;
            }
            case SOUNDSYSTEM_DSOUND:
            {
                soundDev.m_isSoundSystemWin = false;
                break;
            }
            default: // SOUNDSYSTEM_ALSA etc.
            {
                // We don't support other types
                continue;
            }
        }
        soundDev.m_id = soundDevices[i].nDeviceID;
        soundDev.m_isOutputDevice = true;
        soundDev.m_deviceName = soundDevices[i].szDeviceName;
        soundDev.m_deviceId = soundDevices[i].szDeviceName;
        soundDev.m_isDefault = (soundDevices[i].nDeviceID == outputDeviceId);

        soundDevs.push_back(soundDev);
    }
    delete[] soundDevices;
}

void BB_Instance::UpdateNickName(const std::wstring nickName)
{
    m_context.m_nickName = nickName;
    setInstProp();
}

INT32 BB_Instance::GetUserId(const std::wstring nickName)
{
    INT32 userId = -1;
    std::vector<BB_ChannelUser> users;
    try
    {
        getUsers(users);
    }
    catch(BB_Exception excp)
    {
        return userId;
    }

    for(unsigned int i=0; i < users.size(); i++)
    {
        if (users[i].m_userName == nickName)
        {
            userId = users[i].m_id;
            break;
        }
    }

    return userId;
}
