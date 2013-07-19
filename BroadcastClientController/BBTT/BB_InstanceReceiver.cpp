#include "BB_InstanceReceiver.h"
#include "Utils/BB_Exception.h"
#include "Utils/Utils.h"
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <vector>

using namespace std;

BB_InstanceReceiver::BB_InstanceReceiver(GroupType groupType, const BB_InstanceContext &context, const wstring name, IInstStatus* instStat) :
    m_groupType(GROUP_TYPE_RECEIVERS), m_name(name), m_instStat(instStat), BB_Instance(context)
{
}

BB_InstanceReceiver::~BB_InstanceReceiver(void)
{
}

void BB_InstanceReceiver::init()
{
    BB_Instance::init();
    initSoundDevices();

    m_stopThread = false;
    m_thread = new Thread(this);
}

void BB_InstanceReceiver::finalize()
{
    m_stopThread = true;
    m_thread->Join();

    closeSoundDevices();
    BB_Instance::finalize();
}

void BB_InstanceReceiver::closeSoundDevices()
{
    TT_CloseSoundDuplexDevices(m_ttInst);
    TT_CloseSoundOutputDevice(m_ttInst);
    TT_CloseSoundInputDevice(m_ttInst);
}

void BB_InstanceReceiver::initSoundDevices()
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

int BB_InstanceReceiver::gainLevel(int refVolume)
{
    if(refVolume <= SOUND_VOLUME_MAX)
    {
        return SOUND_GAIN_DEFAULT;
    }

    float gain = refVolume / (float)SOUND_VOLUME_MAX;
    gain *= SOUND_GAIN_DEFAULT;
    return gain;
}

void BB_InstanceReceiver::updateUserGainLevel(int volume)
{
    int gain = gainLevel(volume);

    std::vector<BB_ChannelUser> users;
    getUsers(users);

    for(unsigned int i=0; i < users.size(); i++)
    {
        BB_ChannelUser user = users[i];
        if(volume <= SOUND_VOLUME_MAX)
        {
            //disable soft gain
            if (!TT_SetUserGainLevel(m_ttInst, user.m_id, SOUND_GAIN_DEFAULT))
            {
                THROW_EXCEPT("Set user gain level failed");
            }
        }
        else
        {
            if (!TT_SetUserGainLevel(m_ttInst, user.m_id, gain))
            {
                THROW_EXCEPT("Set user gain level failed");
            }
        }
    }
}

void BB_InstanceReceiver::UpdateVolumeLevel(int volumeLevel)
{
    if (!TT_SetSoundOutputVolume(m_ttInst, volumeLevel))
    {
        THROW_EXCEPT("Update volume level failed");
    }
    updateUserGainLevel(volumeLevel);
}

int BB_InstanceReceiver::GetVolumeLevel()
{
    return TT_GetSoundOutputVolume(m_ttInst);
}

void BB_InstanceReceiver::run()
{
    // Wait for configuration to be set by GUI for the first time
    Sleep(5000);

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

        // Read config
        BB_GroupElementConfig config = BB_ConfigMgr::Instance().GetGroupElementConfig(m_groupType, m_name);

        int vol = GetVolumeLevel();
        if (GetVolumeLevel() != config.m_SrcVolumeLevel)
        {
            try
            {
                UpdateVolumeLevel(config.m_SrcVolumeLevel);
                m_instStat->setError(INST_ERR_FIXED_VOL_LEVEL);
            }
            catch(BB_Exception excp)
            {
                m_instStat->setError(INST_ERR_VOL_LEVEL);
            }
        }
    }
}
