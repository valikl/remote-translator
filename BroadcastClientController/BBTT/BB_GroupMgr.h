#pragma once

#include <list>
#include <map>
#include <vector>
#include <string>

#include "BB_Instance.h"
#include "BB_ConfigMgr.h"
#include "Utils/CriticalSection.h"
#include "BB_GroupMgr.h"
#include "Utils/Utils.h"
#include "Utils/Lock.h"
#include "Utils/BB_Exception.h"
#include "GUI/iinststatus.h"

using namespace std;

template<class T>
class BB_GroupMgr
{
public:
    BB_GroupMgr() { TT_SetLicenseInformation(L"Bnei Baruch", 1600664704); }
    ~BB_GroupMgr() {};

    void init()
    {        
        try
        {
            BB_InstanceContext context;
            InitInstanceContext(context);
            BB_Instance inst(context);
            inst.init();

            // Build Sound device list
            m_soundDevList.clear();
            inst.getSoundDevices(m_soundDevList);

            // Build Channels list
            m_channels.clear();
            inst.getChannels(m_channels);

            inst.finalize();
        }
        catch(BB_Exception excp)
        {
            THROW_EXCEPT(excp.GetInfo());
        }
    }
    void finalize()
    {
        Lock lock(m_cs);

        typename map<wstring, T *>::iterator it;
        for (it = m_elements.begin(); it != m_elements.end(); ++it)
        {
            T *inst = (*it).second;
            inst->finalize();
            delete inst;
        }
        m_elements.clear();
    }

    std::vector<BB_SoundDevice> getSoundDevices() { return m_soundDevList; }

    void AddInstance(const std::wstring name, const std::wstring inputSoundDevId, const std::wstring outputSoundDevId, IInstStatus* instStat)
    {
        if (FindInstance(name) != NULL)
        {
            // Already connected
            THROW_EXCEPT("Instance already connected");
        }

        BB_InstanceContext context;
        InitInstanceContext(context);

        BB_SoundDevice soundDevice;
        if (!FindSoundDev(inputSoundDevId, BB_ConfigMgr::Instance().GetGroupElementConfig(m_groupType, name).m_isSoundSystemWin, soundDevice))
        {
            THROW_EXCEPT("Sound input device not found");
        }
        context.m_inputSoundDevId = soundDevice.m_id;

        if (!FindSoundDev(outputSoundDevId, BB_ConfigMgr::Instance().GetGroupElementConfig(m_groupType, name).m_isSoundSystemWin, soundDevice))
        {
            THROW_EXCEPT("Sound output device not found");
        }
        context.m_outputSoundDevId = soundDevice.m_id;

        context.m_nickName = BB_ConfigMgr::Instance().GetGroupElementConfig(m_groupType, name).m_nickName;

        context.m_channelName = L"";
        if (BB_ConfigMgr::Instance().GetConnectionConfig(m_groupType).m_srcPath != L"")
        {
            // Not root
            context.m_channelName = L"/" + BB_ConfigMgr::Instance().GetConnectionConfig(m_groupType).m_srcPath;
        }
        context.m_channelName += L"/" + BB_ConfigMgr::Instance().GetGroupElementConfig(m_groupType, name).m_channelName + L"/";

        // Get channel id
        for (unsigned int i=0; i < m_channels.size(); i++)
        {
            if (m_channels[i].path == context.m_channelName)
            {
                context.channelId = m_channels[i].id;
                break;
            }
        }

        Lock lock(m_cs);

        // Add new instance
        T *inst = new T(m_groupType, context, name, instStat);
        inst->init();
        m_elements.insert(pair<wstring, T *>(name, inst));
    }

    void RemoveInstance(const std::wstring name)
    {
        Lock lock(m_cs);

        typename std::map<wstring, T *>::const_iterator it = m_elements.find(name);
        if (it != m_elements.end())
        {
            T *inst = (*it).second;
            inst->finalize();
            delete inst;
            m_elements.erase(name);
        }
    }

    void UpdateNickName(const std::wstring name, const std::wstring nickName)
    {
        Lock lock(m_cs);

        T *inst = FindInstance(name);
        if (inst == NULL)
        {
            THROW_EXCEPT("Cannot update nick name. Group instance is not connected");
        }

        inst->UpdateNickName(nickName);
        BB_ConfigMgr::Instance().SetGroupElementNickName(m_groupType, name, nickName);
    }

    void UpdateSoundDev(const std::wstring name, int id, bool isInput)
    {
        Lock lock(m_cs);

        T *inst = FindInstance(name);
        if (inst == NULL)
        {
            THROW_EXCEPT("Cannot update sound device. Group instance is not connected");
        }

        inst->UpdateSoundDev(id, isInput);
        if (isInput)
        {
            BB_ConfigMgr::Instance().SetGroupElementInputSoundDevId(m_groupType, name, id);
        }
        else
        {
            BB_ConfigMgr::Instance().SetGroupElementOutputSoundDevId(m_groupType, name, id);
        }
    }

protected:

    void InitInstanceContext(BB_InstanceContext &context)
    {
        ConnectionConfig config = BB_ConfigMgr::Instance().GetConnectionConfig(m_groupType);

        context.m_TCP = config.m_TCP;
        context.m_IP = config.m_IP;
        context.m_UDP = config.m_UDP;
        context.m_srvPsw = config.m_srvPsw;
        context.m_srvUser = config.m_srvUser;
        context.m_srvUserPsw = config.m_srvUserPsw;
        context.m_audioDir = DEFAULT_AUDIO_STORAGE;
    }

    bool FindSoundDev(const std::wstring deviceId, bool isSoundSystemWin, BB_SoundDevice &soundDevice)
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

    T *FindInstance(const std::wstring name)
    {
        typename std::map<std::wstring, T *>::iterator it = m_elements.find(name);
        if (it != m_elements.end())
        {
            return (*it).second;
        }
        return NULL;
    }

    // Sound Devices List
    std::vector<BB_SoundDevice> m_soundDevList;

    // Channels list
    std::vector<BB_Channel> m_channels;

    GroupType m_groupType;
    std::map<std::wstring, T *> m_elements;

    std::wstring m_channelPrefix;

    BB_CriticalSection m_cs;
};

