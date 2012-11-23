#pragma once

#ifdef WIN32
#include <windows.h>
#endif
#include <../TeamTalk/TeamTalk4.h>
#include "BB_Instance.h"

class BB_InstanceAudio : public BB_Instance
{
public:
    BB_InstanceAudio(const BB_InstanceContext &context);
    ~BB_InstanceAudio(void);

    // We don't want to call TT functions in Ctor & Dtor
	// Use init and finalize instead
    virtual void init();
    virtual void finalize();

    void initSoundDevices();
    void closeSoundDevices();

    // Operations
    void StartSoundLoopbackTest(INT32 inputSoundDevId, INT32 outputSoundDevId);
    void StopSoundLoopbackTest();
    void StartTargetSoundLoopbackTest(const AGC &agc, bool bEnableDenoise, INT32 maxNoiseSuppress, bool bEchoCancel);
    void StopTargetSoundLoopbackTest();
    void MuteMicrophone(bool bMute);
    void MuteTarget(bool bMute);
    void UpdateVolumeLevel(int volumeLevel);
    void UpdateMicrophoneGainLevel(int gainLevel);
    void EnableDenoising(bool bEnable);
    void EnableEchoCancellation(bool bEnable);
    void EnableVoiceActivation(bool bEnable, int voiceactSlider = 0);
    void SetAGCEnable(bool bEnable, const AGC *agc = NULL);
    void GetMicrophoneLevel(int &level);
};

