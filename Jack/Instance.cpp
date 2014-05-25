#include "Instance.h"
#ifdef UNICODE
#define cout wcout
#define cin wcin
#define string wstring
#define ostringstream wostringstream
#define istringstream wistringstream
#define _T(x) L ## x
#else
#define _T
#endif

using namespace std;

BB_Instance::BB_Instance(const BB_InstanceContext &context, bool isInput) :
    m_context(context), m_isInput(isInput)
{
	// We don't want to call TT functions in Ctor
	// Caller must call init()
}

BB_Instance::~BB_Instance(void)
{
}

void BB_Instance::printLog(string msg)
{
    time_t t = time(0);
    localtime(&t);
    string t_str(ctime(&t));

    cout << t_str.substr(0, t_str.length() -1) << " " << m_context.m_ProcessName << ": " << msg.c_str() << endl;
}

bool BB_Instance::init()
{
	m_ttInst = TT_InitTeamTalkPoll();

    initSoundDevice();
    printLog("Sound device initialized");

	if (!connect())
	{
		return false;
	}
	
	return true;
 }
 
 bool BB_Instance::connect()
 {
    if (!login())
	{
		return false;
	}
    printLog("Logged in successfully");
	
	if (!joinChannel())
	{
		return false;
	}
    printLog("Joined channel successfully");
	
	// Get user id
    m_userID = TT_GetMyUserID(m_ttInst);
	
	return true;
 }

void BB_Instance::finalize()
{
    TT_Disconnect(m_ttInst);
}

bool BB_Instance::initSoundDevice()
{
    if (m_isInput)
    {
        TT_InitSoundInputDevice(m_ttInst, 0);
    }
    else
    {
        TT_InitSoundOutputDevice(m_ttInst, 0);
    }
    return true;
}

bool BB_Instance::login()
{
    TTMessage msg;
    int wait_ms, cmd_id;

    // now that we got all the information we needed we can connect and logon
    if (!TT_Connect(m_ttInst, m_context.m_IP.c_str(), m_context.m_TCP, m_context.m_UDP, 0, 0))
    {
        printLog("Connection to the server failed");
        return false;
    }
     
    // wait for connect event
    wait_ms = 10000;
    if (!TT_GetMessage(m_ttInst, &msg, &wait_ms) || msg.wmMsg == WM_TEAMTALK_CON_FAILED)
    {
        printLog("Connection to the server failed2");
        return false;
    }

    //now that we're connected log on
    cmd_id = TT_DoLogin(m_ttInst, m_context.m_nickName.c_str(), m_context.m_srvPsw.c_str(), m_context.m_srvUser.c_str(), m_context.m_srvUserPsw.c_str());
    if(cmd_id < 0)
    {
        printLog("Log on to the server failed");
        return false;
    }

    //wait for server reply
    if (!TT_GetMessage(m_ttInst, &msg, &wait_ms) || msg.wmMsg != WM_TEAMTALK_CMD_PROCESSING)
    {
        printLog("Log on to the server failed2");
        return false;
    }

	//get response
    if (!TT_GetMessage(m_ttInst, &msg, &wait_ms) || msg.wmMsg == WM_TEAMTALK_CMD_ERROR)
    {
        printLog("Log on to the server failed3");
        return false;
    }

    //wait for login command to complete
    //client will now post all the server information
    while(TT_GetMessage(m_ttInst, &msg, &wait_ms) && msg.wmMsg != WM_TEAMTALK_CMD_PROCESSING) {}

    return true;
}

bool BB_Instance::joinChannel()
{
    TTMessage msg;
    int wait_ms = 10000;

    m_channelId = TT_GetChannelIDFromPath(m_ttInst, m_context.m_channelPath.c_str());

    if (TT_DoJoinChannelByID(m_ttInst, m_channelId, m_context.m_channelPsw.c_str()) == -1)
	{
        printLog("Cannot join the channel");
        return false;
	}

    while(TT_GetMessage(m_ttInst, &msg, &wait_ms) &&  msg.wmMsg != WM_TEAMTALK_CMD_MYSELF_JOINED) {}

    return true;
}

bool BB_Instance::setClassroom()
{
    Channel channel;
    if (!TT_GetChannel(m_ttInst, m_channelId, &channel))
    {
        printLog("Get channel failed");
        return false;
    }

    if ((channel.voiceUsers[0] != m_userID) || (channel.voiceUsers[1] > 0))
    {
        int i = 0;
        while ((channel.voiceUsers[i] != 0) && (i < TT_VOICEUSERS_MAX))
        {
            channel.voiceUsers[i++] = 0;
        }

        channel.voiceUsers[0] = m_userID;

        if (TT_DoUpdateChannel(m_ttInst, &channel) == -1)
        {
            printLog("Update channel failed");
            return false;
        }
        else
        {
            printLog("Classroom property restored");
        }
    }

    return true;
}

bool BB_Instance::enableTransmission()
{
    if (!TT_EnableTransmission(m_ttInst, TRANSMIT_AUDIO, true))
    {
        printLog("Enable Transmission failed");
        return false;
    }

    return true;
}

bool BB_Instance::startSoundLoopbackTest()
{
    // Ask Yossi!!!
    if (!TT_StartSoundLoopbackTest(m_ttInst, 0, 0, 48000, 2))
    {
        printLog("Start Sound Loopback Test failed");
        return false;
    }

    return true;
}

bool BB_Instance::stopSoundLoopbackTest()
{
    if (!TT_StopSoundLoopbackTest(m_ttInst))
    {
        printLog("Stop Sound Loopback Test failed");
        return false;
    }

    return true;
}

bool BB_Instance::isInstExist()
{
    Channel channel;
    if (!TT_GetChannel(m_ttInst, m_channelId, &channel))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool BB_Instance::isUserExist()
{
    INT32* userIDs = NULL;
    INT32 size = 0;

    if (!TT_GetChannelUsers(m_ttInst, m_channelId, userIDs, &size) || size == 0)
    {
        return false;
    }

    if (size == 0)
    {
        return false;
    }

    userIDs = new INT32[size];
    if (!TT_GetChannelUsers(m_ttInst, m_channelId, userIDs, &size))
    {
        delete[] userIDs;
        return false;
    }

    for (int i = 0; i < size; ++i)
    {
        User ttUser;
        if (!TT_GetUser(m_ttInst, userIDs[i], &ttUser))
        {
            continue;
        }

        if (ttUser.szNickname == m_context.m_nickName)
        {
            delete[] userIDs;
            return true;
        }
    }

    delete[] userIDs;

    return false;
}

bool BB_Instance::processTTMessage(const TTMessage& msg, bool &killInst)
{
	killInst = true;
	
    switch(msg.wmMsg)
    {
        case WM_TEAMTALK_CMD_MYSELF_LOGGEDOUT :
        {
            printLog("User is Logged Out");
            return false;
        }
        case WM_TEAMTALK_CON_LOST:
        {
            printLog("Connection Lost");
			killInst = false;
            return false;
        }
        case WM_TEAMTALK_CMD_MYSELF_LEFT :
        {
            printLog("User Left The Channel");
            return false;
        }
        case WM_TEAMTALK_CMD_MYSELF_KICKED :
        {
            User ttUser;
            TT_GetUser(m_ttInst, msg.wParam, &ttUser);
            printLog(string("User Was Kicked by") + string(ttUser.szNickname));
            return false;
        }
		default:
		{
		}
    }
    return true;
}


bool BB_Instance::loop()
{
    int wait_ms = 10000;
    TTMessage msg;
    while(1)
    {
	    TT_GetMessage(m_ttInst, &msg, &wait_ms);
		
		bool killInst;
        if (!processTTMessage(msg, killInst))
        {
            return killInst;
        }

        if (m_isInput)
        {
            //setClassroom();
        }
    }
}

