#include "BB_InstanceDummy.h"
#include "Utils/BB_Exception.h"
#include "Utils.h"
#include <vector>

using namespace std;

BB_InstanceDummy::BB_InstanceDummy(const BB_InstanceContext &context) :
    BB_Instance(context)
{
    m_msgThread = NULL;
    m_stopThread = false;
    m_isConnectionLost = false;
}

BB_InstanceDummy::~BB_InstanceDummy(void)
{
    StopHandleMessages();
}

void BB_InstanceDummy::init()
{
    BB_Instance::init();
    initSoundDevices();
}

void BB_InstanceDummy::finalize()
{
    closeSoundDevices();
    BB_Instance::finalize();
}

void BB_InstanceDummy::closeSoundDevices()
{
    TT_CloseSoundDuplexDevices(m_ttInst);
    TT_CloseSoundOutputDevice(m_ttInst);
    TT_CloseSoundInputDevice(m_ttInst);
}

void BB_InstanceDummy::initSoundDevices()
{
    if (!TT_InitSoundDuplexDevices(m_ttInst, m_context.m_inputSoundDevId,
            m_context.m_outputSoundDevId))
    {
        THROW_EXCEPT("Sound duplex devices initialization failed");
    }

    ClientFlags flags = TT_GetFlags(m_ttInst);
    if (!(flags & CLIENT_SNDINOUTPUT_DUPLEX) && (flags & CLIENT_SNDOUTPUT_READY) &&(flags & CLIENT_SNDINPUT_READY))
    {
        THROW_EXCEPT("Cannot initialize Duplex mode");
    }

    // Init volume level to 0
    if (!TT_SetSoundOutputVolume(m_ttInst, 0))
    {
        THROW_EXCEPT("Volume level initialization failed");
    }
}

void BB_InstanceDummy::StartSoundLoopbackTest(INT32 inputSoundDevId, INT32 outputSoundDevId)
{
    if (!TT_InitSoundInputDevice(m_ttInst, inputSoundDevId))
    {
        THROW_EXCEPT("Sound input device initialization failed");
    }

    if (!TT_InitSoundOutputDevice(m_ttInst, outputSoundDevId))
    {
        THROW_EXCEPT("Sound output device initialization failed");
    }

    if (!TT_StartSoundLoopbackTest(m_ttInst, inputSoundDevId, outputSoundDevId, 16000, 2))
    {
        TT_CloseSoundOutputDevice(m_ttInst);
        TT_CloseSoundInputDevice(m_ttInst);
        THROW_EXCEPT("Cannot start sound loopback test");
    }
}

void BB_InstanceDummy::StopSoundLoopbackTest()
{
    if (!TT_StopSoundLoopbackTest(m_ttInst))
    {
        THROW_EXCEPT("Cannot stop sound loopback test");
    }
    TT_CloseSoundOutputDevice(m_ttInst);
    TT_CloseSoundInputDevice(m_ttInst);
}

void BB_InstanceDummy::StartTargetSoundLoopbackTest(const AGC &agc, bool bEnableDenoise, INT32 maxNoiseSuppress, bool bEchoCancel,
    INT32 inputSoundDevId, INT32 outputSoundDevId)
{
    if (!TT_InitSoundDuplexDevices(m_ttInst, inputSoundDevId, outputSoundDevId))
    {
        THROW_EXCEPT("Sound devices initialization failed");
    }

    AudioConfig audioConfig;
    audioConfig.bEnableAGC = agc.m_enable;
    audioConfig.nGainLevel = agc.m_gainLevel;
    audioConfig.nMaxIncDBSec = agc.m_maxIncrement;
    audioConfig.nMaxDecDBSec = agc.m_maxDecrement;
    audioConfig.nMaxGainDB = agc.m_maxGain;
    audioConfig.bEnableDenoise = bEnableDenoise;
    audioConfig.nMaxNoiseSuppressDB = maxNoiseSuppress;

    if (!TT_StartSoundLoopbackTestEx(m_ttInst, inputSoundDevId, outputSoundDevId,
        16000, 2, &audioConfig, bEchoCancel))
    {
        TT_CloseSoundDuplexDevices(m_ttInst);
        THROW_EXCEPT("Cannot start extended sound loopback test");
    }
}

void BB_InstanceDummy::StopTargetSoundLoopbackTest()
{
    if (!TT_StopSoundLoopbackTest(m_ttInst))
    {
        THROW_EXCEPT("Cannot stop sound loopback test");
    }
    TT_CloseSoundDuplexDevices(m_ttInst);
}

void BB_InstanceDummy::StartHandleMessages()
{
    // Create message handle loop thread
    m_msgThread = new Thread(this);
}

void BB_InstanceDummy::StopHandleMessages()
{
    if (m_msgThread != NULL)
    {
        // Stop the thread
        m_stopThread = true;
        m_msgThread->Join();
    }
}

void BB_InstanceDummy::run()
{
    TTMessage msg;
    int timeout = MESSAGE_TIMEOUT;
    while(TT_GetMessage(m_ttInst, &msg, &timeout))
    {
        if (msg.wmMsg == WM_TEAMTALK_CON_LOST)
        {
            m_isConnectionLost = true;
        }

        if (m_stopThread)
        {
            return;
        }
    }
}

