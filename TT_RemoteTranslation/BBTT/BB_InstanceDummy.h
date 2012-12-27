#pragma once

#ifdef WIN32
#include <windows.h>
#endif
#include <../TeamTalk/TeamTalk4.h>
#include "IRunnable.h"
#include "BB_Thread.h"
#include "BB_Instance.h"

const INT32 MESSAGE_TIMEOUT(5000);

class BB_InstanceDummy : public BB_Instance, public IRunnable
{
public:
    BB_InstanceDummy(const BB_InstanceContext &context);
    ~BB_InstanceDummy(void);

    // the thread procedure
    virtual void run();

    virtual void init();
    virtual void finalize();

    void initSoundDevices();
    void closeSoundDevices();

    bool isConnectionLost() { return m_isConnectionLost; }
    void ClearConnectionLostFlag() { m_isConnectionLost = false; }

    void StartHandleMessages();
    void StopHandleMessages();

    // Operations
    void StartSoundLoopbackTest(INT32 inputSoundDevId, INT32 outputSoundDevId);
    void StopSoundLoopbackTest();
    void StartTargetSoundLoopbackTest(const AGC &agc, bool bEnableDenoise, INT32 maxNoiseSuppress, bool bEchoCancel,
        INT32 inputSoundDevId, INT32 outputSoundDevId);
    void StopTargetSoundLoopbackTest();

private:

    Thread *m_msgThread;
    bool m_stopThread;
    bool m_isConnectionLost;
};


