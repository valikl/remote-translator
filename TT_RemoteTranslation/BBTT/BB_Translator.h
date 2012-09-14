#ifndef _BB_TRANSLATOR_H_
#define _BB_TRANSLATOR_H_

#pragma once

#include <list>
#include <string>

#include "BB_Instance.h"

const std::wstring VIDEO_CHANNEL_NAME(L"Video");
const std::wstring SOURCE_CHANNEL_NAME(L"Source");
const std::wstring SOUND_CHECK_CHANNEL_NAME(L"Sound Check");

const std::wstring SRC_CHANNEL_PREFIX(L"SRC_");
const std::wstring DST_CHANNEL_PREFIX(L"DST_");
const std::wstring VIDEO_CHANNEL_PREFIX(L"VIDEO_");

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

enum TranslatorOpCode
{
    OP_CODE_UPDATE_MICROPHONE_GAIN,
    OP_CODE_UPDATE_SOURCE_LEVEL,
    OP_CODE_UPDATE_TARGET_LEVEL,
    OP_CODE_UPDATE_VIDEO_QUALITY,
    OP_CODE_MUTE_MICROPHONE,
    OP_CODE_MUTE_TARGET
};

class BB_Translator
{
public:
    BB_Translator();
	~BB_Translator(void);

	// connect to the server and get happenings
	int init();

    // disconnect etc.
    int finalize();

	std::vector<Happening> getHappenings() { return m_hapList; }
	//int setActiveHappening(std::string hapName);

	std::vector<BB_SoundDevice> getSoundDevices() { return m_soundDevList; }

    int connectHap(std::wstring hapName, std::wstring nickName, std::wstring srcName, std::wstring dstName,
                  std::wstring inputSoundDevId, std::wstring outputSoundDevId);
    int disconnectHap();
    int getUsers(std::vector<BB_ChannelUser> &userList, bool isSource);

    int handleOperation(TranslatorOpCode eOpCode);

    bool isConnected() {return m_isConnected; }

private:

	int initHapsList(const std::vector<BB_Channel> &channels);
	void initSoundDevicesList();

	bool findHap(HappeningEx &hap, std::wstring name);
	bool findSrcChannelId(const HappeningEx hap, std::wstring name, INT32 &channelId);
	bool findDstChannelId(const HappeningEx hap, std::wstring name, INT32 &channelId);
    bool findSoundDev(std::wstring deviceId, BB_SoundDevice &soundDevice);
	
	BB_Instance *m_channelVideo;
	BB_Instance *m_channelSrc;
	BB_Instance *m_channelDst;

	// Happening list for GUI
	std::vector<Happening> m_hapList;

	// Happening list with channel IDs for class internal usage
	std::vector<HappeningEx> m_hapListEx;

	// Sound Devices List
	std::vector<BB_SoundDevice> m_soundDevList;

    bool m_isConnected;
};

#endif
