#pragma once

#include <list>
#include <string>

#include "BB_Instance.h"
#include "BB_ConfigMgr.h"
#include "BB_GroupMgr.h"
#include "BB_InstanceReceiver.h"

const std::wstring RECEIVER_CHANNEL_PREFIX(L"RCV_");

class BB_GroupMgrReceiver : public BB_GroupMgr<BB_InstanceReceiver>
{
public:
    ~BB_GroupMgrReceiver(void);

    // Returns the instance of the singleton
    static BB_GroupMgrReceiver &Instance();

    // Operations
    void UpdateVolumeLevel(const std::wstring name, int volumeLevel);
    int GetVolumeLevel(const std::wstring name);

private:
    BB_GroupMgrReceiver();
    BB_GroupMgrReceiver(const BB_GroupMgrReceiver &);
    const BB_GroupMgrReceiver &operator=(const BB_GroupMgrReceiver &);
};

