#include "BB_InstanceAudio.h"
#include "Utils/BB_Exception.h"
#include "Utils.h"
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <vector>

using namespace std;

BB_InstanceAudio::BB_InstanceAudio(const BB_InstanceContext &context) :
    BB_Instance(context)
{
    m_isMuted = true;
}

BB_InstanceAudio::~BB_InstanceAudio(void)
{
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

void BB_InstanceAudio::StartSoundLoopbackTest(INT32 inputSoundDevId, INT32 outputSoundDevId)
{
    if (!TT_InitSoundInputDevice(m_ttInst, inputSoundDevId))
    {
        THROW_EXCEPT("Sound input device initialization failed");
    }

    if (!TT_InitSoundOutputDevice(m_ttInst, outputSoundDevId))
    {
        THROW_EXCEPT("Sound output device initialization failed");
    }

    if (!TT_StartSoundLoopbackTest(m_ttInst, inputSoundDevId, outputSoundDevId, 16000, 2))
    {
        TT_CloseSoundOutputDevice(m_ttInst);
        TT_CloseSoundInputDevice(m_ttInst);
        THROW_EXCEPT("Cannot start sound loopback test");
    }
}

void BB_InstanceAudio::StopSoundLoopbackTest()
{
    if (!TT_StopSoundLoopbackTest(m_ttInst))
    {
        THROW_EXCEPT("Cannot stop sound loopback test");
    }
    TT_CloseSoundOutputDevice(m_ttInst);
    TT_CloseSoundInputDevice(m_ttInst);
}

void BB_InstanceAudio::StartTargetSoundLoopbackTest(const AGC &agc, bool bEnableDenoise, INT32 maxNoiseSuppress, bool bEchoCancel,
    INT32 inputSoundDevId, INT32 outputSoundDevId)
{
    if (!TT_InitSoundDuplexDevices(m_ttInst, inputSoundDevId, outputSoundDevId))
    {
        THROW_EXCEPT("Sound devices initialization failed");
    }

    AudioConfig audioConfig;
    audioConfig.bEnableAGC = agc.m_enable;
    audioConfig.nGainLevel = agc.m_gainLevel;
    audioConfig.nMaxIncDBSec = agc.m_maxIncrement;
    audioConfig.nMaxDecDBSec = agc.m_maxDecrement;
    audioConfig.nMaxGainDB = agc.m_maxGain;
    audioConfig.bEnableDenoise = bEnableDenoise;
    audioConfig.nMaxNoiseSuppressDB = maxNoiseSuppress;

    if (!TT_StartSoundLoopbackTestEx(m_ttInst, inputSoundDevId, outputSoundDevId,
        16000, 2, &audioConfig, bEchoCancel))
    {
        TT_CloseSoundDuplexDevices(m_ttInst);
        THROW_EXCEPT("Cannot start extended sound loopback test");
    }
}

void BB_InstanceAudio::StopTargetSoundLoopbackTest()
{
    if (!TT_StopSoundLoopbackTest(m_ttInst))
    {
        THROW_EXCEPT("Cannot stop sound loopback test");
    }
    TT_CloseSoundDuplexDevices(m_ttInst);
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

void BB_InstanceAudio::UpdateVolumeLevel(int volumeLevel)
{
    if (!TT_SetSoundOutputVolume(m_ttInst, volumeLevel))
    {
        THROW_EXCEPT("Update volume level failed");
    }
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
