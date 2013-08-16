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

class BB_InstanceSource : public BB_Instance, public IRunnable
{
public:
    BB_InstanceSource(GroupType groupType, const BB_InstanceContext &context, const std::wstring name, IInstStatus* instStat);
    ~BB_InstanceSource(void);

    // We don't want to call TT functions in Ctor & Dtor
	// Use init and finalize instead
    virtual void init();
    virtual void finalize();

    // Thread procedure
    virtual void run();

    void initSoundDevices();
    void closeSoundDevices();

    // Operations
    void UpdateMicrophoneGainLevel(int gainLevel);
    INT32 GetMicrophoneGainLevel();

    INT32 GetMicrophoneLevel();

    void EnableDenoising(bool bEnable);
    bool IsDenoisingEnabled();

    void EnableEchoCancellation(bool bEnable);
    bool IsEchoCancellationEnabled();

    void EnableVoiceActivation(bool bEnable, int voiceactSlider = 0);
    // Return -1 if disabled, otherwise return voiceactSlider
    int IsVoiceActivationEnabled();

    void SetAGCEnable(bool bEnable, const AGC *agc = NULL);
    // Return true if enabled
    bool GetAGC(AGC &agc);

    void UpdateSoundDev(int id, bool isInput);

private:
    // TODO: add functions transmission checkbox enabling, change sound card,
    // test sound card, get line-in signal, watchdog for configuration parameters, change instance language, change instance channel

    INT32 GetUserId();

    GroupType m_groupType;
    std::wstring m_name;

    IInstStatus* m_instStat;

    Thread *m_thread;
    bool m_stopThread;
};


