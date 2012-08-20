#ifndef _BB_TRANSLATOR_H_
#define _BB_TRANSLATOR_H_

#pragma once

#include <list>
#include <string>

#include "BB_Instance.h"

const std::string VIDEO_CHANNEL_NAME("Video");
const std::wstring SOURCE_CHANNEL_NAME(L"Source");
const std::wstring SOUND_CHECK_CHANNEL_NAME(L"Sound Check");

struct Happening
{
	//string m_hapName;
	std::vector<std::string> m_srcChannels;
	std::vector<std::string> m_dstChannels;
	std::string m_videoChannel;
};

struct BB_TranslatorContext
{
	std::wstring m_IP;
	int m_TCP;
	int m_UDP;
	std::wstring m_srvPsw;
	std::wstring m_srvUser;
	std::wstring m_srvUserPsw;
	std::wstring m_nickName;
	std::wstring m_audioDir;
};

class BB_Translator
{
public:
	BB_Translator(const BB_TranslatorContext &context);
	~BB_Translator(void);

	// connect to the server and get happenings
	int init();

	std::vector<Happening> getHappenings() { return m_hapList; }
	//int setActiveHappening(std::string hapName);

private:
	BB_Instance *m_channelVideo;
	BB_Instance *m_channelSrc;
	BB_Instance *m_channelDst;

	std::vector<Happening> m_hapList;

	BB_TranslatorContext m_context;
};

#endif
