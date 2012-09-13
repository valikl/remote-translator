#include "BB_Translator.h"
#include "BB_ClientConfigMgr.h"
#include "Utils.h"

using namespace std;

BB_Translator::BB_Translator()
{
    m_channelVideo = NULL;
    m_channelSrc = NULL;
    m_channelDst = NULL;
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

    ClientConfig config = BB_ClientConfigMgr::Instance().getConfig();
    context.m_TCP = config.m_TCP;
    context.m_IP = config.m_IP;
    context.m_UDP = config.m_UDP;
    context.m_srvPsw = config.m_srvPsw;
    context.m_srvUser = config.m_srvUser;
    context.m_srvUserPsw = config.m_srvUserPsw;
	context.m_audioDir = DEFAULT_AUDIO_STORAGE;

    BB_SoundDevice soundDevice;
    if (!findSoundDev(inputSoundDevId, soundDevice))
    {
        return EXIT_FAILURE;
    }
    context.m_inputSoundDevId = soundDevice.m_id;

    if (!findSoundDev(outputSoundDevId, soundDevice))
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

	return EXIT_SUCCESS;
}

int BB_Translator::finalize()
{
    return disconnectHap();
}

int BB_Translator::init()
{
	// Get Dummy Instance
	BB_InstanceContext context;

    ClientConfig config = BB_ClientConfigMgr::Instance().getConfig();
    context.m_TCP = config.m_TCP;
    context.m_IP = config.m_IP;
    context.m_UDP = config.m_UDP;
    context.m_srvPsw = config.m_srvPsw;
    context.m_srvUser = config.m_srvUser;
    context.m_srvUserPsw = config.m_srvUserPsw;

	BB_Instance inst(context);
	inst.getInstance();

	std::vector<BB_Channel> channels;
	int ret = inst.getChannels(channels);
	if (ret != EXIT_SUCCESS)
	{
		return ret;
	}

	ret = initHapsList(channels);
	if (ret != EXIT_SUCCESS)
	{
		return ret;
	}

	ret = inst.getSoundDevices(m_soundDevList);

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
    for (int i=0; i < hap.m_dstChannels.size(); i++)
	{
		if (hap.m_dstChannels[i].m_name == name)
		{
			channelId = hap.m_dstChannels[i].m_id;
			return true;
		}
	}
	return false;
}

bool BB_Translator::findSoundDev(wstring deviceId, BB_SoundDevice &soundDevice)
{
    for (int i=0; i < m_soundDevList.size(); i++)
    {
        if (m_soundDevList[i].m_deviceId == deviceId)
        {
            soundDevice = m_soundDevList[i];
            return true;
        }
    }
    return false;
}

int BB_Translator::getUsers(std::vector<BB_ChannelUser> &userList, bool isSource)
{
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
        //TT_SetUserMute (IN TTInstance *lpTTInstance, IN INT32 nUserID, IN BOOL bMute)
    }
    case OP_CODE_MUTE_TARGET:
    {
        //TT_SetUserMute (IN TTInstance *lpTTInstance, IN INT32 nUserID, IN BOOL bMute)
    }
    default:
    {
        ret = EXIT_FAILURE;
    }
    }

    return ret;
}
