#pragma once
#ifndef TIXML_USE_TICPP
    #define TIXML_USE_TICPP
#endif

#include "Ticpp/ticpp.h"

#include <string>
#include <vector>

const std::string NODE_GROUPS("Groups");
const std::string NODE_SOURCES("Sources");
const std::string NODE_RECEIVERS("Receivers");
const std::string NODE_RESTRICTED_SERVERS("RestrictedServers");

const std::string ATTR_IP("ip");
const std::string ATTR_TCP("tcp");
const std::string ATTR_UDP("udp");
const std::string ATTR_SRV_PASSWORD("srvPassword");
const std::string ATTR_SRV_USER("srvUser");
const std::string ATTR_SRV_USER_PASSWORD("srvUserPassword");
const std::string ATTR_SOURCE_PATH("sourcePath");

const std::string NODE_SOURCE("Source");
const std::string NODE_RECEIVER("Receiver");
const std::string NODE_RESTRICTED_SERVER("RestrictedServer");

const std::string ATTR_NAME("name");
const std::string ATTR_NICK_NAME("nickName");
const std::string ATTR_CHANNEL_NAME("channelName");

const std::string NODE_AUDIO_SETTINGS("AudioSettings");
const std::string ATTR_DENOISE_LEVEL("denoiseLevel");
const std::string ATTR_ECHO_CANCEL("echoCancel");
const std::string ATTR_MIC_GAIN_LEVEL("micGainLevel");
const std::string ATTR_SRC_VOLUME_LEVEL("srcVolumeLevel");
const std::string ATTR_SOUND_SYS_WIN("soundSystemWin");
const std::string ATTR_INPUT_SOUND_DEV_ID("inputSoundDevId");
const std::string ATTR_OUTPUT_SOUND_DEV_ID("outputSoundDevId");

const std::string NODE_AGC("AGC");
const std::string ATTR_ENABLE("enable");
const std::string ATTR_GAIN_LEVEL("gainLevel");
const std::string ATTR_MAX_INC("maxIncrement");
const std::string ATTR_MAX_DEC("maxDecrement");
const std::string ATTR_MAX_GAIN("maxGain");

const std::string NODE_VOICE_ACTIVATION("VoiceActivation");
const std::string ATTR_VOICE_ACTIVATION_ENABLE("voiceActivationEnable");
const std::string ATTR_VOICE_ACTIVATION_LEVEL("voiceActivationLevel");

// Restore/Original config files
const std::string CONFIG_FILE("config_.xml");
const std::string DEFAULT_CONFIG_FILE("default_config_.xml");

enum GroupType
{
    GROUP_TYPE_NONE = 0,
    GROUP_TYPE_SOURCES = 1,
    GROUP_TYPE_RECEIVERS = 2,
    GROUP_TYPE_RESTRICTED_SERVERS =3
};

struct AGC
{
	bool m_enable;
	int  m_gainLevel;
	int  m_maxIncrement;
	int  m_maxDecrement;
	int  m_maxGain;
};

struct BB_GroupElementConfig
{
    std::wstring m_name;
    std::wstring m_nickName;
    std::wstring m_channelName;

    // Audio Settings
    int m_noiseCancel;
    bool m_echoCancel;
    int m_MicGainLevel;
    int m_SrcVolumeLevel;
    bool m_isSoundSystemWin;
    std::wstring m_InputSoundDevId;
    std::wstring m_OutputSoundDevId;

    // AGC
    AGC m_AGC;

    // Voice Activation
    bool m_EnableVoiceActivation;
    int m_VoiceActivationLevel;
};

struct ConnectionConfig
{
    std::wstring m_IP;
    int          m_TCP;
    int          m_UDP;
    std::wstring m_srvUser;
    std::wstring m_srvUserPsw;
    std::wstring m_srvPsw;
    std::wstring m_srcPath;
    std::wstring m_audioDir;
};

struct BB_GroupConfig
{
    ConnectionConfig m_ConnectionConfig;
    std::vector<BB_GroupElementConfig> m_groupList;
};


// Client configuration manager
class BB_ConfigMgr
{
public:
    ~BB_ConfigMgr(void);

	// Returns the instance of the singleton
    static BB_ConfigMgr &Instance();

    void init(bool bRestore);
	int saveConfig();
	
    ConnectionConfig GetConnectionConfig(GroupType groupType);
    BB_GroupElementConfig GetGroupElementConfig(GroupType groupType, const std::wstring name);

    void AddGroupElement(GroupType groupType, const std::wstring name, const std::wstring nickName, const std::wstring channel);
    void RemoveGroupElement(GroupType groupType, const std::wstring name);

    void SetIP(GroupType groupType, const std::wstring ip);
    void SetTCP(GroupType groupType, int tcp);
    void SetUDP(GroupType groupType, int udp);
    void SetSrvUser(GroupType groupType, const std::wstring srvUser);
    void SetSrvUserPsw(GroupType groupType, const std::wstring srvUserPsw);
    void SetSrvPsw(GroupType groupType, const std::wstring srvPsw);
    void SetPath(GroupType groupType, const std::wstring path);

    void SetGroupName(GroupType groupType, const std::wstring name);
    void SetGroupNickName(GroupType groupType, const std::wstring name, const std::wstring nickName);
    void SetGroupChannel(GroupType groupType, const std::wstring name, const std::wstring channel);
    void SetGroupAGC(GroupType groupType, const std::wstring name, AGC agc);
    void SetGroupEnableVoiceActivation(GroupType groupType, const std::wstring name, bool enable);
    void SetGroupVoiceActivationLevel(GroupType groupType, const std::wstring name, int level);

    void SetGroupNoiseCancel(GroupType groupType, const std::wstring name, int noiseCancel);
    void SetGroupEchoCancel(GroupType groupType, const std::wstring name, bool echoCancel);
    void SetGroupMicGainLevel(GroupType groupType, const std::wstring name, int micGainLevel);
    void SetGroupSrcVolumeLevel(GroupType groupType, const std::wstring name, int srcVolumeLevel);
    void SetGroupSoundSystemWin(GroupType groupType, const std::wstring name, bool isSoundSystemWin);
    void SetGroupInputSoundDevId(GroupType groupType, const std::wstring name, const std::wstring inputSoundDevId);
    void SetGroupOutputSoundDevId(GroupType groupType, const std::wstring name, const std::wstring outputSoundDevId);

private:

    BB_ConfigMgr();
    BB_ConfigMgr(const BB_ConfigMgr &);
    const BB_ConfigMgr &operator=(const BB_ConfigMgr &);

    void loadConfig();

	// read configuration from file
	void loadConfigFromFile(); 
	// read configuration from server
	int loadConfigFromServer(std::string serverName); 
	// return configuration
	int saveConfigToFile();

    void loadGroupsConfig(const ticpp::Document &doc, BB_GroupConfig &groupConfig, const std::string &nodeGroupsName, GroupType groupType);
    void loadGroupConfig(const ticpp::Node *node, BB_GroupElementConfig &groupConfig);
    void loadAudioSettingsConfig(const ticpp::Node *node, BB_GroupElementConfig &groupConfig);
    void loadAgcConfig(const ticpp::Node *node, BB_GroupElementConfig &groupConfig);
    void loadVoiceActivationConfig(const ticpp::Node *node, BB_GroupElementConfig &groupConfig);

    std::string buildGroupConfig(BB_GroupConfig &groupConfig, const std::string &nodeGroupsName, const std::string &nodeGroupName, GroupType groupType);

    BB_GroupConfig *GetGroupConfig(GroupType groupType);
    BB_GroupElementConfig *_GetGroupElementConfig(GroupType groupType, const std::wstring name);

    BB_GroupConfig m_sources;
    BB_GroupConfig m_receivers;
    BB_GroupConfig m_restrictedServers;

	std::string m_fileName;
};


