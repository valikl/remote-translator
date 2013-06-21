#include "BB_Translator.h"
#include "Utils.h"
#include "Utils/Lock.h"
#include "Utils/BB_Exception.h"

using namespace std;

BB_Translator::BB_Translator() : m_channelVideo(NULL), m_channelSrc(NULL), m_channelDst(NULL), m_channelDstLocal(NULL),
    m_channelDummy(NULL), m_channelDstTest(NULL), m_isLoopbackStarted(false), m_isTargetLoopbackStarted(false),
    m_isConnected(false)
{
    TT_SetLicenseInformation(L"Bnei Baruch", 1600664704);
}

BB_Translator::~BB_Translator(void)
{
}

BB_Translator& BB_Translator::Instance()
{
    static BB_Translator instance;
    return instance;
}

void BB_Translator::disconnectHap()
{
    Lock lock(m_cs);

    m_isConnected = false;

    if (m_channelVideo)
    {
        //m_channelVideo->finalize();
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
    if (m_channelDstLocal)
    {
        m_channelDstLocal->finalize();
        delete m_channelDstLocal;
    }

    if (m_channelDummy)
    {
        m_channelDummy->ClearConnectionLostFlag();
    }

    m_channelVideo = NULL;
    m_channelSrc = NULL;
    m_channelDst = NULL;
    m_channelDstLocal = NULL;
}

void BB_Translator::connectHap(wstring hapName, wstring nickName, wstring srcName, wstring dstName,
    wstring inputSoundDevId, wstring outputSoundDevId)
{
    Lock lock(m_cs);

    if (m_isConnected)
    {
        // Already connected
        THROW_EXCEPT("Translator already connected");
    }

    BB_InstanceContext context;
    initInstanceContext(context);

    BB_SoundDevice soundDevice;
    if (!findSoundDev(inputSoundDevId, BB_ClientConfigMgr::Instance().getConfig().m_isSoundSystemWin, soundDevice))
    {
        THROW_EXCEPT("Sound input device not found");
    }
    context.m_inputSoundDevId = soundDevice.m_id;

    if (!findSoundDev(outputSoundDevId, BB_ClientConfigMgr::Instance().getConfig().m_isSoundSystemWin, soundDevice))
    {
        THROW_EXCEPT("Sound output device not found");
    }
    context.m_outputSoundDevId = soundDevice.m_id;
	
	// Find Happening
	HappeningEx hap;
    if (!findHap(hap, hapName))
	{
        THROW_EXCEPT("Happening not found");
	}

    try
    {
        if (!findSrcChannelId(hap, srcName, context.channelId))
        {
            THROW_EXCEPT("Source channel not found");
        }
        context.m_nickName = SRC_CHANNEL_PREFIX + nickName;
        context.m_channelName = srcName;
        m_channelSrc = new BB_InstanceAudio(context);
        m_channelSrc->init();

        if (!findDstChannelId(hap, dstName, context.channelId))
        {
            THROW_EXCEPT("Destination channel not found");
        }
        context.m_nickName = DST_CHANNEL_PREFIX + nickName;
        context.m_channelName = dstName;
        m_channelDst = new BB_InstanceAudio(context);
        m_channelDst->init();

        // Local Dst
        if (!findSrcChannelId(hap, dstName, context.channelId))
        {
            //THROW_EXCEPT("Local Destination channel not found");
        }
        else
        {
            context.m_nickName = LCL_CHANNEL_PREFIX + nickName;
            context.m_channelName = dstName;
            m_channelDstLocal = new BB_InstanceAudio(context);
            m_channelDstLocal->init();
        }

        context.channelId = hap.m_videoChannel.m_id;
        context.m_nickName = VIDEO_CHANNEL_PREFIX + nickName;
        context.m_channelName = VIDEO_CHANNEL_NAME;
        m_channelVideo = new BB_InstanceVideo(context);
        //m_channelVideo->init();
    }
    catch(BB_Exception excp)
    {
        lock.Unlock();
        disconnectHap();
        THROW_EXCEPT(excp.GetInfo());
    }

    m_isConnected = true;
}

void BB_Translator::finalize()
{
    if (m_channelDummy)
    {
        m_channelDummy->finalize();
        delete m_channelDummy;
        m_channelDummy = NULL;
    }
    disconnectHap();
}

void BB_Translator::init()
{
	// Get Dummy Instance
    BB_InstanceContext context;
    initInstanceContext(context);

    m_channelDummy = new BB_InstanceDummy(context);
    try
    {
        m_channelDummy->login();
    }
    catch(BB_Exception excp)
    {
        delete m_channelDummy;
        m_channelDummy = NULL;
        THROW_EXCEPT(excp.GetInfo());
    }

    try
    {
        m_channelDummy->StartHandleMessages();

        std::vector<BB_Channel> channels;
        m_channelDummy->getChannels(channels);

        if (initHapsList(channels) != EXIT_SUCCESS)
        {
            THROW_EXCEPT("Cannot build happenings list");
        }

        m_soundDevList.clear();
        m_channelDummy->getSoundDevices(m_soundDevList);
    }
    catch(BB_Exception excp)
    {
        finalize();
        THROW_EXCEPT(excp.GetInfo());
    }
}

bool BB_Translator::isConnectionLost()
{
    Lock lock(m_cs);

    if (m_channelDummy)
    {
        return m_channelDummy->isConnectionLost();
    }
    else
    {
        return false;
    }
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

void BB_Translator::getUsers(std::vector<BB_ChannelUser> &userList, InstType instType)
{
    Lock lock(m_cs);

    if (!m_isConnected)
    {
        THROW_EXCEPT("Cannot generate Users list. Translator is not connected");
    }

    switch (instType)
    {
        case INSTANCE_TYPE_SRC:
        {
            m_channelSrc->getUsers(userList);
            break;
        }
        case INSTANCE_TYPE_DST:
        {
            m_channelDst->getUsers(userList);
            break;
        }
        case INSTANCE_TYPE_DST_LOCAL:
        {
            if (m_channelDstLocal)
            {
                m_channelDstLocal->getUsers(userList);
            }
            else
            {
                THROW_EXCEPT("Cannot generate Users list. No local translator.");
            }
            break;
        }
        case INSTANCE_TYPE_VIDEO:
        {
            m_channelVideo->getUsers(userList);
            break;
        }
        default:
        {
            break;
        }
    }
}

void BB_Translator::StartSoundLoopbackTest(wstring inputSoundDevId, wstring outputSoundDevId, bool isSoundSystemWin)
{
    Lock lock(m_cs);

    if (m_isLoopbackStarted)
    {
        THROW_EXCEPT("Sound loopback already started");
    }

    BB_SoundDevice inputSoundDev;
    if (!findSoundDev(inputSoundDevId, isSoundSystemWin, inputSoundDev))
    {
        THROW_EXCEPT("Input sound device was not found");
    }

    BB_SoundDevice outputSoundDev;
    if (!findSoundDev(outputSoundDevId, isSoundSystemWin, outputSoundDev))
    {
        THROW_EXCEPT("Output sound device was not found");
    }

    m_channelDummy->StartSoundLoopbackTest(inputSoundDev.m_id, outputSoundDev.m_id);
    m_isLoopbackStarted = true;
}

void BB_Translator::StopSoundLoopbackTest()
{
    Lock lock(m_cs);

    if (!m_isLoopbackStarted)
    {
        THROW_EXCEPT("Sound loopback test was not started");
    }
    m_isLoopbackStarted = false;
    m_channelDummy->StopSoundLoopbackTest();
}

void BB_Translator::StartTargetSoundLoopbackTest(const AGC &agc, bool bEnableDenoise, INT32 maxNoiseSuppress, bool bEchoCancel,
    wstring inputSoundDevId, wstring outputSoundDevId, bool isSoundSystemWin)
{
    Lock lock(m_cs);

    if (m_isTargetLoopbackStarted)
    {
        THROW_EXCEPT("Target loopback already started");
    }

    BB_SoundDevice inputSoundDev;
    if (!findSoundDev(inputSoundDevId, isSoundSystemWin, inputSoundDev))
    {
        THROW_EXCEPT("Input sound device was not found");
    }

    BB_SoundDevice outputSoundDev;
    if (!findSoundDev(outputSoundDevId, isSoundSystemWin, outputSoundDev))
    {
        THROW_EXCEPT("Output sound device was not found");
    }

    m_channelDummy->StartTargetSoundLoopbackTest(agc, bEnableDenoise, maxNoiseSuppress, bEchoCancel,
        inputSoundDev.m_id, outputSoundDev.m_id);
    m_isTargetLoopbackStarted = true;
}

void BB_Translator::StopTargetSoundLoopbackTest()
{
    Lock lock(m_cs);

    if (!m_isTargetLoopbackStarted)
    {
        THROW_EXCEPT("Target loopback not started");
    }
    m_isTargetLoopbackStarted = false;
    m_channelDummy->StopTargetSoundLoopbackTest();
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

void BB_Translator::MuteMicrophone(bool bMute)
{
    Lock lock(m_cs);

    if (!m_isConnected)
    {
        THROW_EXCEPT("Cannot mute microphone. Translator is not connected");
    }
    m_channelDst->MuteMicrophone(bMute);
}

void BB_Translator::MuteTarget(bool bMute, InstType type)
{
    Lock lock(m_cs);

    if (!m_isConnected)
    {
        THROW_EXCEPT("Cannot mute target. Translator is not connected");
    }

    if (type == INSTANCE_TYPE_DST_LOCAL && m_channelDstLocal == NULL)
    {
        THROW_EXCEPT("Cannot mute target. No Local Translator.");
    }

    if (type == INSTANCE_TYPE_DST)
    {
        m_channelDst->MuteTarget(bMute);
    }
    else // INSTANCE_TYPE_DST_LOCAL
    {
        m_channelDstLocal->MuteTarget(bMute);
    }
}

void BB_Translator::UpdateVolumeLevel(int volumeLevel, bool isSource, InstType type)
{
    Lock lock(m_cs);

    if (!m_isConnected)
    {
        THROW_EXCEPT("Cannot update volume level. Translator is not connected");
    }
    if (isSource)
    {
        m_channelSrc->UpdateVolumeLevel(volumeLevel);
    }
    else
    {
        if (type == INSTANCE_TYPE_DST)
        {
             m_channelDst->UpdateVolumeLevel(volumeLevel);
        }
        else // INSTANCE_TYPE_DST_LOCAL
        {
            m_channelDstLocal->UpdateVolumeLevel(volumeLevel);
        }
    }
}

void BB_Translator::UpdateMicrophoneGainLevel(int gainLevel)
{
    Lock lock(m_cs);

    if (!m_isConnected)
    {
        THROW_EXCEPT("Cannot update microphone gain level. Translator is not connected");
    }
    m_channelDst->UpdateMicrophoneGainLevel(gainLevel);
}

void BB_Translator::EnableDenoising(bool bEnable)
{
    Lock lock(m_cs);

    if (!m_isConnected)
    {
        THROW_EXCEPT("Cannot update denosing. Translator is not connected");
    }

    m_channelSrc->EnableDenoising(bEnable);
    m_channelDst->EnableDenoising(bEnable);
}

void BB_Translator::EnableEchoCancellation(bool bEnable)
{
    Lock lock(m_cs);

    if (!m_isConnected)
    {
        THROW_EXCEPT("Cannot update echo cancellation. Translator is not connected");
    }
    m_channelSrc->EnableEchoCancellation(bEnable);
    m_channelDst->EnableEchoCancellation(bEnable);
}

void BB_Translator::SetAGCEnable(bool bEnable, const AGC *agc)
{
    Lock lock(m_cs);

    if (!m_isConnected)
    {
        THROW_EXCEPT("Cannot update AGC. Translator is not connected");
    }
    m_channelDst->SetAGCEnable(bEnable, agc);
}

void BB_Translator::EnableVoiceActivation(bool bEnable, int voiceactSlider)
{
    Lock lock(m_cs);

    if (!m_isConnected)
    {
        THROW_EXCEPT("Cannot update voice activation. Translator is not connected");
    }
    m_channelDst->EnableVoiceActivation(bEnable, voiceactSlider);
}

void BB_Translator::GetMicrophoneLevel(INT32 &level)
{
    Lock lock(m_cs);

    if (!m_isConnected)
    {
        THROW_EXCEPT("Cannot return microphone level. Translator is not connected");
    }
    m_channelDst->GetMicrophoneLevel(level);
}

void BB_Translator::OpenVideoWindow(HWND hWnd)
{
    Lock lock(m_cs);
    m_channelVideo->OpenVideoWindow(hWnd);
}

void BB_Translator::StartDstSoundTest()
{
    Lock lock(m_cs);

    if (!m_isConnected)
    {
        THROW_EXCEPT("Cannot start target sound test. Translator is not connected");
    }

    if (m_channelDstTest != NULL)
    {
        THROW_EXCEPT("Target sound test already started");
    }

    BB_InstanceContext context;
    m_channelDst->getInstanceContext(context);
    context.m_nickName = DST_SOUND_TEST_CHANNEL_NICKNAME;
    m_channelDstTest = new BB_InstanceAudio(context);
    m_channelDstTest->init();
    int tstv;
    if (BB_ClientConfigMgr::Instance().getConfig().m_SrcVolumeLevel*2 > SOUND_VOLUME_MAX)
        tstv = SOUND_VOLUME_MAX;
    else
        tstv = BB_ClientConfigMgr::Instance().getConfig().m_SrcVolumeLevel*2;
    m_channelDstTest->UpdateVolumeLevel(tstv);
}

void BB_Translator::StopDstSoundTest()
{
    Lock lock(m_cs);

    if (m_channelDstTest == NULL)
    {
        THROW_EXCEPT("Target sound test not started");
    }

    m_channelDstTest->finalize();
    delete m_channelDstTest;
    m_channelDstTest = NULL;
}

void BB_Translator::ReconnectSrcChannel(wstring hapName, wstring srcName)
{
    Lock lock(m_cs);

    if (!m_isConnected)
    {
        THROW_EXCEPT("Cannot re-connect source language. Translator is not connected");
    }

    BB_InstanceContext context;
    m_channelSrc->getInstanceContext(context);
    context.m_channelName = srcName;

    // Find Happening
    HappeningEx hap;
    if (!findHap(hap, hapName))
    {
        THROW_EXCEPT("Happening not found");
    }

    if (!findSrcChannelId(hap, srcName, context.channelId))
    {
        THROW_EXCEPT("Source channel not found");
    }

    // Disconnect source channel
    m_channelSrc->finalize();
    delete m_channelSrc;

    // Connect
    m_channelSrc = new BB_InstanceAudio(context);
    m_channelSrc->init();
}


///Chat functions

void BB_Translator::StartTranslatorsChat(IWriter *writer){
    if(m_channelDst!=0)
    m_channelDst->StartChat(writer);
}

void BB_Translator::SendMessageToTranslators(std::wstring &txtmsg){
    m_channelDst->SendMessage(txtmsg);
}

void BB_Translator::StopTranslatorsChat(){
    m_channelDst->StopChatThreads();
}



