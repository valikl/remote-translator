#pragma once

#ifdef WIN32
#include <windows.h>
#endif
#include <../TeamTalk/TeamTalk4.h>
#include <vector>
#include "BB_ClientConfigMgr.h"


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
    bool m_PacketsLost;
};

class BB_Instance
{
public:
    BB_Instance(const BB_InstanceContext &context);
    ~BB_Instance(void);

	// We don't want to call TT functions in Ctor & Dtor
	// Use init and finalize instead
    virtual void init();
    virtual void finalize();

    // Connect & login
    void login();

    // Return context
    void getInstanceContext(BB_InstanceContext &context) { context = m_context; }

    // Return users list
    virtual void getUsers(std::vector<BB_ChannelUser> &userList);

    // Return channels list
    void getChannels(std::vector<BB_Channel> &channels);

    // Return sound devices list
    void getSoundDevices(std::vector<BB_SoundDevice> &soundDevs);

protected:
		
    void joinChannel();
    void setInstProp();

	void processTTMessage(const TTMessage& msg);

	TTInstance* m_ttInst;

    BB_InstanceContext m_context;

	INT32 m_channelId;

    std::vector<BB_ChannelUser> m_UserList;
};


