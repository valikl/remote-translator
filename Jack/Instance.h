#pragma once

#ifdef WIN32
#include <windows.h>
#endif
#include "TeamTalk4.h"
#include <string>
#include <iostream>

struct BB_InstanceContext
{
	std::string m_IP;
	int m_TCP;
	int m_UDP;
    std::string m_srvPsw;
    std::string m_srvUser;
    std::string m_srvUserPsw;
    std::string m_nickName;
    std::string m_channelPath;
    std::string m_channelPsw;
    std::string m_ProcessName;
};


class BB_Instance
{
public:
    BB_Instance(const BB_InstanceContext &context, bool isInput);
    ~BB_Instance(void);

	// We don't want to call TT functions in Ctor & Dtor
	// Use init and finalize instead
    bool init();
    void finalize();
	bool connect();

    bool setClassroom();
    bool enableTransmission();
    bool startSoundLoopbackTest();
    bool stopSoundLoopbackTest();

    bool isInstExist();
    bool isUserExist();
    bool loop();

private:
		
    bool login();
    bool joinChannel();
    bool initSoundDevice();

    void printLog(std::string msg);

	bool processTTMessage(const TTMessage& msg, bool &killInst);

	TTInstance* m_ttInst;

    BB_InstanceContext m_context;

	INT32 m_channelId;
    INT32 m_userID;

    bool m_isInput;
};


