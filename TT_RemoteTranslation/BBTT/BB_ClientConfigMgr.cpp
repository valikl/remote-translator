#include "BB_ClientConfigMgr.h"
#include "Ticpp/tinyxml.h"

using namespace std;
using namespace ticpp;

BB_ClientConfigMgr::BB_ClientConfigMgr(void)
{
}

BB_ClientConfigMgr::~BB_ClientConfigMgr(void)
{
}

BB_ClientConfigMgr& BB_ClientConfigMgr::Instance()
{
	static BB_ClientConfigMgr instance;
	return instance;
}

int BB_ClientConfigMgr::init(bool bRestore)
{
    if (bRestore)
    {
        m_fileName = DEFAULT_CONFIG_FILE;
    }
    else
    {
        m_fileName = CONFIG_FILE;
    }

    int err = loadConfig();
    if (err == EXIT_FAILURE && !bRestore)
    {
        m_fileName = DEFAULT_CONFIG_FILE;
        err = loadConfig();
    }

    return err;
}

int BB_ClientConfigMgr::loadConfig()
{
	try
	{
		// Currently we support only configuration file
		loadConfigFromFile();
	}
	catch(ticpp::Exception& ex)
	{
		// XML error
		std::cout << ex.what();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

ClientConfig BB_ClientConfigMgr::getConfig()
{
	return m_config;
}

void BB_ClientConfigMgr::loadConfigFromFile()
{
	ticpp::Document doc(m_fileName.c_str());
	doc.LoadFile();

	loadServerConnectConfig(doc);
	loadTemplateConfig(doc);
	loadAudioSettingsConfig(doc);
	loadVideoSettings(doc);
}

void BB_ClientConfigMgr::loadVideoSettings(const ticpp::Document &doc)
{
		// parse through all BBconfig Elements
    ticpp::Iterator<ticpp::Element> child;
    for(child = child.begin(doc.FirstChildElement()); child != child.end(); child++)
    {
		string strName;
        child->GetValue(&strName);
		if (strName == NODE_VIDEO_SETTINGS)
		{
			 // now parse through all the attributes of this element
            ticpp::Iterator< ticpp::Attribute > attribute;
            for(attribute = attribute.begin(child.Get()); attribute != attribute.end(); attribute++)
            {
				string strValue;
                attribute->GetName(&strName);
                attribute->GetValue(&strValue);

				if (strName == ATTR_VIDEO_QUALITY)
				{
					m_config.m_VideoQuality = atoi(strValue.c_str());
					continue;
				}
		    }
			break;
		}
	}
}

void BB_ClientConfigMgr::loadServerConnectConfig(const ticpp::Document &doc)
{
	// parse through all BBconfig Elements
    ticpp::Iterator<ticpp::Element> child;
    for(child = child.begin(doc.FirstChildElement()); child != child.end(); child++)
    {
		string strName;
        child->GetValue(&strName);
		if (strName == NODE_SERVER_CONNECT)
		{
			 // now parse through all the attributes of this element
            ticpp::Iterator< ticpp::Attribute > attribute;
            for(attribute = attribute.begin(child.Get()); attribute != attribute.end(); attribute++)
            {
				string strValue;
                attribute->GetName(&strName);
                attribute->GetValue(&strValue);
                   
				wstring wstrValue;
				wstrValue.assign(strValue.begin(), strValue.end());

				if (strName == ATTR_IP)
				{
					m_config.m_IP = wstrValue;
					continue;
				}

				if (strName == ATTR_TCP)
				{
					m_config.m_TCP = atoi(strValue.c_str());
					continue;
				}

				if (strName == ATTR_UDP)
				{
					m_config.m_UDP = atoi(strValue.c_str());
					continue;
				}

				if (strName == ATTR_SRV_PASSWORD)
				{
					m_config.m_srvPsw = wstrValue;
					continue;
				}

				if (strName == ATTR_SRV_USER)
				{
					m_config.m_srvUser = wstrValue;
					continue;
				}

				if (strName == ATTR_SRV_USER_PASSWORD)
				{
					m_config.m_srvUserPsw = wstrValue;
					continue;
				}

				if (strName == ATTR_NICK_NAME)
				{
					m_config.m_NickName = wstrValue;
					continue;
				}

				if (strName == ATTR_HAP_NAME)
				{
					m_config.m_Happening = wstrValue;
					continue;
				}

				if (strName == ATTR_SRC_NAME)
				{
					m_config.m_SrcChannel = wstrValue;
					continue;
				}

				if (strName == ATTR_TRG_NAME)
				{
					m_config.m_TrgChannel = wstrValue;
					continue;
				}
		    }
			break;
		}
	}
}

void BB_ClientConfigMgr::loadTemplateConfig(const ticpp::Document &doc)
{
	// parse through all BBconfig Elements
    ticpp::Iterator<ticpp::Element> child;
    for(child = child.begin(doc.FirstChildElement()); child != child.end(); child++)
    {
		string strName;
        child->GetValue(&strName);
		if (strName == NODE_TEMPLATES)
		{
			 // now parse through all the attributes of this element
            ticpp::Iterator< ticpp::Attribute > attribute;
            for(attribute = attribute.begin(child.Get()); attribute != attribute.end(); attribute++)
            {
				string strValue;
                attribute->GetName(&strName);
                attribute->GetValue(&strValue);
                    
				wstring wstrValue;
				wstrValue.assign(strValue.begin(), strValue.end());

				if (strName == ATTR_HAP_PREFIX)
				{
					m_config.m_hapTemplate.m_hapRegexp = wstrValue;
					continue;
				}

				if (strName == ATTR_SRC_PREFIX)
				{
					m_config.m_hapTemplate.m_srcRegexp = wstrValue;
					continue;
				}

				if (strName == ATTR_DST_PREFIX)
				{
					m_config.m_hapTemplate.m_dstRegexp = wstrValue;
					continue;
				}

				if (strName == ATTR_VIDEO_PREFIX)
				{
					m_config.m_hapTemplate.m_videoRegexp = wstrValue;
					continue;
				}
		    }
			break;
		}
	}
}

void BB_ClientConfigMgr::loadAudioSettingsConfig(const ticpp::Document &doc)
{
	// parse through all BBconfig Elements
    ticpp::Iterator<ticpp::Element> child;
    for(child = child.begin(doc.FirstChildElement()); child != child.end(); child++)
    {
		string strName;
        child->GetValue(&strName);
		if (strName != NODE_AUDIO_SETTINGS)
		{
			continue;
		}

			// now parse through all the attributes of this element
        ticpp::Iterator< ticpp::Attribute > attribute;
        for(attribute = attribute.begin(child.Get()); attribute != attribute.end(); attribute++)
        {
			string strValue;
            attribute->GetName(&strName);
            attribute->GetValue(&strValue);
                    
			if (strName == ATTR_DENOISE_LEVEL)
			{
				m_config.m_noiseCancel = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_ECHO_CANCEL)
			{
				m_config.m_echoCancel = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_FRAMES_PER_SEC)
			{
				m_config.m_framesPerSec = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_MIC_GAIN_LEVEL)
			{
				m_config.m_MicGainLevel = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_SRC_VOLUME_LEVEL)
			{
				m_config.m_SrcVolumeLevel = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_TRG_VOLUME_LEVEL)
			{
                m_config.m_TrgVolumeLevel = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_MIC_MUTE)
			{
				m_config.m_MicMute = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_TRG_MUTE)
			{
				m_config.m_TrgMute = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_SOUND_SYS_WIN)
			{
				m_config.m_isSoundSystemWin = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_INPUT_SOUND_DEV_ID)
			{
                wstring wstrValue;
                wstrValue.assign(strValue.begin(), strValue.end());
                m_config.m_InputSoundDevId = wstrValue;
				continue;
			}

			if (strName == ATTR_OUTPUT_SOUND_DEV_ID)
			{
                wstring wstrValue;
                wstrValue.assign(strValue.begin(), strValue.end());
                m_config.m_OutputSoundDevId = wstrValue;
				continue;
			}
		}

        loadAgcConfig(child);
        loadVoiceActivationConfig(child);
	}
}

void BB_ClientConfigMgr::loadAgcConfig(const ticpp::Iterator<ticpp::Element> &element)
{
    ticpp::Iterator< ticpp::Node > node;
    for (node = node.begin(element.Get()); node != node.end(); node++)
    {
        string strName;
        node->GetValue(&strName);
        if (strName != NODE_AGC)
        {
            continue;
        }

        // now parse through all the attributes of this element
        ticpp::Iterator< ticpp::Attribute > attribute;
        for(attribute = attribute.begin(node.Get()); attribute != attribute.end(); attribute++)
        {
            string strValue;
            attribute->GetName(&strName);
            attribute->GetValue(&strValue);

            if (strName == ATTR_ENABLE)
            {
                m_config.m_AGC.m_enable = atoi(strValue.c_str());
                continue;
            }

            if (strName == ATTR_GAIN_LEVEL)
            {
                m_config.m_AGC.m_gainLevel = atoi(strValue.c_str());
                continue;
            }

            if (strName == ATTR_MAX_INC)
            {
                m_config.m_AGC.m_maxIncrement = atoi(strValue.c_str());
                continue;
            }

            if (strName == ATTR_MAX_DEC)
            {
                m_config.m_AGC.m_maxDecrement = atoi(strValue.c_str());
                continue;
            }

            if (strName == ATTR_MAX_GAIN)
            {
                m_config.m_AGC.m_maxGain = atoi(strValue.c_str());
                continue;
            }
        }
    }
}


void BB_ClientConfigMgr::loadVoiceActivationConfig(const ticpp::Iterator<ticpp::Element> &element)
{
    ticpp::Iterator< ticpp::Node > node;
    for (node = node.begin(element.Get()); node != node.end(); node++)
    {
        string strName;
        node->GetValue(&strName);
        if (strName != NODE_VOICE_ACTIVATION)
        {
            continue;
        }

        // now parse through all the attributes of this element
        ticpp::Iterator< ticpp::Attribute > attribute;
        for(attribute = attribute.begin(node.Get()); attribute != attribute.end(); attribute++)
        {
            string strValue;
            attribute->GetName(&strName);
            attribute->GetValue(&strValue);

            if (strName == ATTR_VOICE_ACTIVATION_ENABLE)
            {
                m_config.m_EnableVoiceActivation = atoi(strValue.c_str());
                continue;
            }

            if (strName == ATTR_VOICE_ACTIVATION_LEVEL)
            {
                m_config.m_VoiceActivationLevel = atoi(strValue.c_str());
                continue;
            }
        }
    }
}


int BB_ClientConfigMgr::saveConfig()
{
	char buffer[100];

	string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
	xml += "<" + NODE_BBCONFIG + ">\n";
	

	xml += "<" + NODE_SERVER_CONNECT + " " +
		ATTR_IP + "=\"" + string(m_config.m_IP.begin(), m_config.m_IP.end()) + "\" " + 
		ATTR_TCP + "=\"" + string(itoa(m_config.m_TCP, buffer, 10)) + "\" " +
		ATTR_UDP + "=\"" + string(itoa(m_config.m_UDP, buffer, 10)) + "\" " +
		ATTR_SRV_PASSWORD + "=\"" + string(m_config.m_srvPsw.begin(), m_config.m_srvPsw.end()) + "\" " +
		ATTR_SRV_USER + "=\"" + string(m_config.m_srvUser.begin(), m_config.m_srvUser.end()) + "\" " +
		ATTR_SRV_USER_PASSWORD + "=\"" + string(m_config.m_srvUserPsw.begin(), m_config.m_srvUserPsw.end()) + "\" " + 
		ATTR_NICK_NAME + "=\"" + string(m_config.m_NickName.begin(), m_config.m_NickName.end()) + "\" " + 
		ATTR_HAP_NAME + "=\"" + string(m_config.m_Happening.begin(), m_config.m_Happening.end()) + "\" " + 
		ATTR_SRC_NAME + "=\"" + string(m_config.m_SrcChannel.begin(), m_config.m_SrcChannel.end()) + "\" " + 
		ATTR_TRG_NAME + "=\"" + string(m_config.m_TrgChannel.begin(), m_config.m_TrgChannel.end()) + "\" " + "/>\n";

	xml += "<" + NODE_TEMPLATES + " " +
		ATTR_HAP_PREFIX + "=\"" + string(m_config.m_hapTemplate.m_hapRegexp.begin(), m_config.m_hapTemplate.m_hapRegexp.end()) + "\" " + 
		ATTR_SRC_PREFIX + "=\"" + string(m_config.m_hapTemplate.m_srcRegexp.begin(), m_config.m_hapTemplate.m_srcRegexp.end()) + "\" " +
		ATTR_DST_PREFIX + "=\"" + string(m_config.m_hapTemplate.m_dstRegexp.begin(), m_config.m_hapTemplate.m_dstRegexp.end()) + "\" " +
		ATTR_VIDEO_PREFIX + "=\"" + string(m_config.m_hapTemplate.m_videoRegexp.begin(), m_config.m_hapTemplate.m_videoRegexp.end()) + "\" " + "/>\n";

	xml += "<" + NODE_AUDIO_SETTINGS + " " +
		ATTR_DENOISE_LEVEL + "=\"" + string(itoa(m_config.m_noiseCancel, buffer, 10)) + "\" " + 
		ATTR_ECHO_CANCEL + "=\"" + string(itoa(m_config.m_echoCancel, buffer, 10)) + "\" " +
		ATTR_FRAMES_PER_SEC + "=\"" + string(itoa(m_config.m_framesPerSec, buffer, 10)) + "\" " + 
		ATTR_MIC_GAIN_LEVEL + "=\"" + string(itoa(m_config.m_MicGainLevel, buffer, 10)) + "\" " + 
		ATTR_SRC_VOLUME_LEVEL + "=\"" + string(itoa(m_config.m_SrcVolumeLevel, buffer, 10)) + "\" " + 
        ATTR_TRG_VOLUME_LEVEL + "=\"" + string(itoa(m_config.m_TrgVolumeLevel, buffer, 10)) + "\" " +
		ATTR_MIC_MUTE + "=\"" + string(itoa(m_config.m_MicMute, buffer, 10)) + "\" " + 
		ATTR_TRG_MUTE + "=\"" + string(itoa(m_config.m_TrgMute, buffer, 10)) + "\" " + 
		ATTR_SOUND_SYS_WIN + "=\"" + string(itoa(m_config.m_isSoundSystemWin, buffer, 10)) + "\" " + 
        ATTR_INPUT_SOUND_DEV_ID + "=\"" + string(m_config.m_InputSoundDevId.begin(), m_config.m_InputSoundDevId.end()) + "\" " +
        ATTR_OUTPUT_SOUND_DEV_ID + "=\"" + string(m_config.m_OutputSoundDevId.begin(), m_config.m_OutputSoundDevId.end()) + "\" " + ">\n";

	xml += "<" + NODE_AGC + " " +
		ATTR_ENABLE + "=\"" + string(itoa(m_config.m_AGC.m_enable, buffer, 10)) + "\" " + 
		ATTR_GAIN_LEVEL + "=\"" + string(itoa(m_config.m_AGC.m_gainLevel, buffer, 10)) + "\" " +
		ATTR_MAX_INC + "=\"" + string(itoa(m_config.m_AGC.m_maxIncrement, buffer, 10)) + "\" " +
		ATTR_MAX_DEC + "=\"" + string(itoa(m_config.m_AGC.m_maxDecrement, buffer, 10)) + "\" " +
		ATTR_MAX_GAIN + "=\"" + string(itoa(m_config.m_AGC.m_maxGain, buffer, 10)) + "\" " + "/>\n";

    xml += "<" + NODE_VOICE_ACTIVATION + " " +
        ATTR_VOICE_ACTIVATION_ENABLE + "=\"" + string(itoa(m_config.m_EnableVoiceActivation, buffer, 10)) + "\" " +
        ATTR_VOICE_ACTIVATION_LEVEL + "=\"" + string(itoa(m_config.m_VoiceActivationLevel, buffer, 10)) + "\" " + "/>\n";

	xml += "</" + NODE_AUDIO_SETTINGS + ">\n";

	xml += "<" + NODE_VIDEO_SETTINGS + " " +
		ATTR_VIDEO_QUALITY + "=\"" + string(itoa(m_config.m_VideoQuality, buffer, 10)) + "\" " + "/>\n";

	xml += "</" + NODE_BBCONFIG + ">\n";

    FILE *pFile = fopen(CONFIG_FILE.c_str(), "wb");
	if (pFile == NULL)
	{
		return EXIT_FAILURE;
	}
	fwrite(xml.c_str(), 1 , xml.size(), pFile);
	fclose(pFile);

	return EXIT_SUCCESS;
}
