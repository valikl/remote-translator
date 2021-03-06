#pragma once

#ifdef WIN32
#include <windows.h>
#endif
#include <string>
#include "TT_Include/TeamTalk4.h"
#include "BB_ConfigMgr.h"
#include "BB_Instance.h"
#include "Utils/IRunnable.h"
#include "Utils/BB_Thread.h"
#include "GUI/iinststatus.h"

class BB_InstanceReceiver : public BB_Instance, public IRunnable
{
public:
    BB_InstanceReceiver(GroupType groupType, const BB_InstanceContext &context, const std::wstring name, IInstStatus* instStat);
    ~BB_InstanceReceiver(void);

    // We don't want to call TT functions in Ctor & Dtor
	// Use init and finalize instead
    virtual void init();
    virtual void finalize();

    // Thread procedure
    virtual void run();

    void initSoundDevices();
    void closeSoundDevices();

    // Operations
    void UpdateVolumeLevel(int volumeLevel);
    int GetVolumeLevel();

    void UpdateSoundDev(int id, bool isInput);

private:
    // TODO: add functions transmission checkbox enabling, change sound card,
    // test sound card, get line-in signal, watchdog for configuration parameters, change instance language, change instance channel

    INT32 GetUserId();

    void updateUserGainLevel(int volume);
    int gainLevel(int refVolume);

    GroupType m_groupType;
    std::wstring m_name;

    IInstStatus* m_instStat;

    Thread *m_thread;
    bool m_stopThread;
};


