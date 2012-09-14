#include "BB_Translator.h"
#include "BB_ClientConfigMgr.h"
#include "Utils.h"

using namespace std;

BB_Translator::BB_Translator()
{
    m_channelVideo = NULL;
    m_channelSrc = NULL;
    m_channelDst = NULL;
    m_isConnected = NULL;
    m_channelDummy = NULL;
    m_isLoopbackStarted = false;
    m_isConnected = false;
}

BB_Translator::~BB_Translator(void)
{
}

int BB_Translator::disconnectHap()
{

    if (m_channelVideo)
    {
        m_channelVideo->finalize();
        delete m_channelVideo;
    }
    if (m_channelSrc)
    {
        m_channelSrc->finalize();
        delete m_channelSrc;
    }
    if (m_channelDst)
    {
        m_channelDst->finalize();
        delete m_channelDst;
    }

    return EXIT_SUCCESS;
}

int BB_Translator::connectHap(wstring hapName, wstring nickName, wstring srcName, wstring dstName,
    wstring inputSoundDevId, wstring outputSoundDevId)
{
    BB_InstanceContext context;
    initInstanceContext(context);

    BB_SoundDevice soundDevice;
    if (!findSoundDev(inputSoundDevId, BB_ClientConfigMgr::Instance().getConfig().m_isSoundSystemWin, soundDevice))
    {
        return EXIT_FAILURE;
    }
    context.m_inputSoundDevId = soundDevice.m_id;

    if (!findSoundDev(outputSoundDevId, BB_ClientConfigMgr::Instance().getConfig().m_isSoundSystemWin, soundDevice))
    {
        return EXIT_FAILURE;
    }
    context.m_outputSoundDevId = soundDevice.m_id;
	
	// Find Happening
	HappeningEx hap;
    if (!findHap(hap, hapName))
	{
		return EXIT_FAILURE;
	}

	if (!findSrcChannelId(hap, srcName, context.channelId))
	{
		return EXIT_FAILURE;
	}
	context.m_nickName = SRC_CHANNEL_PREFIX + nickName;
	context.m_channelName = srcName;
	m_channelSrc = new BB_Instance(context);
	m_channelSrc->init();

	if (!findDstChannelId(hap, dstName, context.channelId))
	{
		return EXIT_FAILURE;
	}
	context.m_nickName = DST_CHANNEL_PREFIX + nickName;
	context.m_channelName = dstName;
	m_channelDst = new BB_Instance(context);
	m_channelDst->init(); 

	context.channelId = hap.m_videoChannel.m_id;
	context.m_nickName = VIDEO_CHANNEL_PREFIX + nickName;
	context.m_channelName = VIDEO_CHANNEL_NAME;
    m_channelVideo = new BB_Instance(context);
    m_channelVideo->init();

    m_isConnected = true;
	return EXIT_SUCCESS;
}

int BB_Translator::finalize()
{
    return disconnectHap();
    if (m_channelDummy)
    {
        delete m_channelDummy;
    }
}

int BB_Translator::init()
{
	// Get Dummy Instance
    BB_InstanceContext context;
    initInstanceContext(context);

    m_channelDummy = new BB_Instance(context);
    m_channelDummy->getInstance();

	std::vector<BB_Channel> channels;
    int ret = m_channelDummy->getChannels(channels);
	if (ret != EXIT_SUCCESS)
	{
		return ret;
	}

	ret = initHapsList(channels);
	if (ret != EXIT_SUCCESS)
	{
		return ret;
	}

    ret = m_channelDummy->getSoundDevices(m_soundDevList);

    return ret;
}

int BB_Translator::initHapsList(const std::vector<BB_Channel> &channels)
{
		// Find Source Channel Id
	INT32 sourceChannelId = ROOT_PARENT_ID;
    for (unsigned int i=0; i < channels.size(); i++)
	{
		if (channels[i].name == SOURCE_CHANNEL_NAME)
		{
			sourceChannelId = channels[i].id;
			break;
		}
	}

	if (sourceChannelId == ROOT_PARENT_ID)
	{
		// Source Channel was not found;
		return EXIT_FAILURE;
	}

	// Build Happening
	// NOTE: We currently support only 1 Happening under root.
	Happening hap;
	HappeningEx hapEx;
    for (unsigned int i=0; i < channels.size(); i++)
	{
		if (channels[i].name == VIDEO_CHANNEL_NAME)
		{
			// Add Video channel. 
			// NOTE: It is currently hard coded.
			hap.m_videoChannel = VIDEO_CHANNEL_NAME;
			hapEx.m_videoChannel.m_name = VIDEO_CHANNEL_NAME;
			hapEx.m_videoChannel.m_id = channels[i].id;
			continue;
		}

		ChannelInfo channelInfo;

		if ((channels[i].parentId == sourceChannelId) 
			||
			(channels[i].parentId == ROOT_PARENT_ID  &&
			channels[i].name != SOURCE_CHANNEL_NAME &&
			channels[i].name != SOUND_CHECK_CHANNEL_NAME))
		{
			// Convert from wstring to string and save
			//name.assign(channels[i].name.begin(), channels[i].name.end());

			// For internal usage			
			channelInfo.m_name = channels[i].name;
			channelInfo.m_id = channels[i].id;
		}
		else
		{
			continue;
		}

		if (channels[i].parentId == sourceChannelId)
		{
			// Source Channel
			hap.m_srcChannels.push_back(channels[i].name);
			hapEx.m_srcChannels.push_back(channelInfo);
		}
		else
		{
			// Destination Channel
			hap.m_dstChannels.push_back(channels[i].name);
			hapEx.m_dstChannels.push_back(channelInfo);
		}
	}

	// Set Happaning name
	// It is hardcoded now
	hap.m_hapName = hapEx.m_hapChannel.m_name = HAPPENING_CHANNEL_DEFAULT_NAME;
	hapEx.m_hapChannel.m_id = ROOT_PARENT_ID;	 

	// Add Happening
	m_hapList.push_back(hap);
	m_hapListEx.push_back(hapEx);

	return EXIT_SUCCESS;
}

bool BB_Translator::findHap(HappeningEx &hap, wstring name)
{
    for (unsigned int i=0; i < m_hapListEx.size(); i++)
	{
		if (m_hapListEx[i].m_hapChannel.m_name == name)
		{
			hap = m_hapListEx[i];
			return true;
		}
	}
	return false;
}

bool BB_Translator::findSrcChannelId(const HappeningEx hap, wstring name, INT32 &channelId)
{
    for (unsigned int i=0; i < hap.m_srcChannels.size(); i++)
	{
		if (hap.m_srcChannels[i].m_name == name)
		{
			channelId = hap.m_srcChannels[i].m_id;
			return true;
		}
	}
	return false;
}

bool BB_Translator::findDstChannelId(const HappeningEx hap, wstring name, INT32 &channelId)
{
    for (unsigned int i=0; i < hap.m_dstChannels.size(); i++)
	{
		if (hap.m_dstChannels[i].m_name == name)
		{
			channelId = hap.m_dstChannels[i].m_id;
			return true;
		}
	}
	return false;
}

bool BB_Translator::findSoundDev(wstring deviceId, bool isSoundSystemWin, BB_SoundDevice &soundDevice)
{
    for (unsigned int i=0; i < m_soundDevList.size(); i++)
    {
        if (m_soundDevList[i].m_deviceId == deviceId &&
            m_soundDevList[i].m_isSoundSystemWin == isSoundSystemWin)
        {
            soundDevice = m_soundDevList[i];
            return true;
        }
    }
    return false;
}

int BB_Translator::getUsers(std::vector<BB_ChannelUser> &userList, bool isSource)
{
    if (!m_isConnected)
    {
        return EXIT_FAILURE;
    }

    int ret;
    if (isSource)
    {
        ret = m_channelSrc->getUsers(userList);
    }
    else
    {
        ret = m_channelDst->getUsers(userList);
    }

    return ret;
}

int BB_Translator::StartSoundLoopbackTest(wstring inputSoundDevId, wstring outputSoundDevId, bool isSoundSystemWin)
{
    if (m_isLoopbackStarted)
    {
        return EXIT_FAILURE;
    }

    BB_SoundDevice inputSoundDev;
    if (!findSoundDev(inputSoundDevId, isSoundSystemWin, inputSoundDev))
    {
        return EXIT_FAILURE;
    }

    BB_SoundDevice outputSoundDev;
    if (!findSoundDev(outputSoundDevId, isSoundSystemWin, outputSoundDev))
    {
        return EXIT_FAILURE;
    }

    int ret = m_channelDummy->StartSoundLoopbackTest(inputSoundDev.m_id, outputSoundDev.m_id);
    if (EXIT_SUCCESS == ret)
    {
        m_isLoopbackStarted = true;
    }
    return ret;
}

int BB_Translator::StopSoundLoopbackTest()
{
    if (!m_isLoopbackStarted)
    {
        return EXIT_FAILURE;
    }
    m_isLoopbackStarted = false;
    return m_channelDummy->StopSoundLoopbackTest();
}

void BB_Translator::initInstanceContext(BB_InstanceContext &context)
{
    ClientConfig config = BB_ClientConfigMgr::Instance().getConfig();
    context.m_TCP = config.m_TCP;
    context.m_IP = config.m_IP;
    context.m_UDP = config.m_UDP;
    context.m_srvPsw = config.m_srvPsw;
    context.m_srvUser = config.m_srvUser;
    context.m_srvUserPsw = config.m_srvUserPsw;
    context.m_audioDir = DEFAULT_AUDIO_STORAGE;
}

int BB_Translator::MuteMicrophone(bool bMute)
{
    return m_channelDst->MuteMicrophone(bMute);
}

int BB_Translator::MuteTarget(bool bMute)
{
   return m_channelDst->MuteTarget(bMute);
}

#if 0
int handleOperation(TranslatorOpCode eOpCode)
{
    int ret = EXIT_SUCCESS;
    switch (eOpCode)
    {
    case OP_CODE_UPDATE_MICROPHONE_GAIN:
    {
    }
    case OP_CODE_UPDATE_SOURCE_LEVEL:
    {
    }
    case OP_CODE_UPDATE_TARGET_LEVEL:
    {
    }
    case OP_CODE_UPDATE_VIDEO_QUALITY:
    {
    }
    case OP_CODE_MUTE_MICROPHONE:
    {
        // Disable my microphone
       // TT_EnableTransmission 	( 	IN TTInstance *  	lpTTInstance,
        //        IN TransmitTypes  	uTxType,
         //       IN BOOL  	bEnable	 )
    }
    case OP_CODE_MUTE_TARGET:
    {
        // Mute other users in my channel
        //TT_SetSoundOutputMute (IN TTInstance *lpTTInstance, IN BOOL bMuteAll);
    }
    case OP_START_SOUND_LOOPBACK_TEST:
    {
        TT_StartSoundLoopbackTest( 	IN TTInstance *  	lpTTInstance,
                IN INT32  	nInputDeviceID,
                IN INT32  	nOutputDeviceID,
                IN INT32  	nSampleRate,
                IN INT32  	nChannels
            )
    }
    default:
    {
        ret = EXIT_FAILURE;
    }
    }

    return ret;
}
#endif
