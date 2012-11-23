#ifndef _BB_TRANSLATOR_H_
#define _BB_TRANSLATOR_H_

#pragma once

#include <list>
#include <string>

#include "BB_Instance.h"
#include "BB_ClientConfigMgr.h"
#include "BB_InstanceAudio.h"
#include "BB_InstanceVideo.h"
#include "Utils/CriticalSection.h"

const std::wstring VIDEO_CHANNEL_NAME(L"Video");
const std::wstring SOURCE_CHANNEL_NAME(L"Source");
const std::wstring SOUND_CHECK_CHANNEL_NAME(L"Sound Check");

const std::wstring SRC_CHANNEL_PREFIX(L"SRC_");
const std::wstring DST_CHANNEL_PREFIX(L"DST_");
const std::wstring VIDEO_CHANNEL_PREFIX(L"VIDEO_");

const std::wstring DST_SOUND_TEST_CHANNEL_NICKNAME(L"DstSoundTestUser");

const std::wstring HAPPENING_CHANNEL_DEFAULT_NAME(L"");

struct Happening
{
	std::wstring m_hapName;
	std::vector<std::wstring> m_srcChannels;
	std::vector<std::wstring> m_dstChannels;
	std::wstring m_videoChannel;
};

struct ChannelInfo
{
	std::wstring m_name;
	INT32 m_id;
};

struct HappeningEx
{
	ChannelInfo m_hapChannel;
	std::vector<ChannelInfo> m_srcChannels;
	std::vector<ChannelInfo> m_dstChannels;
	ChannelInfo m_videoChannel;
};

class BB_Translator
{
public:
	~BB_Translator(void);

    // Returns the instance of the singleton
    static BB_Translator &Instance();

	// connect to the server and get happenings
    void init();

    // disconnect etc.
    void finalize();

	std::vector<Happening> getHappenings() { return m_hapList; }
	//int setActiveHappening(std::string hapName);

	std::vector<BB_SoundDevice> getSoundDevices() { return m_soundDevList; }

    void connectHap(std::wstring hapName, std::wstring nickName, std::wstring srcName, std::wstring dstName,
        std::wstring inputSoundDevId, std::wstring outputSoundDevId);
    void disconnectHap();
    void getUsers(std::vector<BB_ChannelUser> &userList, bool isSource);

    void ReconnectSrcChannel(std::wstring hapName, std::wstring srcName);

    bool isConnected() { return m_isConnected; }

    // Operations
    void StartSoundLoopbackTest(std::wstring inputSoundDevId, std::wstring outputSoundDevId, bool m_isSoundSystemWin);
    void StopSoundLoopbackTest();
    void StartTargetSoundLoopbackTest(const AGC &agc, bool bEnableDenoise, INT32 maxNoiseSuppress, bool bEchoCancel);
    void StopTargetSoundLoopbackTest();
    // Disable/Enable my microphone
    void MuteMicrophone(bool bMute);
    // Mute other users in my channel
    void MuteTarget(bool bMute);
    void UpdateVolumeLevel(int volumeLevel, bool isSource);
    void UpdateMicrophoneGainLevel(int gainLevel);
    void EnableDenoising(bool bEnable);
    void EnableEchoCancellation(bool bEnable);
    // Target
    void EnableVoiceActivation(bool bEnable, int voiceactSlider = 0);
    // Microphone(target)
    void SetAGCEnable(bool bEnable, const AGC *agc = NULL);
    // Microphone(target)
    void GetMicrophoneLevel(INT32 &level);
    // Destination sound test
    void StartDstSoundTest();
    void StopDstSoundTest();

    // Video
    void OpenVideoWindow(HWND hWnd);

private:
    BB_Translator();
    BB_Translator(const BB_Translator &);
    const BB_Translator &operator=(const BB_Translator &);

	int initHapsList(const std::vector<BB_Channel> &channels);
	void initSoundDevicesList();

	bool findHap(HappeningEx &hap, std::wstring name);
	bool findSrcChannelId(const HappeningEx hap, std::wstring name, INT32 &channelId);
	bool findDstChannelId(const HappeningEx hap, std::wstring name, INT32 &channelId);
    bool findSoundDev(std::wstring deviceId, bool isSoundSystemWin, BB_SoundDevice &soundDevice);

    void initInstanceContext(BB_InstanceContext &context);

    BB_InstanceVideo *m_channelVideo;
    BB_InstanceAudio *m_channelSrc;
    BB_InstanceAudio *m_channelDst;
    BB_InstanceAudio *m_channelDummy;
    BB_InstanceAudio *m_channelDstTest;

	// Happening list for GUI
	std::vector<Happening> m_hapList;

	// Happening list with channel IDs for class internal usage
	std::vector<HappeningEx> m_hapListEx;

	// Sound Devices List
	std::vector<BB_SoundDevice> m_soundDevList;

    BB_CriticalSection m_cs;

    bool m_isConnected;
    bool m_isLoopbackStarted;
    bool m_isTargetLoopbackStarted;
};

#endif
