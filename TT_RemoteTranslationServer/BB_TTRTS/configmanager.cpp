#include "configmanager.h"
#include "Utils/BB_Exception.h"
#include "Ticpp/tinyxml.h"

using namespace std;
using namespace ticpp;

ConfigManager::ConfigManager(void)
{
}

ConfigManager::~ConfigManager(void)
{
}

ConfigManager& ConfigManager::Instance()
{
    static ConfigManager instance;
    return instance;
}

void ConfigManager::init(bool bRestore)
{
    if (bRestore)
    {
        m_fileName = DEFAULT_CONFIG_FILE;
    }
    else
    {
        m_fileName = CONFIG_FILE;
    }

    try
    {
        loadConfig();
    }
    catch(ticpp::Exception& ex)
    {
        // XML error
        if (!bRestore)
        {
            m_fileName = DEFAULT_CONFIG_FILE;
            try
            {
                loadConfig();
            }
            catch(ticpp::Exception& ex)
            {
                THROW_EXCEPT(ex.what());
            }
        }
        else
        {
            THROW_EXCEPT(ex.what());
        }
    }
}

void ConfigManager::loadConfig()
{
    // Currently we support only configuration file
    loadConfigFromFile();
}

ClientConfig ConfigManager::getConfig()
{
    return m_config;
}

void ConfigManager::loadConfigFromFile()
{
    ticpp::Document doc(m_fileName.c_str());
    doc.LoadFile();

    loadServerConnectConfig(doc);
    loadTemplateConfig(doc);

}


void ConfigManager::loadServerConnectConfig(const ticpp::Document &doc)
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

void ConfigManager::loadTemplateConfig(const ticpp::Document &doc)
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




int ConfigManager::saveConfig()
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
