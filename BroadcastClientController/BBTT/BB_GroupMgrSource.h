#pragma once

#include <list>
#include <string>

#include "BB_Instance.h"
#include "BB_ConfigMgr.h"
#include "BB_GroupMgr.h"
#include "BB_InstanceSource.h"

const std::wstring SRC_CHANNEL_PREFIX(L"SRC_");
const std::wstring RESTRICTED_CHANNEL_PREFIX(L"RST_");

class BB_GroupMgrSource : public BB_GroupMgr<BB_InstanceSource>
{
public:
    ~BB_GroupMgrSource(void);

    // Returns the instance of the singleton
    static BB_GroupMgrSource &Instance(GroupType groupType);

    // Operations
    void UpdateMicrophoneGainLevel(const std::wstring name, int gainLevel);
    int GetMicrophoneGainLevel(const std::wstring name);

    int GetMicrophoneLevel(const std::wstring name);

    void EnableDenoising(const std::wstring name, bool bEnable);
    bool IsDenoisingEnabled(const std::wstring name);

    void EnableEchoCancellation(const std::wstring name, bool bEnable);
    bool IsEchoCancellationEnabled(const std::wstring name);

    void EnableVoiceActivation(const std::wstring name, bool bEnable, int voiceactSlider = 0);
    // Return -1 if disabled, otherwise return voiceactSlider
    int IsVoiceActivationEnabled(const std::wstring name);

    void SetAGCEnable(const std::wstring name, bool bEnable, const AGC *agc);
    // Return true if enabled
    bool GetAGC(const std::wstring name, AGC &agc);

private:
    BB_GroupMgrSource(GroupType groupType);
    BB_GroupMgrSource(const BB_GroupMgrSource &);
    const BB_GroupMgrSource &operator=(const BB_GroupMgrSource &);
};


