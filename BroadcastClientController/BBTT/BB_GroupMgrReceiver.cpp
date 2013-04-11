#include "BB_GroupMgrReceiver.h"
#include "BB_ConfigMgr.h"
#include "Utils/Lock.h"
#include "Utils/BB_Exception.h"

using namespace std;

BB_GroupMgrReceiver::BB_GroupMgrReceiver()
{
    m_groupType = GROUP_TYPE_RECEIVERS;
}

BB_GroupMgrReceiver::~BB_GroupMgrReceiver(void)
{
}

BB_GroupMgrReceiver& BB_GroupMgrReceiver::Instance()
{
    static BB_GroupMgrReceiver instance;
    return instance;
}

void BB_GroupMgrReceiver::UpdateVolumeLevel(const std::wstring name, int volumeLevel)
{
    Lock lock(m_cs);

    BB_InstanceReceiver *inst = FindInstance(name);

    if (inst == NULL)
    {
        THROW_EXCEPT("Cannot update volume level. Group instance is not connected");
    }

    inst->UpdateVolumeLevel(volumeLevel);
}




