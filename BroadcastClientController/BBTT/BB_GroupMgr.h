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

using namespace std;

template<class T>
class BB_GroupMgr
{
public:
    BB_GroupMgr() { TT_SetLicenseInformation(L"Bnei Baruch", 1600664704); }
    ~BB_GroupMgr() {};

    void init()
    {
        // Build Sound device list
        try
        {
            BB_InstanceContext context;
            InitInstanceContext(context);
            BB_Instance inst(context);
            inst.init();
            m_soundDevList.clear();
            inst.getSoundDevices(m_soundDevList);
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

    void AddInstance(const std::wstring name, const std::wstring inputSoundDevId, const std::wstring outputSoundDevId)
    {
        Lock lock(m_cs);

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

        context.m_nickName = m_channelPrefix + BB_ConfigMgr::Instance().GetGroupElementConfig(m_groupType, name).m_nickName;
        context.m_channelName = BB_ConfigMgr::Instance().GetGroupElementConfig(m_groupType, name).m_channelName;

        // Get channel id
        std::vector<BB_Channel> channels;
        BB_Instance *tempInst = new BB_Instance(context);
        tempInst->login();
        tempInst->getChannels(channels);
        tempInst->finalize();
        delete tempInst;

        for (unsigned int i=0; i < channels.size(); i++)
        {
            if (channels[i].path == context.m_channelName)
            {
                context.channelId = channels[i].id;
                break;
            }
        }

        //try
        {
            T *inst = new T(m_groupType, context, name);
            inst->init();
            m_elements.insert(pair<wstring, T *>(name, inst));
        }
        //catch(BB_Exception excp)
        //{
        //    lock.Unlock();
        //    RemoveInstance(name);
        //     THROW_EXCEPT(excp.GetInfo());
        //}
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

    GroupType m_groupType;
    std::map<std::wstring, T *> m_elements;

    std::wstring m_channelPrefix;

    BB_CriticalSection m_cs;
};

