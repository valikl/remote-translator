#pragma once
#ifndef TIXML_USE_TICPP
    #define TIXML_USE_TICPP
#endif

#include "Ticpp/ticpp.h"

#include <string>
#include <vector>

const std::string NODE_BBCONFIG("BBconfig"); 
const std::string NODE_SERVER_CONNECT("ServerConnect");
const std::string ATTR_IP("ip");
const std::string ATTR_TCP("tcp");
const std::string ATTR_UDP("udp");
const std::string ATTR_SRV_PASSWORD("srvPassword");
const std::string ATTR_SRV_USER("srvUser");
const std::string ATTR_SRV_USER_PASSWORD("srvUserPassword");

const std::string NODE_TEMPLATES("Templates");
const std::string ATTR_HAP_PREFIX("hapPrefix");
const std::string ATTR_SRC_PREFIX("srcPrefix");
const std::string ATTR_DST_PREFIX("dstPrefix");
const std::string ATTR_VIDEO_PREFIX("videoPrefix");

const std::string NODE_AUDIO_SETTINGS("AudioSettings");
const std::string ATTR_DENOISE_LEVEL("denoiseLevel");
const std::string ATTR_ECHO_CANCEL("echoCancel");
const std::string ATTR_FRAMES_PER_SEC("framesPerSec");

const std::string NODE_AGC("AGC");
const std::string ATTR_ENABLE("enable");
const std::string ATTR_GAIN_LEVEL("gainLevel");
const std::string ATTR_MAX_INC("maxIncrement");
const std::string ATTR_MAX_DEC("maxDecrement");
const std::string ATTR_MAX_GAIN("maxGain");

// template for happening structure:
// hap_<happening name>/source_<source language channel>
// hap_<happening name>/destination_<destination language channel>
// hap_<happening name>/video_<video channel>
struct HapTemplate
{
	std::string m_hapRegexp;
	std::string m_srcRegexp;
	std::string m_dstRegexp;
	std::string m_videoRegexp;
};

struct HapData
{
    std::string m_Happening;
    std::vector<std::string> m_srcList;
    std::vector<std::string> m_trgList;
    std::string m_Video;
};

struct AGC
{
	bool m_enable;
	int  m_gainLevel;
	int  m_maxIncrement;
	int  m_maxDecrement;
	int  m_maxGain;
};

// Client configuration
struct ClientConfig
{
    std::string m_IP;
    int    m_TCP;
    int    m_UDP;
    std::string m_srvUser;
    std::string m_srvUserPsw;
    std::string m_srvPsw;

    // Regexp for happening
    HapTemplate m_hapTemplate;

    // Struct AGC
    AGC m_AGC;
    // Struct De-noise
    int m_noiseCancel;
    // Boolean echo cancelation function
    bool m_echoCancel;
    // Percentage of frames to show 100% - All frames shown, 0% - No frames shown
    int m_framesPerSec;

    //Structure fields for GUI intitialization
    std::string m_NickName;
    std::string m_Happening;
    std::string m_SrcChannel;
    std::string m_TrgChannel;
    int m_MicGainLevel;
    int m_SrcVolumeLevel;
    int m_trgVolumeLevel;
    int m_VideoQuality;

    bool m_MicMute;
    bool m_TrgMute;

    bool m_isSoundSystemWin;
    int m_InputSoundDevId;
    int m_OutputSoundDevId;
 };

// Client configuration manager
class BB_ClientConfigMgr
{
public:
	~BB_ClientConfigMgr(void);

	// Returns the instance of the singleton
	static BB_ClientConfigMgr &Instance();

	int init(std::string fileName = "config.xml");
	int saveConfig();
	
	ClientConfig getConfig();

private:

	BB_ClientConfigMgr();
	BB_ClientConfigMgr(const BB_ClientConfigMgr &);
	const BB_ClientConfigMgr &operator=(const BB_ClientConfigMgr &);

	int loadConfig();

	// read configuration from file
	void loadConfigFromFile(); 
	// read configuration from server
	int loadConfigFromServer(std::string serverName); 
	// return configuration
	int saveConfigToFile();

	void loadServerConnectConfig(const ticpp::Document &doc);
	void loadTemplateConfig(const ticpp::Document &doc);
	void loadAudioSettingsConfig(const ticpp::Document &doc);

	ClientConfig m_config;
	std::string m_fileName;
};

