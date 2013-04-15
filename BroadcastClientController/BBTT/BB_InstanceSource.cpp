#include "BB_InstanceSource.h"
#include "Utils/BB_Exception.h"
#include "Utils/Utils.h"
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <vector>

using namespace std;

BB_InstanceSource::BB_InstanceSource(GroupType groupType, const BB_InstanceContext &context) :
    m_groupType(groupType), BB_Instance(context)
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
    if (m_stopThread)
    {
        m_stopThread = true;
        m_thread->Join();
    }

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

void BB_InstanceSource::run()
{
    while(!m_stopThread)
    {
        // Every 10 sec.
        Sleep(10000);

        try
        {
            // Read config
            BB_GroupElementConfig config = BB_ConfigMgr::Instance().GetGroupElementConfig(m_groupType, L"TODO"/*m_name*/);

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
        }
        catch(BB_Exception excp)
        {
            // Not found in the list
            continue;
        }
    }
}
