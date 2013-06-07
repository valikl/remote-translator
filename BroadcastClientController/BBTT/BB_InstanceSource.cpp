#include "BB_InstanceSource.h"
#include "Utils/BB_Exception.h"
#include "Utils/Utils.h"
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <vector>

using namespace std;

BB_InstanceSource::BB_InstanceSource(GroupType groupType, const BB_InstanceContext &context, const wstring name) :
    m_groupType(groupType), m_name(name), BB_Instance(context)
{
}

BB_InstanceSource::~BB_InstanceSource(void)
{
}

void BB_InstanceSource::init()
{
    BB_Instance::init();
    initSoundDevices();

    m_stopThread = false;
    m_thread = new Thread(this);
}

void BB_InstanceSource::finalize()
{
    m_stopThread = true;
    m_thread->Join();

    closeSoundDevices();
    BB_Instance::finalize();
}

void BB_InstanceSource::closeSoundDevices()
{
    TT_CloseSoundDuplexDevices(m_ttInst);
    TT_CloseSoundOutputDevice(m_ttInst);
    TT_CloseSoundInputDevice(m_ttInst);
}

void BB_InstanceSource::initSoundDevices()
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

void BB_InstanceSource::UpdateMicrophoneGainLevel(int gainLevel)
{
    if (!TT_SetSoundInputGainLevel(m_ttInst, gainLevel))
    {
        THROW_EXCEPT("Update microphone gain level failed");
    }
}

void BB_InstanceSource::EnableDenoising(bool bEnable)
{
    if (!TT_EnableDenoising(m_ttInst, bEnable))
    {
        THROW_EXCEPT("Denoising update failed");
    }
}

void BB_InstanceSource::EnableEchoCancellation(bool bEnable)
{
    if (!TT_EnableEchoCancellation(m_ttInst, bEnable))
    {
        THROW_EXCEPT("Echo cancelation update failed");
    }
}

void BB_InstanceSource::SetAGCEnable(bool bEnable, const AGC *agc)
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

void BB_InstanceSource::EnableVoiceActivation(bool bEnable, int voiceactSlider)
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

void BB_InstanceSource::GetMicrophoneLevel(INT32 &level)
{
    level = TT_GetSoundInputLevel(m_ttInst);
}


INT32 BB_InstanceSource::GetUserId()
{
    // Read config
    BB_GroupElementConfig config = BB_ConfigMgr::Instance().GetGroupElementConfig(m_groupType, m_name);

    INT32 userId = 0;
    std::vector<BB_ChannelUser> users;
    getUsers(users);
    for(unsigned int i=0; i < users.size(); i++)
    {
        if (users[i].m_userName == config.m_nickName)
        {
            userId = users[i].m_id;
            break;
        }
    }

    return userId;
}

void BB_InstanceSource::run()
{
    int cnt = 0;
    while(!m_stopThread)
    {
        // Every 1 sec.
        Sleep(1000);
        if (++cnt < 10)
        {
            continue;
        }
        cnt = 0;

        try
        {
            // Read config
            BB_GroupElementConfig config = BB_ConfigMgr::Instance().GetGroupElementConfig(m_groupType, m_name);

            if (!TT_SetSoundInputGainLevel(m_ttInst, config.m_MicGainLevel))
            {
            }

            if (!TT_EnableDenoising(m_ttInst, config.m_noiseCancel))
            {
            }

            if (!TT_EnableEchoCancellation(m_ttInst, config.m_echoCancel))
            {
            }

            if (!TT_EnableAGC(m_ttInst, /*TODO bEnable*/true))
            {
            }

            if (/*TODO bEnable*/true)
            {
                if (!TT_SetAGCSettings(m_ttInst, config.m_AGC.m_gainLevel, config.m_AGC.m_maxIncrement,
                        config.m_AGC.m_maxDecrement, config.m_AGC.m_maxGain))
                {
                }
            }

            if (!TT_EnableVoiceActivation(m_ttInst, config.m_EnableVoiceActivation))
            {
            }

            if (config.m_EnableVoiceActivation)
            {
                if (!TT_SetVoiceActivationLevel(m_ttInst, config.m_VoiceActivationLevel))
                {
                }
            }

            Channel channel;
            if (!TT_GetChannel(m_ttInst, m_channelId, &channel))
            {
                continue;
            }

            int i = 0;
            while ((channel.voiceUsers[i] != 0) && (i < TT_VOICEUSERS_MAX))
            {
                channel.voiceUsers[i++] = 0;
            }

           channel.voiceUsers[0] = GetUserId();
           if (channel.voiceUsers[0] == 0)
           {
               // User not found
           }

            if (TT_DoUpdateChannel(m_ttInst, &channel) == -1)
            {
                continue;
            }
        }
        catch(BB_Exception excp)
        {
            // Not found in the list
            continue;
        }
    }
}
