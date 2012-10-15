#include "BB_Instance.h"
#include "Utils.h"
#include <stdio.h>
#include <tchar.h>

using namespace std;

BB_Instance::BB_Instance(const BB_InstanceContext &context) : m_context(context), m_thread(NULL), m_stopThread(false)
{
	// We don't want to call TT functions in Ctor
	// Caller must call init()

	m_channelId = context.channelId;
}

BB_Instance::~BB_Instance(void)
{
	// We don't want to call TT functions in Dtor
	// Caller must call finalize()
}

int BB_Instance::init()
{
	int ret;
	CHECK_ret(getInstance());
	CHECK_ret(joinChannel());
	CHECK_ret(setInstProp());
    CHECK_ret(initSoundDevices());

	return EXIT_SUCCESS;
}

void BB_Instance::finalize()
{
    closeSoundDevices();
	TT_DoLogout(m_ttInst);
	TT_DoQuit(m_ttInst);
}

int BB_Instance::getInstance()
{
    TTMessage msg;
    int wait_ms, cmd_id;

	m_ttInst = TT_InitTeamTalkPoll();

    //now that we got all the information we needed we can connect and logon
    if(!TT_Connect(m_ttInst, m_context.m_IP.c_str(), m_context.m_TCP, m_context.m_UDP, 0, 0))
        goto error_connect;
     
    //wait for connect event
    wait_ms = 10000;
    if(!TT_GetMessage(m_ttInst, &msg, &wait_ms) || msg.wmMsg == WM_TEAMTALK_CON_FAILED)
        goto error_connect;

    assert(msg.wmMsg == WM_TEAMTALK_CON_SUCCESS);
    assert(TT_GetFlags(m_ttInst) & CLIENT_CONNECTED);
    cout << "Now Connected..." << endl;

    //now that we're connected log on
	cmd_id = TT_DoLogin(m_ttInst, _T(""), m_context.m_srvPsw.c_str(), m_context.m_srvUser.c_str(), m_context.m_srvUserPsw.c_str());
    if(cmd_id < 0)
        goto error_login;

    cout << "Login command got cmd ID #" << cmd_id << endl;

    //wait for server reply
    if(!TT_GetMessage(m_ttInst, &msg, &wait_ms) || msg.wmMsg != WM_TEAMTALK_CMD_PROCESSING)
        goto error_login;

	//get response
    if(!TT_GetMessage(m_ttInst, &msg, &wait_ms) || msg.wmMsg == WM_TEAMTALK_CMD_ERROR)
        goto error_login;

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

	return EXIT_SUCCESS;

error_connect:
    cout << "Failed to connect to server." << endl;
    return EXIT_FAILURE;

error_login:
    cout << "Failed to log on to server." << endl;
    return EXIT_FAILURE;
}

int BB_Instance::closeSoundDevices()
{
    TT_CloseSoundDuplexDevices(m_ttInst);
    TT_CloseSoundOutputDevice(m_ttInst);
    TT_CloseSoundInputDevice(m_ttInst);

    return EXIT_SUCCESS;
}

int BB_Instance::initSoundDevices()
{
    // Init input sound device
    CHECK_ret_bool(TT_InitSoundInputDevice(m_ttInst, m_context.m_inputSoundDevId));
    CHECK_ret_bool(TT_EnableTransmission(m_ttInst, (TRANSMIT_AUDIO), false));

    // Init output sound device
    CHECK_ret_bool(TT_InitSoundOutputDevice(m_ttInst, m_context.m_outputSoundDevId));
    CHECK_ret_bool(TT_EnableTransmission(m_ttInst, (TRANSMIT_AUDIO), true));

    CHECK_ret_bool(TT_InitSoundDuplexDevices(m_ttInst, m_context.m_inputSoundDevId,
        m_context.m_outputSoundDevId));

    ClientFlags flags = TT_GetFlags(m_ttInst);
	if (!(flags & CLIENT_SNDINOUTPUT_DUPLEX) && (flags & CLIENT_SNDOUTPUT_READY) &&(flags & CLIENT_SNDINPUT_READY))
    {
        return EXIT_FAILURE;
		cout << "Cannot initialize Duplex mode"<<endl;
    }

	return EXIT_SUCCESS;
}


int BB_Instance::joinChannel()
{
    TTMessage msg;
    int wait_ms = 10000;

	if (TT_DoJoinChannelByID(m_ttInst, m_channelId, _T("")) == -1) 	
	{
 		printf("Cannot connect to channel!\n");
		return EXIT_FAILURE;
	}

	while(TT_GetMessage(m_ttInst, &msg, &wait_ms) &&  msg.wmMsg != WM_TEAMTALK_CMD_MYSELF_JOINED)
 		processTTMessage(msg);

	return EXIT_SUCCESS;
}

int BB_Instance::setInstProp()
{
	int ret = 0;
    TTMessage msg;
    int wait_ms = 10000;

	ret = TT_DoChangeNickname(m_ttInst, m_context.m_nickName.c_str());
	while(TT_GetMessage(m_ttInst, &msg, &wait_ms) &&  msg.wmMsg != WM_TEAMTALK_CMD_PROCESSING)
 		processTTMessage(msg);

	if (msg.wmMsg == CMDERR_NOT_LOGGEDIN)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
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

int BB_Instance::SetAudioLevels()
{
	INT32 volume, vmin, vmax;

	vmin = SOUND_VOLUME_MIN;
	vmax = SOUND_VOLUME_MAX;

	volume = (SOUND_GAIN_MAX+SOUND_GAIN_MIN)/2;
//	CHECK_ret_bool(TT_SetSoundInputGainLevel(ttInst, volume));
	volume = TT_GetSoundInputGainLevel(m_ttInst);

	volume = TT_GetSoundOutputVolume(m_ttInst);

//volume = TT_GetUserVolume(ttInst, TT_GetMyUserID(ttInst));

//TT_SetSoundOutputVolume(ttInst, SOUND_VOLUME_MIN);
	return EXIT_SUCCESS;

}

int BB_Instance::EnableTransmition()
{
	TT_EnableTransmission(m_ttInst, (TRANSMIT_AUDIO), TRUE);
	if (!(TT_GetFlags(m_ttInst) & CLIENT_TX_AUDIO))
	{
		cout <<"Video or audio transmission is not enabled" <<endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}


int BB_Instance::getVideoDevice()
{
	int num;
	VideoCaptureDevice* video_devices = NULL;

	CHECK_ret_bool(TT_GetVideoCaptureDevices(m_ttInst, video_devices, &num));
	if (num == 0)
	{
		cout << "No video devices found" << endl;
		return EXIT_FAILURE;
	}
	video_devices = new VideoCaptureDevice[num];
	CHECK_ret_bool(TT_GetVideoCaptureDevices(m_ttInst, video_devices, &num));

	for (int i = 0; i < num; ++i)
	{
		VideoCaptureDevice& video_device = video_devices[i];
		cout << "Video device name: " << video_device.szDeviceName << endl;
	}

	delete video_devices;
	return EXIT_SUCCESS;
}


int BB_Instance::getChannels(std::vector<BB_Channel> &channels)
{
	INT32 ret = EXIT_FAILURE;
	INT32* channelIDs = NULL;
	INT32 size = 0;

	if (!TT_GetServerChannels(m_ttInst, channelIDs, &size) || size == 0)
	{
		goto __err_exit1;
	}

	if (size == 0)
	{
		cout << "No channels!" << endl;
		goto __err_exit1;
	}

	channelIDs = new INT32[size];
	if (!TT_GetServerChannels(m_ttInst, channelIDs, &size))
	{
		goto __err_exit2;
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

	ret = EXIT_SUCCESS;

__err_exit2:
	delete[] channelIDs;
__err_exit1:
	return ret;
}

int BB_Instance::getSoundDevices(vector<BB_SoundDevice> &soundDevs)
{
	INT32 ret = EXIT_FAILURE;
	SoundDevice* soundDevices = NULL;
	INT32 size = 0;

    INT32 inputDeviceId;
    INT32 outputDeviceId;
    if (!TT_GetDefaultSoundDevices(m_ttInst, &inputDeviceId, &outputDeviceId))
    {
        goto __err_exit1;
    }

	if (!TT_GetSoundInputDevices(m_ttInst, soundDevices, &size) || size == 0)
	{
		goto __err_exit1;
	}

	soundDevices = new SoundDevice[size];
	if (!TT_GetSoundInputDevices(m_ttInst, soundDevices, &size))
	{
		goto __err_exit2;
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
		goto __err_exit1;
	}

	soundDevices = new SoundDevice[size];
	if (!TT_GetSoundOutputDevices(m_ttInst, soundDevices, &size))
	{
		goto __err_exit2;
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

	ret = EXIT_SUCCESS;

__err_exit2:
	delete[] soundDevices;
__err_exit1:
	return ret;
}


int BB_Instance::getUsers(std::vector<BB_ChannelUser> &userList)
{
    INT32 ret = EXIT_FAILURE;
    INT32* userIDs = NULL;
    INT32 size = 0;

    // Always rebuild list
    m_UserList.clear();

    if (!TT_GetChannelUsers(m_ttInst, m_channelId, userIDs, &size) || size == 0)
    {
        goto __err_exit1;
    }

    if (size == 0)
    {
        cout << "No users!" << endl;
        goto __err_exit1;
    }

    userIDs = new INT32[size];
    if (!TT_GetChannelUsers(m_ttInst, m_channelId, userIDs, &size))
    {
        goto __err_exit2;
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
        user.m_userName = ttUser.szUsername;
        user.m_id = userIDs[i];
        m_UserList.push_back(user);
    }

    userList = m_UserList;
    ret = EXIT_SUCCESS;

__err_exit2:
    delete[] userIDs;
__err_exit1:
    return ret;
}

int BB_Instance::StartSoundLoopbackTest(INT32 inputSoundDevId, INT32 outputSoundDevId)
{
    if (!TT_InitSoundInputDevice(m_ttInst, inputSoundDevId))
    {
        return EXIT_FAILURE;
    }

    if (!TT_InitSoundOutputDevice(m_ttInst, outputSoundDevId))
    {
        TT_CloseSoundInputDevice(m_ttInst);
        return EXIT_FAILURE;
    }

    if (!TT_StartSoundLoopbackTest(m_ttInst, inputSoundDevId, outputSoundDevId, 16000, 2))
    {
        TT_CloseSoundOutputDevice(m_ttInst);
        TT_CloseSoundInputDevice(m_ttInst);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int BB_Instance::StopSoundLoopbackTest()
{
    TT_StopSoundLoopbackTest(m_ttInst);
    TT_CloseSoundOutputDevice(m_ttInst);
    TT_CloseSoundInputDevice(m_ttInst);
    return EXIT_SUCCESS;
}

int BB_Instance::StartTargetSoundLoopbackTest(const AGC &agc, bool bEnableDenoise, INT32 maxNoiseSuppress, bool bEchoCancel)
{
    AudioConfig audioConfig;
    audioConfig.bEnableAGC = agc.m_enable;
    audioConfig.nGainLevel = agc.m_gainLevel;
    audioConfig.nMaxIncDBSec = agc.m_maxIncrement;
    audioConfig.nMaxDecDBSec = agc.m_maxDecrement;
    audioConfig.nMaxGainDB = agc.m_maxGain;
    audioConfig.bEnableDenoise = bEnableDenoise;
    audioConfig.nMaxNoiseSuppressDB = maxNoiseSuppress;

    if (!TT_StartSoundLoopbackTestEx(m_ttInst, m_context.m_inputSoundDevId, m_context.m_outputSoundDevId,
        16000, 2, &audioConfig, bEchoCancel))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int BB_Instance::StopTargetSoundLoopbackTest()
{
    TT_StopSoundLoopbackTest(m_ttInst);
    return EXIT_SUCCESS;
}

int BB_Instance::MuteMicrophone(bool bMute)
{
    int ret;
    CHECK_ret(TT_EnableTransmission(m_ttInst, TRANSMIT_AUDIO, !(bMute)));
    return EXIT_SUCCESS;
}

int BB_Instance::MuteTarget(bool bMute)
{
    int ret;
    CHECK_ret(TT_SetSoundOutputMute(m_ttInst, bMute));
    return EXIT_SUCCESS;
}

int BB_Instance::UpdateVolumeLevel(int volumeLevel)
{
    int ret;
    CHECK_ret(TT_SetSoundOutputVolume(m_ttInst, volumeLevel));
    return EXIT_SUCCESS;
}

int BB_Instance::UpdateMicrophoneGainLevel(int gainLevel)
{
    int ret;
    CHECK_ret(TT_SetSoundInputGainLevel(m_ttInst, gainLevel));
    return EXIT_SUCCESS;
}

int BB_Instance::UpdateVideoQuality(int videoQuality)
{
    return EXIT_SUCCESS;
}

int BB_Instance::EnableDenoising(bool bEnable)
{
    int ret;
    CHECK_ret(TT_EnableDenoising(m_ttInst, bEnable));
    return EXIT_SUCCESS;
}

int BB_Instance::EnableEchoCancellation(bool bEnable)
{
    int ret;
    CHECK_ret(TT_EnableEchoCancellation(m_ttInst, bEnable));
    return EXIT_SUCCESS;
}

int BB_Instance::SetAGCEnable(bool bEnable, const AGC *agc)
{
    int ret;
    if (bEnable)
    {
        CHECK_ret(TT_SetAGCSettings(m_ttInst, agc->m_gainLevel, agc->m_maxIncrement, agc->m_maxDecrement, agc->m_maxGain));
    }

    CHECK_ret(TT_EnableAGC(m_ttInst, bEnable));
    return EXIT_SUCCESS;
}

int BB_Instance::EnableVoiceActivation(bool bEnable, int voiceactSlider)
{
    int ret;
    CHECK_ret(TT_EnableVoiceActivation(m_ttInst, bEnable));
    if (bEnable)
    {
        CHECK_ret(TT_SetVoiceActivationLevel(m_ttInst, voiceactSlider));
    }
    return EXIT_SUCCESS;
}

int BB_Instance::GetMicrophoneLevel(INT32 &level)
{
    level = TT_GetSoundInputLevel(m_ttInst);
    return EXIT_SUCCESS;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

HWND CreateVideoWindow(HWND hWnd)
{
    // Based on example from http://www.winprog.org/tutorial/simple_window.html

    HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE/*GWL_STYLE*/);

    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = L"BBVideoWindowClass";
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        //MessageBox(NULL, "Window Registration Failed!", "Error!",
          //  MB_ICONEXCLAMATION | MB_OK);
        return NULL;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"BBVideoWindowClass",
        L"Video",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
       // MessageBox(NULL, "Window Creation Failed!", "Error!",
       //     MB_ICONEXCLAMATION | MB_OK);
        return NULL;
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    //return Msg.wParam;
    return hwnd;
}


int BB_Instance::OpenVideoWindow(HWND hWnd)
{
    if (m_thread)
    {
        // Video window is already opened
        return EXIT_FAILURE;
    }
    m_stopThread = false;
    m_hWnd = hWnd;
    m_thread = new Thread(this);
    return EXIT_SUCCESS;
}

int BB_Instance::CloseVideoWindow()
{
    if (m_thread == NULL)
    {
        // Video window is not opened
        return EXIT_FAILURE;
    }
    m_stopThread = true;
    m_thread->Join();

    delete m_thread;
    m_thread = NULL;
    return EXIT_SUCCESS;
}

void BB_Instance::run()
{
    std::vector<BB_ChannelUser> userList;
    if (getUsers(userList) != EXIT_SUCCESS)
    {
        return;
    }

    int userId = -1;
    for (unsigned int i = 0; i < userList.size(); i++)
    {
        if (userList[i].m_userName == m_context.m_nickName)
        {
            userId = userList[i].m_id;
            break;
        }
    }

    if (userId == -1)
    {
        return;
    }

    int cmdId = TT_DoSubscribe(m_ttInst, userId, (SUBSCRIBE_VIDEO | SUBSCRIBE_INTERCEPT_VIDEO));
    if(cmdId > 0)
    {
         cout << "Subscribing to video events from #" << userId << endl;
    }
    else
    {
         cout << "Failed to issue subscribe command" << endl;
    }

    HWND hWnd = CreateVideoWindow(m_hWnd);
    HDC hDC = GetDC(hWnd);

    TTMessage msg;
    int wait_ms = 10000;
    while(TT_GetMessage(m_ttInst, &msg, &wait_ms))
    {
        if (msg.wmMsg == WM_TEAMTALK_USER_VIDEOFRAME)
        {         
            processTTMessage(msg);
            VideoFrame videoFrame;
            int res = TT_AcquireUserVideoFrame(m_ttInst, userId, &videoFrame);
            res = TT_PaintVideoFrame(m_ttInst, userId, hDC, 0, 0, 100, 100);
            TT_ReleaseUserVideoFrame(m_ttInst, userId);
        }
    }

    ReleaseDC(hWnd, hDC);
}


