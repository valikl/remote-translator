#include "BB_GroupMgr.h"
#include "Utils/Utils.h"
#include "Utils/Lock.h"
#include "Utils/BB_Exception.h"

using namespace std;

template<class T>
void BB_GroupMgr<T>::init()
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

template<class T>
void BB_GroupMgr<T>::finalize()
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

template<class T>
void BB_GroupMgr<T>::RemoveInstance(const std::wstring name)
{
    Lock lock(m_cs);

    typename std::map<wstring, T *>::const_iterator it = m_elements.find(name);
    if (it != m_elements.end())
    {
        T *inst = (*it).second;
        inst->finalize();
        delete inst;
        m_elements.erase(it);
    }
}

template<class T>
void BB_GroupMgr<T>::AddInstance(const wstring name, const wstring inputSoundDevId, const wstring outputSoundDevId)
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

    try
    {
        T inst = new T(context);
        inst->init();
        m_elements.insert(pair<wstring, T *>(name, inst));
    }
    catch(BB_Exception excp)
    {
        lock.Unlock();
        RemoveInstance(name);
        THROW_EXCEPT(excp.GetInfo());
    }
}


template<class T>
void BB_GroupMgr<T>::InitInstanceContext(ConnectionConfig &context)
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

template<class T>
bool BB_GroupMgr<T>::FindSoundDev(const wstring deviceId, bool isSoundSystemWin, BB_SoundDevice &soundDevice)
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
