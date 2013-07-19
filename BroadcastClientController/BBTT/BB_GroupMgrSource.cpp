#include "BB_GroupMgrSource.h"
#include "Utils/Lock.h"
#include "Utils/BB_Exception.h"

using namespace std;

BB_GroupMgrSource::BB_GroupMgrSource(GroupType groupType)
{
    m_groupType = groupType;
    if (groupType == GROUP_TYPE_SOURCES)
    {
        m_channelPrefix = SRC_CHANNEL_PREFIX;
    }
    else
    {
        m_channelPrefix = RESTRICTED_CHANNEL_PREFIX;
    }
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
    BB_ConfigMgr::Instance().SetGroupElementMicGainLevel(m_groupType, name, gainLevel);
}

int BB_GroupMgrSource::GetMicrophoneGainLevel(const std::wstring name)
{
    Lock lock(m_cs);

    BB_InstanceSource *inst = FindInstance(name);

    if (inst == NULL)
    {
        THROW_EXCEPT("Cannot return microphone level. Group instance is not connected");
    }
    return inst->GetMicrophoneGainLevel();
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
    BB_ConfigMgr::Instance().SetGroupElementNoiseCancel(m_groupType, name, bEnable);
}


bool BB_GroupMgrSource::IsDenoisingEnabled(const std::wstring name)
{
    Lock lock(m_cs);

    BB_InstanceSource *inst = FindInstance(name);

    if (inst == NULL)
    {
        THROW_EXCEPT("Cannot get denosing. Group instance is not connected");
    }

    return inst->IsDenoisingEnabled();
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
    BB_ConfigMgr::Instance().SetGroupElementEchoCancel(m_groupType, name, bEnable);
}

bool BB_GroupMgrSource::IsEchoCancellationEnabled(const std::wstring name)
{
    Lock lock(m_cs);

    BB_InstanceSource *inst = FindInstance(name);

    if (inst == NULL)
    {
        THROW_EXCEPT("Cannot get echo cancellation. Group instance is not connected");
    }
    return inst->IsEchoCancellationEnabled();
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
    BB_ConfigMgr::Instance().SetGroupElementAGC(m_groupType, name, *agc);
}

bool BB_GroupMgrSource::GetAGC(const std::wstring name, AGC &agc)
{
    Lock lock(m_cs);

    BB_InstanceSource *inst = FindInstance(name);

    if (inst == NULL)
    {
        THROW_EXCEPT("Cannot update echo cancellation. Group instance is not connected");
    }
    return inst->GetAGC(agc);
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
    BB_ConfigMgr::Instance().SetGroupElementEnableVoiceActivation(m_groupType, name, bEnable);
    BB_ConfigMgr::Instance().SetGroupElementVoiceActivationLevel(m_groupType, name, voiceactSlider);
}

int BB_GroupMgrSource::IsVoiceActivationEnabled(const std::wstring name)
{
    Lock lock(m_cs);

    BB_InstanceSource *inst = FindInstance(name);

    if (inst == NULL)
    {
        THROW_EXCEPT("Cannot get voice activation. Group instance is not connected");
    }
    return inst->IsVoiceActivationEnabled();
}


