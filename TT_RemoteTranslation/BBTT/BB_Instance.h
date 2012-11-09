#ifndef _BB_INSTANCE_H_
#define _BB_INSTANCE_H_

#pragma once

#ifdef WIN32
#include <windows.h>
#endif
#include <sys/stat.h>
#include <../TeamTalk/TeamTalk4.h>
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include <stdlib.h>
#include <vector>
#include "BB_ClientConfigMgr.h"
#include "IRunnable.h"
#include "BB_Thread.h"
#include "Utils/BB_Window.h"

const std::wstring BB_VIDEO_WINDOW_CLASS(L"BBVideoWindowClass");
const std::wstring BB_VIDEO_WINDOW_CHANNEL(L"Video Channel");

struct BB_InstanceContext
{
	std::wstring m_IP;
	int m_TCP;
	int m_UDP;
	std::wstring m_srvPsw;
	std::wstring m_srvUser;
	std::wstring m_srvUserPsw;
	std::wstring m_nickName;
	std::wstring m_audioDir;

    INT32 m_inputSoundDevId;
    INT32 m_outputSoundDevId;

	std::wstring m_channelName;
	INT32 channelId;
};

const INT32 ROOT_PARENT_ID(1);
const std::wstring DEFAULT_AUDIO_STORAGE(L"");

struct BB_Channel
{
	std::wstring name;
	INT32 id;
	INT32 parentId;
};

struct BB_SoundDevice
{
	std::wstring m_deviceName;
    std::wstring m_deviceId;
	bool m_isOutputDevice;
	bool m_isSoundSystemWin;
    bool m_isDefault;
	INT32 m_id;
};

struct BB_ChannelUser
{
    std::wstring m_userName;
    INT32 m_id;
    bool m_isActive;
    bool m_isVideo;
};

class BB_Instance : public IRunnable
{
public:
	BB_Instance(const BB_InstanceContext &context);
	~BB_Instance(void);

    // the thread procedure
    virtual void run();

	// We don't want to call TT functions in Ctor & Dtor
	// Use init and finalize instead
    void init();
	void finalize();
    void getInstance();

    void initSoundDevices();
    void closeSoundDevices();
    void SetAudioLevels();
    void EnableTransmition();
	
    void getChannels(std::vector<BB_Channel> &channels);
    void getSoundDevices(std::vector<BB_SoundDevice> &soundDevs);
    void getUsers(std::vector<BB_ChannelUser> &userList);

    // Operations
    void StartSoundLoopbackTest(INT32 inputSoundDevId, INT32 outputSoundDevId);
    void StopSoundLoopbackTest();
    void StartTargetSoundLoopbackTest(const AGC &agc, bool bEnableDenoise, INT32 maxNoiseSuppress, bool bEchoCancel);
    void StopTargetSoundLoopbackTest();
    void MuteMicrophone(bool bMute);
    void MuteTarget(bool bMute);
    void UpdateVolumeLevel(int volumeLevel);
    void UpdateMicrophoneGainLevel(int gainLevel);
    void UpdateVideoQuality(int videoQuality);
    void EnableDenoising(bool bEnable);
    void EnableEchoCancellation(bool bEnable);
    void EnableVoiceActivation(bool bEnable, int voiceactSlider = 0);
    void SetAGCEnable(bool bEnable, const AGC *agc = NULL);
    void GetMicrophoneLevel(int &level);

    void OpenVideoWindow(HWND hWnd);

private:
		
    static void GetDroppedFrames(int videoQuality, std::vector<int>& droppedFrames, int seed);
    static bool IsFrameDropped(int frameIdx, std::vector<int>& droppedFrames);

    void joinChannel();
    void setInstProp();

	void processTTMessage(const TTMessage& msg);

    void StopVideoThreads();

	TTInstance* m_ttInst;

	BB_InstanceContext m_context;

	INT32 m_channelId;

    std::vector<BB_ChannelUser> m_UserList;

    // Used for video channel
    BB_Window *m_videoWin;
    Thread *m_videoWinThread;
    Thread *m_videoLoopThread;
    bool m_stopThread;
    HWND m_hWnd;
};


#endif

