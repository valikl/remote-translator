#pragma once

#include <list>
#include <string>

#include "BB_Instance.h"
#include "BB_ConfigMgr.h"
#include "BB_GroupMgr.h"
#include "BB_InstanceSource.h"

const std::wstring SRC_CHANNEL_PREFIX(L"SRC_");
const std::wstring RESTRICTED_CHANNEL_PREFIX(L"RST_");

class BB_GroupMgrSource : BB_GroupMgr<BB_InstanceSource>
{
public:
    ~BB_GroupMgrSource(void);

    // Returns the instance of the singleton
    static BB_GroupMgrSource &Instance(GroupType groupType);

    // Operations
    void UpdateMicrophoneGainLevel(const std::wstring name, int gainLevel);
    void EnableDenoising(const std::wstring name, bool bEnable);
    void EnableEchoCancellation(const std::wstring name, bool bEnable);
    void EnableVoiceActivation(const std::wstring name, bool bEnable, int voiceactSlider = 0);
    void SetAGCEnable(const std::wstring name, bool bEnable, const AGC *agc);
    void GetMicrophoneLevel(const std::wstring name, int &level);

private:
    BB_GroupMgrSource(GroupType groupType);
    BB_GroupMgrSource(const BB_GroupMgrSource &);
    const BB_GroupMgrSource &operator=(const BB_GroupMgrSource &);
};


