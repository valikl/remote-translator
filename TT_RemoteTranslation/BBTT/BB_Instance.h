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

enum DeviceType
{
	BB_IN_SOUND_DEVICE,
	BB_OUT_SOUND_DEVICE
};

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

	std::wstring m_channelName;
};

const INT32 ROOT_PARENT_ID(1);

struct BB_Channel
{
	std::wstring name;
	INT32 id;
	INT32 parentId;
};

class BB_Instance
{
public:
	BB_Instance(const BB_InstanceContext &context);
	~BB_Instance(void);

	// We don't want to call TT functions in Ctor & Dtor
	// Use init and finalize instead
	int init();
	void finalize();

	int getChannelId();
	int initDevice();
	int SetAudioLevels();
	int EnableTransmition();
	int getVideoDevice();
	
	int getChannels(std::vector<BB_Channel> &channels);

private:
		
	int joinChannel();
	int getInstance();
	int setInstProp();

	void processTTMessage(const TTMessage& msg);

	TTInstance* m_ttInst;

	BB_InstanceContext m_context;

	INT32 m_channelId;
};

#endif

