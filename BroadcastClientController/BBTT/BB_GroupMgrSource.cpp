#include "BB_GroupMgrSource.h"
#include "Utils/Lock.h"
#include "Utils/BB_Exception.h"

using namespace std;

BB_GroupMgrSource::BB_GroupMgrSource(GroupType groupType)
{
    m_groupType = groupType;
}

BB_GroupMgrSource::~BB_GroupMgrSource(void)
{
}

BB_GroupMgrSource& BB_GroupMgrSource::Instance(GroupType groupType)
{
    static BB_GroupMgrSource instanceSrc(GROUP_TYPE_SOURCES);
    static BB_GroupMgrSource instanceRstr(GROUP_TYPE_RESTRICTED_SERVERS);
    if (groupType == GROUP_TYPE_SOURCES)
    {
        return instanceSrc;
    }
    else // GROUP_TYPE_RESTRICTED_SERVERS
    {
        return instanceRstr;
    }
}

void BB_GroupMgrSource::UpdateMicrophoneGainLevel(const std::wstring name, int gainLevel)
{
    Lock lock(m_cs);

    BB_InstanceSource *inst = FindInstance(name);

    if (inst == NULL)
    {
        THROW_EXCEPT("Cannot update microphone gain level. Group instance is not connected");
    }
    inst->UpdateMicrophoneGainLevel(gainLevel);
}

void BB_GroupMgrSource::EnableDenoising(const std::wstring name, bool bEnable)
{
    Lock lock(m_cs);

    BB_InstanceSource *inst = FindInstance(name);

    if (inst == NULL)
    {
        THROW_EXCEPT("Cannot update denosing. Group instance is not connected");
    }

    inst->EnableDenoising(bEnable);
}

void BB_GroupMgrSource::EnableEchoCancellation(const std::wstring name, bool bEnable)
{
    Lock lock(m_cs);

    BB_InstanceSource *inst = FindInstance(name);

    if (inst == NULL)
    {
        THROW_EXCEPT("Cannot update echo cancellation. Group instance is not connected");
    }
    inst->EnableEchoCancellation(bEnable);
}

void BB_GroupMgrSource::SetAGCEnable(const std::wstring name, bool bEnable, const AGC *agc)
{
    Lock lock(m_cs);

    BB_InstanceSource *inst = FindInstance(name);

    if (inst == NULL)
    {
        THROW_EXCEPT("Cannot update echo cancellation. Group instance is not connected");
    }
    inst->SetAGCEnable(bEnable, agc);
}

void BB_GroupMgrSource::EnableVoiceActivation(const std::wstring name, bool bEnable, int voiceactSlider)
{
    Lock lock(m_cs);

    BB_InstanceSource *inst = FindInstance(name);

    if (inst == NULL)
    {
        THROW_EXCEPT("Cannot update voice activation. Group instance is not connected");
    }
    inst->EnableVoiceActivation(bEnable, voiceactSlider);
}

void BB_GroupMgrSource::GetMicrophoneLevel(const std::wstring name, INT32 &level)
{
    Lock lock(m_cs);

    BB_InstanceSource *inst = FindInstance(name);

    if (inst == NULL)
    {
        THROW_EXCEPT("Cannot return microphone level. Group instance is not connected");
    }
    inst->GetMicrophoneLevel(level);
}

