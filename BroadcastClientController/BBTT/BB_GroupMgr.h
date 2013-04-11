#pragma once

#include <list>
#include <string>

#include "BB_Instance.h"
#include "BB_ConfigMgr.h"
#include "Utils/CriticalSection.h"

template<class T>
class BB_GroupMgr
{
public:
    BB_GroupMgr() {};
    ~BB_GroupMgr() {};

    void init();
    void finalize();

    std::vector<BB_SoundDevice> getSoundDevices() { return m_soundDevList; }

    void AddInstance(const std::wstring name, const std::wstring inputSoundDevId, const std::wstring outputSoundDevId);
    void RemoveInstance(const std::wstring name);

protected:

    void InitInstanceContext(ConnectionConfig &context);

    bool FindSoundDev(const std::wstring deviceId, bool isSoundSystemWin, BB_SoundDevice &soundDevice);

    T *FindInstance(const std::wstring name)
    {
        for (unsigned int i=0; i < m_elements.size(); i++)
        {
            //if (m_elements[i].GetName() == name)
            {
                return m_elements[i];
            }
        }
        return NULL;
    }

    // Sound Devices List
    std::vector<BB_SoundDevice> m_soundDevList;

    GroupType m_groupType;
    std::vector<T *> m_elements;

    BB_CriticalSection m_cs;
};

