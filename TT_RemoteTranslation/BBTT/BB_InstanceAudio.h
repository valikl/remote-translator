#pragma once

#ifdef WIN32
#include <windows.h>
#endif
#include <../TeamTalk/TeamTalk4.h>
#include "BB_Instance.h"
#include "IRunnable.h"
#include "BB_Thread.h"
#include "IWriter.h"

class BB_InstanceAudio : public BB_Instance,  public IRunnable
{
public:
    BB_InstanceAudio(const BB_InstanceContext &context);
    ~BB_InstanceAudio(void);

    // We don't want to call TT functions in Ctor & Dtor
	// Use init and finalize instead
    virtual void init();
    virtual void finalize();
    // Return users list
    virtual void getUsers(std::vector<BB_ChannelUser> &userList);

    void initSoundDevices();
    void closeSoundDevices();

    // Operations
    void MuteMicrophone(bool bMute);
    void MuteTarget(bool bMute);
    void UpdateVolumeLevel(int volumeLevel);
    void UpdateMicrophoneGainLevel(int gainLevel);
    void EnableDenoising(bool bEnable);
    void EnableEchoCancellation(bool bEnable);
    void EnableVoiceActivation(bool bEnable, int voiceactSlider = 0);
    void SetAGCEnable(bool bEnable, const AGC *agc = NULL);
    void GetMicrophoneLevel(int &level);

    ///chat functions
    // the thread procedure
    virtual void run();
    void StartChat(IWriter *writer, IWriter *adminWriter);
    void SendMessage(std::wstring &txtmsg, bool isAdminChat);
    void StopChatThreads();
    bool SetAdminUser();

private:

    bool m_isMuted;

    void updateUserGainLevel(int volume);

    //chat properties
    Thread *m_audioLoopThread;
    bool m_stopThread;
    User adminUser;

    IWriter *m_writer;
    IWriter *m_adminWriter;
};


