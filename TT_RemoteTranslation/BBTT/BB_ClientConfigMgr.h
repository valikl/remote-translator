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
const std::string ATTR_NICK_NAME("nickName");
const std::string ATTR_HAP_NAME("hapName");
const std::string ATTR_SRC_NAME("srcName");
const std::string ATTR_TRG_NAME("trgName");

const std::string NODE_TEMPLATES("Templates");
const std::string ATTR_HAP_PREFIX("hapPrefix");
const std::string ATTR_SRC_PREFIX("srcPrefix");
const std::string ATTR_DST_PREFIX("dstPrefix");
const std::string ATTR_VIDEO_PREFIX("videoPrefix");

const std::string NODE_AUDIO_SETTINGS("AudioSettings");
const std::string ATTR_DENOISE_LEVEL("denoiseLevel");
const std::string ATTR_ECHO_CANCEL("echoCancel");
const std::string ATTR_FRAMES_PER_SEC("framesPerSec");
const std::string ATTR_MIC_GAIN_LEVEL("micGainLevel");
const std::string ATTR_SRC_VOLUME_LEVEL("srcVolumeLevel");
const std::string ATTR_TRG_VOLUME_LEVEL("trgVolumeLevel");
const std::string ATTR_MIC_MUTE("micMute");
const std::string ATTR_TRG_MUTE("trgMute");
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

const std::string NODE_VIDEO_SETTINGS("VideoSettings");
const std::string ATTR_VIDEO_QUALITY("videoQuality");

// template for happening structure:
// hap_<happening name>/source_<source language channel>
// hap_<happening name>/destination_<destination language channel>
// hap_<happening name>/video_<video channel>
struct HapTemplate
{
    std::wstring m_hapRegexp;
    std::wstring m_srcRegexp;
    std::wstring m_dstRegexp;
    std::wstring m_videoRegexp;
};

struct HapData
{
    std::wstring m_Happening;
    std::vector<std::wstring> m_srcList;
    std::vector<std::wstring> m_trgList;
    std::wstring m_Video;
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
    std::wstring m_IP;
    int    m_TCP;
    int    m_UDP;
    std::wstring m_srvUser;
    std::wstring m_srvUserPsw;
    std::wstring m_srvPsw;

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

    // Voice Activation
    bool m_EnableVoiceActivation;
    int m_VoiceActivationLevel;

    //Structure fields for GUI intitialization
    std::wstring m_NickName;
    std::wstring m_Happening;
    std::wstring m_SrcChannel;
    std::wstring m_TrgChannel;
    int m_MicGainLevel;
    int m_SrcVolumeLevel;
    int m_TrgVolumeLevel;
    int m_VideoQuality;

    bool m_MicMute;
    bool m_TrgMute;

    bool m_isSoundSystemWin;
    std::wstring m_InputSoundDevId;
    std::wstring m_OutputSoundDevId;
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

    void SetIP(std::wstring ip) {m_config.m_IP = ip;}
    void SetTCP(int tcp) {m_config.m_TCP = tcp;}
    void SetUDP(int udp) {m_config.m_UDP = udp;}
    void SetSrvUser(std::wstring srvUser) {m_config.m_srvUser = srvUser;}
    void SetSrvUserPsw(std::wstring srvUserPsw) {m_config.m_srvUserPsw = srvUserPsw;}
    void SetSrvPsw(std::wstring srvPsw) {m_config.m_srvPsw = srvPsw;}
    void SetHapTemplate(HapTemplate hapTemplate) {m_config.m_hapTemplate.m_dstRegexp = hapTemplate.m_dstRegexp;
        m_config.m_hapTemplate.m_srcRegexp = hapTemplate.m_srcRegexp; m_config.m_hapTemplate.m_dstRegexp = hapTemplate.m_dstRegexp;
        m_config.m_hapTemplate.m_videoRegexp = hapTemplate.m_videoRegexp;}
    void SetAGC(AGC agc) {m_config.m_AGC.m_enable = agc.m_enable; m_config.m_AGC.m_gainLevel = agc.m_gainLevel;
        m_config.m_AGC.m_maxIncrement = agc.m_maxIncrement; m_config.m_AGC.m_maxDecrement = agc.m_maxDecrement;
        m_config.m_AGC.m_maxGain = agc.m_maxGain;}
    void SetEnableVoiceActivation(bool enable) { m_config.m_EnableVoiceActivation = enable; }
    void SetVoiceActivationLevel(bool level) { m_config.m_VoiceActivationLevel = level; }
    void SetNoiseCancel(int noiseCancel) {m_config.m_noiseCancel = noiseCancel;}
    void SetEchoCancel(bool echoCancel) {m_config.m_echoCancel = echoCancel;}
    void SetFramesPerSec(int framesPerSec) {m_config.m_framesPerSec = framesPerSec;}
    void SetNickName(std::wstring nickName) {m_config.m_NickName = nickName;}
    void SetHappening(std::wstring happening) {m_config.m_Happening = happening;}
    void SetSrcChannel(std::wstring srcChannel) {m_config.m_SrcChannel = srcChannel;}
    void SetTrgChannel(std::wstring trgChannel) {m_config.m_TrgChannel = trgChannel;}
    void SetMicGainLevel(int micGainLevel) {m_config.m_MicGainLevel = micGainLevel;}
    void SetSrcVolumeLevel(int srcVolumeLevel) {m_config.m_SrcVolumeLevel = srcVolumeLevel;}
    void SetTrgVolumeLevel(int trgVolumeLevel) {m_config.m_TrgVolumeLevel = trgVolumeLevel;}
    void SetVideoQuality(int videoQuality) {m_config.m_VideoQuality = videoQuality;}
    void SetMicMute(bool micMute) {m_config.m_MicMute = micMute;}
    void SetTrgMute(bool trgMute) {m_config.m_TrgMute = trgMute;}
    void SetSoundSystemWin(bool isSoundSystemWin) {m_config.m_isSoundSystemWin = isSoundSystemWin;}
    void SetInputSoundDevId(std::wstring inputSoundDevId) {m_config.m_InputSoundDevId = inputSoundDevId;}
    void SetOutputSoundDevId(std::wstring outputSoundDevId) {m_config.m_OutputSoundDevId = outputSoundDevId;}

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
    void loadAgcConfig(const ticpp::Iterator<ticpp::Element> &element);
    void loadVoiceActivationConfig(const ticpp::Iterator<ticpp::Element> &element);
    void loadVideoSettings(const ticpp::Document &doc);

	ClientConfig m_config;
	std::string m_fileName;
};

