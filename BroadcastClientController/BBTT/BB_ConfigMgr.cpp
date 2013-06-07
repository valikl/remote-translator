#include "BB_ConfigMgr.h"
#include "Ticpp/tinyxml.h"
#include "Utils/Lock.h"
#include "Utils/BB_Exception.h"

using namespace std;
using namespace ticpp;

BB_ConfigMgr::BB_ConfigMgr(void)
{
}

BB_ConfigMgr::~BB_ConfigMgr(void)
{
}

BB_ConfigMgr& BB_ConfigMgr::Instance()
{
    static BB_ConfigMgr instance;
	return instance;
}

void BB_ConfigMgr::init(bool bRestore)
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

void BB_ConfigMgr::loadConfig()
{
    loadConfigFromFile();
}

void BB_ConfigMgr::loadConfigFromFile()
{
	ticpp::Document doc(m_fileName.c_str());
	doc.LoadFile();

    loadGroupsConfig(doc, m_sources, NODE_SOURCES, GROUP_TYPE_SOURCES);
    loadGroupsConfig(doc, m_receivers, NODE_RECEIVERS, GROUP_TYPE_RECEIVERS);
    loadGroupsConfig(doc, m_restrictedServers, NODE_RESTRICTED_SERVERS, GROUP_TYPE_RESTRICTED_SERVERS);
}

void BB_ConfigMgr::loadGroupsConfig(const ticpp::Document &doc, BB_GroupConfig &groupConfig, const std::string &nodeGroupsName, GroupType groupType)
{
    // Parse through all Groups Elements
    ticpp::Iterator<ticpp::Element> child;
    for(child = child.begin(doc.FirstChildElement()); child != child.end(); child++)
    {
		string strName;
        child->GetValue(&strName);
        if (strName == nodeGroupsName)
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
                    groupConfig.m_ConnectionConfig.m_IP = wstrValue;
					continue;
				}

				if (strName == ATTR_TCP)
				{
                    groupConfig.m_ConnectionConfig.m_TCP = atoi(strValue.c_str());
					continue;
				}

				if (strName == ATTR_UDP)
				{
                    groupConfig.m_ConnectionConfig.m_UDP = atoi(strValue.c_str());
					continue;
				}

				if (strName == ATTR_SRV_PASSWORD)
				{
                    groupConfig.m_ConnectionConfig.m_srvPsw = wstrValue;
					continue;
				}

				if (strName == ATTR_SRV_USER)
				{
                    groupConfig.m_ConnectionConfig.m_srvUser = wstrValue;
					continue;
				}

				if (strName == ATTR_SRV_USER_PASSWORD)
				{
                    groupConfig.m_ConnectionConfig.m_srvUserPsw = wstrValue;
					continue;
				}

                if (strName == ATTR_SOURCE_PATH)
				{
                    groupConfig.m_ConnectionConfig.m_srcPath = wstrValue;
					continue;
				}
		    }

            // Parse through all Group Elements
            ticpp::Iterator< ticpp::Node > node;
            for (node = node.begin(child.Get()); node != node.end(); node++)
            {
                string strName;
                node->GetValue(&strName);
                if ((nodeGroupsName == NODE_SOURCES && strName == NODE_SOURCE) ||
                    (nodeGroupsName == NODE_RECEIVERS && strName == NODE_RECEIVER) ||
                    (nodeGroupsName == NODE_RESTRICTED_SERVERS && strName == NODE_RESTRICTED_SERVER))
                {
                    BB_GroupElementConfig groupElement;
                    loadGroupConfig(node.Get(), groupElement);
                    groupConfig.m_groupList.insert(pair<wstring, BB_GroupElementConfig>(groupElement.m_name, groupElement));
                }
            }
		}
	}
}

void BB_ConfigMgr::loadGroupConfig(const ticpp::Node *node, BB_GroupElementConfig &groupElement)
{
    // now parse through all the attributes of this element
    ticpp::Iterator< ticpp::Attribute > attribute;
    for(attribute = attribute.begin(node); attribute != attribute.end(); attribute++)
    {
        string strName;
        string strValue;
        attribute->GetName(&strName);
        attribute->GetValue(&strValue);

        wstring wstrValue;
        wstrValue.assign(strValue.begin(), strValue.end());

        if (strName == ATTR_NAME)
        {
            groupElement.m_name = wstrValue;
            continue;
        }

        if (strName == ATTR_NICK_NAME)
        {
            groupElement.m_nickName = wstrValue;
            continue;
        }

        if (strName == ATTR_CHANNEL_NAME)
        {
            groupElement.m_channelName = wstrValue;
            continue;
        }
    }

    loadAudioSettingsConfig(node, groupElement);
}

void BB_ConfigMgr::loadAudioSettingsConfig(const ticpp::Node *node, BB_GroupElementConfig &groupElement)
{
    ticpp::Iterator< ticpp::Node > child;
    for (child = child.begin(node); child != child.end(); child++)
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
                groupElement.m_noiseCancel = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_ECHO_CANCEL)
			{
                groupElement.m_echoCancel = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_MIC_GAIN_LEVEL)
			{
                groupElement.m_MicGainLevel = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_SRC_VOLUME_LEVEL)
			{
                groupElement.m_SrcVolumeLevel = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_SOUND_SYS_WIN)
			{
                groupElement.m_isSoundSystemWin = atoi(strValue.c_str());
				continue;
			}

			if (strName == ATTR_INPUT_SOUND_DEV_ID)
			{
                wstring wstrValue;
                wstrValue.assign(strValue.begin(), strValue.end());
                groupElement.m_InputSoundDevId = wstrValue;
				continue;
			}

			if (strName == ATTR_OUTPUT_SOUND_DEV_ID)
			{
                wstring wstrValue;
                wstrValue.assign(strValue.begin(), strValue.end());
                groupElement.m_OutputSoundDevId = wstrValue;
				continue;
			}
		}

        loadAgcConfig(child.Get(), groupElement);
        loadVoiceActivationConfig(child.Get(), groupElement);
	}
}

void BB_ConfigMgr::loadAgcConfig(const ticpp::Node *node, BB_GroupElementConfig &groupElement)
{
    ticpp::Iterator< ticpp::Node > child;
    for (child = child.begin(node); child != child.end(); child++)
    {
        string strName;
        child->GetValue(&strName);
        if (strName != NODE_AGC)
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

            if (strName == ATTR_ENABLE)
            {
                groupElement.m_AGC.m_enable = atoi(strValue.c_str());
                continue;
            }

            if (strName == ATTR_GAIN_LEVEL)
            {
                groupElement.m_AGC.m_gainLevel = atoi(strValue.c_str());
                continue;
            }

            if (strName == ATTR_MAX_INC)
            {
                groupElement.m_AGC.m_maxIncrement = atoi(strValue.c_str());
                continue;
            }

            if (strName == ATTR_MAX_DEC)
            {
                groupElement.m_AGC.m_maxDecrement = atoi(strValue.c_str());
                continue;
            }

            if (strName == ATTR_MAX_GAIN)
            {
                groupElement.m_AGC.m_maxGain = atoi(strValue.c_str());
                continue;
            }
        }
    }
}


void BB_ConfigMgr::loadVoiceActivationConfig(const ticpp::Node *node, BB_GroupElementConfig &groupElement)
{
    ticpp::Iterator< ticpp::Node > child;
    for (child = child.begin(node); child != child.end(); child++)
    {
        string strName;
        child->GetValue(&strName);
        if (strName != NODE_VOICE_ACTIVATION)
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

            if (strName == ATTR_VOICE_ACTIVATION_ENABLE)
            {
                groupElement.m_EnableVoiceActivation = atoi(strValue.c_str());
                continue;
            }

            if (strName == ATTR_VOICE_ACTIVATION_LEVEL)
            {
                groupElement.m_VoiceActivationLevel = atoi(strValue.c_str());
                continue;
            }
        }
    }
}

string BB_ConfigMgr::buildGroupConfig(BB_GroupConfig &groupConfig, const string &nodeGroupsName, const string &nodeGroupName, GroupType groupType)
{
    string xml = "";
    char buffer[100];

    xml += "<" + nodeGroupsName + " " +
        ATTR_IP + "=\"" + string(groupConfig.m_ConnectionConfig.m_IP.begin(), groupConfig.m_ConnectionConfig.m_IP.end()) + "\" " +
        ATTR_TCP + "=\"" + string(itoa(groupConfig.m_ConnectionConfig.m_TCP, buffer, 10)) + "\" " +
        ATTR_UDP + "=\"" + string(itoa(groupConfig.m_ConnectionConfig.m_UDP, buffer, 10)) + "\" " +
        ATTR_SRV_PASSWORD + "=\"" + string(groupConfig.m_ConnectionConfig.m_srvPsw.begin(), groupConfig.m_ConnectionConfig.m_srvPsw.end()) + "\" " +
        ATTR_SRV_USER + "=\"" + string(groupConfig.m_ConnectionConfig.m_srvUser.begin(), groupConfig.m_ConnectionConfig.m_srvUser.end()) + "\" " +
        ATTR_SRV_USER_PASSWORD + "=\"" + string(groupConfig.m_ConnectionConfig.m_srvUserPsw.begin(), groupConfig.m_ConnectionConfig.m_srvUserPsw.end()) + "\" " +
        ATTR_SOURCE_PATH + "=\"" + string(groupConfig.m_ConnectionConfig.m_srcPath.begin(), groupConfig.m_ConnectionConfig.m_srcPath.end()) + "\" " + ">\n";

    std::map<wstring, BB_GroupElementConfig>::iterator it;
    for (it = groupConfig.m_groupList.begin(); it != groupConfig.m_groupList.end(); ++it)
    for (unsigned int i=0; i < groupConfig.m_groupList.size(); i++)
    {
        xml += "<" + nodeGroupName + " " +
            ATTR_NAME + "=\"" + string(it->second.m_name.begin(), it->second.m_name.end()) + "\" " +
            ATTR_NICK_NAME + "=\"" + string(it->second.m_nickName.begin(), it->second.m_nickName.end()) + "\" " +
            ATTR_CHANNEL_NAME + "=\"" + string(it->second.m_channelName.begin(), it->second.m_channelName.end()) + "\" " + ">\n";

        xml += "<" + NODE_AUDIO_SETTINGS + " " +
            ATTR_DENOISE_LEVEL + "=\"" + string(itoa(it->second.m_noiseCancel, buffer, 10)) + "\" " +
            ATTR_ECHO_CANCEL + "=\"" + string(itoa(it->second.m_echoCancel, buffer, 10)) + "\" ";
            if (groupType == GROUP_TYPE_RECEIVERS)
            {
                xml += ATTR_SRC_VOLUME_LEVEL + "=\"" + string(itoa(it->second.m_SrcVolumeLevel, buffer, 10)) + "\" ";
            }
            else
            {
                xml += ATTR_MIC_GAIN_LEVEL + "=\"" + string(itoa(it->second.m_MicGainLevel, buffer, 10)) + "\" ";
            }
            xml += ATTR_SOUND_SYS_WIN + "=\"" + string(itoa(it->second.m_isSoundSystemWin, buffer, 10)) + "\" " +
            ATTR_INPUT_SOUND_DEV_ID + "=\"" + string(it->second.m_InputSoundDevId.begin(), it->second.m_InputSoundDevId.end()) + "\" " +
            ATTR_OUTPUT_SOUND_DEV_ID + "=\"" + string(it->second.m_OutputSoundDevId.begin(), it->second.m_OutputSoundDevId.end()) + "\" " + ">\n";

        xml += "<" + NODE_AGC + " " +
            ATTR_ENABLE + "=\"" + string(itoa(it->second.m_AGC.m_enable, buffer, 10)) + "\" " +
            ATTR_GAIN_LEVEL + "=\"" + string(itoa(it->second.m_AGC.m_gainLevel, buffer, 10)) + "\" " +
            ATTR_MAX_INC + "=\"" + string(itoa(it->second.m_AGC.m_maxIncrement, buffer, 10)) + "\" " +
            ATTR_MAX_DEC + "=\"" + string(itoa(it->second.m_AGC.m_maxDecrement, buffer, 10)) + "\" " +
            ATTR_MAX_GAIN + "=\"" + string(itoa(it->second.m_AGC.m_maxGain, buffer, 10)) + "\" " + "/>\n";

        xml += "<" + NODE_VOICE_ACTIVATION + " " +
            ATTR_VOICE_ACTIVATION_ENABLE + "=\"" + string(itoa(it->second.m_EnableVoiceActivation, buffer, 10)) + "\" " +
            ATTR_VOICE_ACTIVATION_LEVEL + "=\"" + string(itoa(it->second.m_VoiceActivationLevel, buffer, 10)) + "\" " + "/>\n";

        xml += "</" + NODE_AUDIO_SETTINGS + ">\n";

        xml += "</" + nodeGroupName + ">\n";
    }

    xml += "</" + nodeGroupsName + + ">\n";

    return xml;
}

int BB_ConfigMgr::saveConfig()
{
    Lock lock(m_cs);

    string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
    xml += "<" + NODE_GROUPS + ">\n";
	
    xml += buildGroupConfig(m_sources, NODE_SOURCES, NODE_SOURCE, GROUP_TYPE_SOURCES);
    xml += buildGroupConfig(m_receivers, NODE_RECEIVERS, NODE_RECEIVER, GROUP_TYPE_RECEIVERS);
    xml += buildGroupConfig(m_restrictedServers, NODE_RESTRICTED_SERVERS, NODE_RESTRICTED_SERVER, GROUP_TYPE_RESTRICTED_SERVERS);

    xml += "</" + NODE_GROUPS + ">\n";

    FILE *pFile = fopen(CONFIG_FILE.c_str(), "wb");
	if (pFile == NULL)
	{
		return EXIT_FAILURE;
	}
	fwrite(xml.c_str(), 1 , xml.size(), pFile);
	fclose(pFile);

	return EXIT_SUCCESS;
}

ConnectionConfig BB_ConfigMgr::GetConnectionConfig(GroupType groupType)
{
    return _GetGroupConfig(groupType)->m_ConnectionConfig;
}

BB_GroupConfig BB_ConfigMgr::GetGroupConfig(GroupType groupType)
{
    return *(_GetGroupConfig(groupType));
}

void BB_ConfigMgr::AddGroupElement(GroupType groupType, const std::wstring name, const std::wstring nickName, const std::wstring channel)
{
    Lock lock(m_cs);

    BB_GroupConfig *groups = _GetGroupConfig(groupType);
    if (groups == NULL)
    {
        return;
    }

    BB_GroupElementConfig config;
    config.m_name = name;
    config.m_nickName = nickName;
    config.m_channelName = channel;
    groups->m_groupList.insert(pair<wstring, BB_GroupElementConfig>(name, config));
}

void BB_ConfigMgr::RemoveGroupElement(GroupType groupType, const std::wstring name)
{
    Lock lock(m_cs);

    BB_GroupConfig *groups = _GetGroupConfig(groupType);
    if (groups == NULL)
    {
        return;
    }

    groups->m_groupList.erase(name);
}


BB_GroupConfig *BB_ConfigMgr::_GetGroupConfig(GroupType groupType)
{
    switch (groupType)
    {
        case GROUP_TYPE_SOURCES:
        {
            return &m_sources;
        }
        case GROUP_TYPE_RECEIVERS:
        {
            return &m_receivers;
        }
        case GROUP_TYPE_RESTRICTED_SERVERS:
        {
            return &m_restrictedServers;
        }
        default:
        {
            return NULL;
        }
    }
}

BB_GroupElementConfig *BB_ConfigMgr::_GetGroupElementConfig(GroupType groupType, const wstring name)
{
    BB_GroupConfig *group = _GetGroupConfig(groupType);
    if (group == NULL)
    {
        return NULL;
    }

    map<wstring, BB_GroupElementConfig>::iterator it = group->m_groupList.find(name);
    if (it != group->m_groupList.end())
    {
        return &((*it).second);
    }

    return NULL;
}

BB_GroupElementConfig BB_ConfigMgr::GetGroupElementConfig(GroupType groupType, const wstring name)
{
    Lock lock(m_cs);

    BB_GroupConfig *group = _GetGroupConfig(groupType);
    if (group == NULL)
    {
        lock.Unlock();
        THROW_EXCEPT("No Group Element found");
    }

    map<wstring, BB_GroupElementConfig>::iterator it = group->m_groupList.find(name);
    if (it != group->m_groupList.end())
    {
        return (*it).second;
    }

    lock.Unlock();
    THROW_EXCEPT("No Group Element found");
}

void BB_ConfigMgr::SetIP(GroupType groupType, const wstring ip)
{
    Lock lock(m_cs);
    _GetGroupConfig(groupType)->m_ConnectionConfig.m_IP = ip;
}

void BB_ConfigMgr::SetTCP(GroupType groupType, int tcp)
{
    Lock lock(m_cs);
    _GetGroupConfig(groupType)->m_ConnectionConfig.m_TCP = tcp;
}

void BB_ConfigMgr::SetUDP(GroupType groupType, int udp)
{
    Lock lock(m_cs);
    _GetGroupConfig(groupType)->m_ConnectionConfig.m_UDP = udp;
}

void BB_ConfigMgr::SetSrvUser(GroupType groupType, const wstring srvUser)
{
    Lock lock(m_cs);
    _GetGroupConfig(groupType)->m_ConnectionConfig.m_srvUser = srvUser;
}

void BB_ConfigMgr::SetSrvUserPsw(GroupType groupType, const wstring srvUserPsw)
{
    Lock lock(m_cs);
    _GetGroupConfig(groupType)->m_ConnectionConfig.m_srvUserPsw = srvUserPsw;
}

void BB_ConfigMgr::SetSrvPsw(GroupType groupType, const wstring srvPsw)
{
    Lock lock(m_cs);
    _GetGroupConfig(groupType)->m_ConnectionConfig.m_srvPsw = srvPsw;
}

void BB_ConfigMgr::SetPath(GroupType groupType, const wstring path)
{
    Lock lock(m_cs);
    _GetGroupConfig(groupType)->m_ConnectionConfig.m_srvPsw = path;
}

void BB_ConfigMgr::SetGroupName(GroupType groupType, const wstring name, const std::wstring newName)
{
    Lock lock(m_cs);

    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_name = newName;
}

void BB_ConfigMgr::SetGroupNickName(GroupType groupType, const wstring name, const wstring nickName)
{
    Lock lock(m_cs);

    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_nickName = nickName;
}

void BB_ConfigMgr::SetGroupChannel(GroupType groupType, const wstring name, const wstring channel)
{
    Lock lock(m_cs);

    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_channelName = channel;
}

void BB_ConfigMgr::SetGroupAGC(GroupType groupType, const wstring name, AGC agc)
{
    Lock lock(m_cs);

    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_AGC = agc;
}

void BB_ConfigMgr::SetGroupEnableVoiceActivation(GroupType groupType, const wstring name, bool enable)
{
    Lock lock(m_cs);

    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_EnableVoiceActivation = enable;
}

void BB_ConfigMgr::SetGroupVoiceActivationLevel(GroupType groupType, const wstring name, int level)
{
    Lock lock(m_cs);

    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_VoiceActivationLevel = level;
}

void BB_ConfigMgr::SetGroupNoiseCancel(GroupType groupType, const wstring name, int noiseCancel)
{
    Lock lock(m_cs);

    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_noiseCancel = noiseCancel;
}

void BB_ConfigMgr::SetGroupEchoCancel(GroupType groupType, const wstring name, bool echoCancel)
{
    Lock lock(m_cs);

    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_echoCancel = echoCancel;
}

void BB_ConfigMgr::SetGroupMicGainLevel(GroupType groupType, const wstring name, int micGainLevel)
{
    Lock lock(m_cs);

    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_MicGainLevel = micGainLevel;
}

void BB_ConfigMgr::SetGroupSrcVolumeLevel(GroupType groupType, const wstring name, int srcVolumeLevel)
{
    Lock lock(m_cs);

    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_SrcVolumeLevel = srcVolumeLevel;
}

void BB_ConfigMgr::SetGroupSoundSystemWin(GroupType groupType, const wstring name, bool isSoundSystemWin)
{
    Lock lock(m_cs);

    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_isSoundSystemWin = isSoundSystemWin;
}

void BB_ConfigMgr::SetGroupInputSoundDevId(GroupType groupType, const wstring name, const wstring inputSoundDevId)
{
    Lock lock(m_cs);

    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_InputSoundDevId = inputSoundDevId;
}

void BB_ConfigMgr::SetGroupOutputSoundDevId(GroupType groupType, const wstring name, const wstring outputSoundDevId)
{
    Lock lock(m_cs);

    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_OutputSoundDevId = outputSoundDevId;
}

