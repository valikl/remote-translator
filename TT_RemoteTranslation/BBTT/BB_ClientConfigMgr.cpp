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

int BB_ClientConfigMgr::init(string fileName)
{
	m_fileName = fileName;
	return loadConfig();
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
                    
				if (strName == ATTR_IP)
				{
					m_config.m_IP = strValue;
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
					m_config.m_srvPsw = strValue;
					continue;
				}

				if (strName == ATTR_SRV_USER)
				{
					m_config.m_srvUser = strValue;
					continue;
				}

				if (strName == ATTR_SRV_USER_PASSWORD)
				{
					m_config.m_srvUserPsw = strValue;
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
                    
				if (strName == ATTR_HAP_PREFIX)
				{
					m_config.m_hapTemplate.m_hapRegexp = strValue;
					continue;
				}

				if (strName == ATTR_SRC_PREFIX)
				{
					m_config.m_hapTemplate.m_srcRegexp = strValue;
					continue;
				}

				if (strName == ATTR_DST_PREFIX)
				{
					m_config.m_hapTemplate.m_dstRegexp = strValue;
					continue;
				}

				if (strName == ATTR_VIDEO_PREFIX)
				{
					m_config.m_hapTemplate.m_videoRegexp = strValue;
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
		}

		ticpp::Iterator< ticpp::Node > node;
		for (node = node.begin(child.Get()); node != node.end(); node++)
		{
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
}


int BB_ClientConfigMgr::saveConfig()
{
	char buffer[100];

	string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
	xml += "<" + NODE_BBCONFIG + ">\n";
	
	xml += "<" + NODE_SERVER_CONNECT + " " +
		ATTR_IP + "=\"" + m_config.m_IP + "\" " + 
		ATTR_TCP + "=\"" + string(itoa(m_config.m_TCP, buffer, 10)) + "\" " +
		ATTR_UDP + "=\"" + string(itoa(m_config.m_UDP, buffer, 10)) + "\" " +
		ATTR_SRV_PASSWORD + "=\"" + m_config.m_srvPsw + "\" " +
		ATTR_SRV_USER + "=\"" + m_config.m_srvUser + "\" " +
		ATTR_SRV_USER_PASSWORD + "=\"" + m_config.m_srvUserPsw + "\" " + "/>\n";

	xml += "<" + NODE_TEMPLATES + " " +
		ATTR_HAP_PREFIX + "=\"" + m_config.m_hapTemplate.m_hapRegexp + "\" " + 
		ATTR_SRC_PREFIX + "=\"" + m_config.m_hapTemplate.m_srcRegexp + "\" " +
		ATTR_DST_PREFIX + "=\"" + m_config.m_hapTemplate.m_dstRegexp + "\" " +
		ATTR_VIDEO_PREFIX + "=\"" + m_config.m_hapTemplate.m_videoRegexp + "\" " + "/>\n";

	xml += "<" + NODE_AUDIO_SETTINGS + " " +
		ATTR_DENOISE_LEVEL + "=\"" + string(itoa(m_config.m_noiseCancel, buffer, 10)) + "\" " + 
		ATTR_ECHO_CANCEL + "=\"" + string(itoa(m_config.m_echoCancel, buffer, 10)) + "\" " +
		ATTR_FRAMES_PER_SEC + "=\"" + string(itoa(m_config.m_framesPerSec, buffer, 10)) + "\" " + ">\n";

	xml += "<" + NODE_AGC + " " +
		ATTR_ENABLE + "=\"" + string(itoa(m_config.m_AGC.m_enable, buffer, 10)) + "\" " + 
		ATTR_GAIN_LEVEL + "=\"" + string(itoa(m_config.m_AGC.m_gainLevel, buffer, 10)) + "\" " +
		ATTR_MAX_INC + "=\"" + string(itoa(m_config.m_AGC.m_maxIncrement, buffer, 10)) + "\" " +
		ATTR_MAX_DEC + "=\"" + string(itoa(m_config.m_AGC.m_maxDecrement, buffer, 10)) + "\" " +
		ATTR_MAX_GAIN + "=\"" + string(itoa(m_config.m_AGC.m_maxGain, buffer, 10)) + "\" " + "/>\n";

	xml += "</" + NODE_AUDIO_SETTINGS + ">\n";
	xml += "</" + NODE_BBCONFIG + ">\n";

	FILE *pFile = fopen(m_fileName.c_str(), "wb");
	if (pFile == NULL)
	{
		return EXIT_FAILURE;
	}
	fwrite(xml.c_str(), 1 , xml.size(), pFile);
	fclose(pFile);

	return EXIT_SUCCESS;
}
