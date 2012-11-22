#include "BB_Instance.h"
#include "Utils/BB_Exception.h"
#include "Utils.h"
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
	TT_DoLogout(m_ttInst);
	TT_DoQuit(m_ttInst);
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

    assert(msg.wmMsg == WM_TEAMTALK_CON_SUCCESS);
    assert(TT_GetFlags(m_ttInst) & CLIENT_CONNECTED);
    cout << "Now Connected..." << endl;

    //now that we're connected log on
	cmd_id = TT_DoLogin(m_ttInst, _T(""), m_context.m_srvPsw.c_str(), m_context.m_srvUser.c_str(), m_context.m_srvUserPsw.c_str());
    if(cmd_id < 0)
    {
        THROW_EXCEPT("Connection to the server failed");
    }

    cout << "Login command got cmd ID #" << cmd_id << endl;

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
    assert(msg.lParam == TRUE); //command processing complete
    assert(TT_GetFlags(m_ttInst) & CLIENT_AUTHORIZED); //we're authorized
    //ensure account we used is administrator
    assert(TT_GetMyUserType(m_ttInst) & USERTYPE_ADMIN);
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
	int ret = 0;
    TTMessage msg;
    int wait_ms = 10000;

	ret = TT_DoChangeNickname(m_ttInst, m_context.m_nickName.c_str());
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
    ServerProperties srvprop = {0};
    FileInfo file = {0};
    TTCHAR buf[TT_STRLEN] = {0};
    switch(msg.wmMsg)
    {
    case WM_TEAMTALK_CMD_MYSELF_LOGGEDIN :
        cout << "Logged in successfully..." << endl;
        cout << "Got user ID #" << msg.wParam << endl;
        break;
    case WM_TEAMTALK_CMD_SERVER_UPDATE :
        if(TT_GetServerProperties(m_ttInst, &srvprop))
        {
            cout << "Got new server properties:" << endl;
            cout << "Server name: " << srvprop.szServerName << endl;
            cout << "Server password: " << srvprop.szServerName << endl;
            cout << "MOTD: " << srvprop.szMOTD << endl;
            cout << "Server version: " << srvprop.szServerVersion << endl;
            if((srvprop.uUserRights & USERRIGHT_SUBSCRIPTIONS) == USERRIGHT_NONE)
            {
                cout << "WARNING: It's is not possible to modify subscriptions on this server." << endl;
                cout << "Exiting..." << endl;
                exit(1);
            }
        }
        break;
    case WM_TEAMTALK_CMD_CHANNEL_NEW :
        if(!TT_GetChannelPath(m_ttInst, msg.wParam, buf))
            break;
        cout << "Added channel " << buf << endl;
        break;
    case WM_TEAMTALK_CMD_CHANNEL_UPDATE :
        if(!TT_GetChannelPath(m_ttInst, msg.wParam, buf))
            break;
        cout << "Updated channel " << buf << endl;
        break;
    case WM_TEAMTALK_CMD_CHANNEL_REMOVE :
        //cannot retrieve channel since it no longer exists.
        cout << "Removed channel #" << msg.wParam << endl;
        break;
    case WM_TEAMTALK_CMD_USER_LOGGEDIN :
        if(TT_GetUser(m_ttInst, msg.wParam, &user))
        {
            cout << "User #" << user.nUserID << " " << user.szNickname << " logged in" << endl;
            cout << "Setting audio storage: " << m_context.m_audioDir.c_str() << endl;
            TT_SetUserAudioFolder(m_ttInst, msg.wParam, m_context.m_audioDir.c_str(), NULL, AFF_WAVE_FORMAT);
        }
        break;
    case WM_TEAMTALK_CMD_USER_LOGGEDOUT :
        //can't extract user since the user no longer exists
        cout << "User #" << msg.wParam << " logged out" << endl;
        break;
    case WM_TEAMTALK_CMD_USER_UPDATE :
        if(TT_GetUser(m_ttInst, msg.wParam, &user) && 
           TT_GetChannelPath(m_ttInst, msg.lParam, buf))
        {
            cout << "User #" << user.nUserID << " " << user.szNickname << " updated " << buf << endl;
        }
        break;
    case WM_TEAMTALK_CMD_USER_JOINED :
 /*       if(TT_GetUser(m_ttInst, msg.wParam, &user) && 
           TT_GetChannelPath(m_ttInst, msg.lParam, buf))
        {
            cout << "User #" << user.nUserID << " " << user.szNickname << " joined " << buf << endl;
            int cmd_id = TT_DoSubscribe(m_ttInst, user.nUserID, 
                                        SUBSCRIBE_INTERCEPT_USER_MSG | SUBSCRIBE_INTERCEPT_CHANNEL_MSG |
                                        SUBSCRIBE_INTERCEPT_AUDIO);
            if(cmd_id>0)
                cout << "Subscribing to text and audio events from #" << user.nUserID << endl;
            else
                cout << "Failed to issue subscribe command" << endl;
        }
 */       break;
    case WM_TEAMTALK_CMD_USER_LEFT :
        if(TT_GetUser(m_ttInst, msg.wParam, &user) && 
           TT_GetChannelPath(m_ttInst, msg.lParam, buf))
            cout << "User #" << user.nUserID << " " << user.szNickname << " left " << buf << endl;
        break;
    case WM_TEAMTALK_CMD_FILE_NEW :
        if(TT_GetChannelFileInfo(m_ttInst, msg.lParam, msg.wParam, &file) &&
            TT_GetChannelPath(m_ttInst, msg.lParam, buf))
            cout << "File #" << file.nFileID << " " << file.szFileName << " added to channel " << buf << endl;
        break;
    case WM_TEAMTALK_CMD_FILE_REMOVE :
        //we can't extract it since it no longer exists
        if(TT_GetChannelPath(m_ttInst, msg.lParam, buf))
            cout << "File #" << file.nFileID << " removed from channel " << buf << endl;
        break;
    case WM_TEAMTALK_CMD_USER_TEXTMSG :
        {
            TextMessage textmsg;
            User touser = {0};
            if(!TT_GetUser(m_ttInst, msg.wParam, &user))
                break;
            if(!TT_GetTextMessage(m_ttInst, msg.lParam, TRUE, &textmsg))
                break;
            TT_GetUser(m_ttInst, textmsg.nToUserID, &touser);
            TT_GetChannelPath(m_ttInst, textmsg.nChannelID, buf);
            switch(textmsg.nMsgType)
            {
            case MSGTYPE_USER :
                cout << "Text message from user #" << user.nUserID << " ";
                cout << user.szNickname << " to user #" << touser.nUserID << " ";
                cout << touser.szNickname << " ";
                cout << "content: " << textmsg.szMessage << endl;
                break;
            case MSGTYPE_CHANNEL :
                cout << "Text message from user #" << user.nUserID << " ";
                cout << user.szNickname << " to channel " << buf << " ";
                cout << "content: " << textmsg.szMessage << endl;
                break;
            case MSGTYPE_BROADCAST :
                cout << "Text message from user #" << user.nUserID << " ";
                cout << user.szNickname << " to entire server ";
                cout << "content: " << textmsg.szMessage << endl;
                break;
            default:
                break;
            }
        }
        break;
    case WM_TEAMTALK_CMD_PROCESSING :
        if(msg.lParam == 0)
            cout << "Started processing cmd ID #" << msg.wParam << endl;
        else
            cout << "Finished processing cmd ID #" << msg.wParam << endl;
        break;
    case WM_TEAMTALK_USER_AUDIOFILE :
        if(TT_GetUser(m_ttInst, msg.wParam, &user))
        {
            switch(msg.lParam)
            {
            case AFS_ERROR :
                cout << "Failed to store audio file from #" << user.nUserID << " ";
                cout << user.szNickname << endl;
                break;
            case AFS_STARTED :
                cout << "Storing audio from #" << user.nUserID << " ";
                cout << user.szNickname << " to file." << endl;
                break;
            case AFS_FINISHED :
                cout << "Finished storing audio from #" << user.nUserID << " ";
                cout << user.szNickname << " to file." << endl;
                break;
            case AFS_ABORTED :
                cout << "Aborted storing audio from #" << user.nUserID << " ";
                cout << user.szNickname << " to file." << endl;
                break;
            }
        }
        break;
    default :
        cout << "Unknown message #" << msg.wmMsg << " wParam " << msg.wParam << " lParam " << msg.lParam << endl;
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
        THROW_EXCEPT("Build channel users list failed");
    }

    if (size == 0)
    {
        cout << "No users!" << endl;
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
        cout << "No channels!" << endl;
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
        soundDev.m_id = soundDevices[i].nDeviceID;
        soundDev.m_isOutputDevice = false;
        soundDev.m_isSoundSystemWin = (soundDevices[i].nSoundSystem == SOUNDSYSTEM_WINMM);
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
        soundDev.m_id = soundDevices[i].nDeviceID;
        soundDev.m_isOutputDevice = true;
        soundDev.m_isSoundSystemWin = (soundDevices[i].nSoundSystem == SOUNDSYSTEM_WINMM);
        soundDev.m_deviceName = soundDevices[i].szDeviceName;
        soundDev.m_deviceId = soundDevices[i].szDeviceName;
        soundDev.m_isDefault = (soundDevices[i].nDeviceID == outputDeviceId);

        soundDevs.push_back(soundDev);
    }
    delete[] soundDevices;
}
