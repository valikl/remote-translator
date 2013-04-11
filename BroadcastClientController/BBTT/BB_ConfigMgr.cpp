#include "BB_ConfigMgr.h"
#include "Ticpp/tinyxml.h"
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
                    groupConfig.m_groupList.push_back(groupElement);
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

    for (unsigned int i=0; i < groupConfig.m_groupList.size(); i++)
    {
        xml += "<" + nodeGroupName + " " +
            ATTR_NAME + "=\"" + string(groupConfig.m_groupList[i].m_name.begin(), groupConfig.m_groupList[i].m_name.end()) + "\" " +
            ATTR_NICK_NAME + "=\"" + string(groupConfig.m_groupList[i].m_nickName.begin(), groupConfig.m_groupList[i].m_nickName.end()) + "\" " +
            ATTR_CHANNEL_NAME + "=\"" + string(groupConfig.m_groupList[i].m_channelName.begin(), groupConfig.m_groupList[i].m_channelName.end()) + "\" " + ">\n";

        xml += "<" + NODE_AUDIO_SETTINGS + " " +
            ATTR_DENOISE_LEVEL + "=\"" + string(itoa(groupConfig.m_groupList[i].m_noiseCancel, buffer, 10)) + "\" " +
            ATTR_ECHO_CANCEL + "=\"" + string(itoa(groupConfig.m_groupList[i].m_echoCancel, buffer, 10)) + "\" ";
            if (groupType == GROUP_TYPE_RECEIVERS)
            {
                xml += ATTR_SRC_VOLUME_LEVEL + "=\"" + string(itoa(groupConfig.m_groupList[i].m_SrcVolumeLevel, buffer, 10)) + "\" ";
            }
            else
            {
                xml += ATTR_MIC_GAIN_LEVEL + "=\"" + string(itoa(groupConfig.m_groupList[i].m_MicGainLevel, buffer, 10)) + "\" ";
            }
            xml += ATTR_SOUND_SYS_WIN + "=\"" + string(itoa(groupConfig.m_groupList[i].m_isSoundSystemWin, buffer, 10)) + "\" " +
            ATTR_INPUT_SOUND_DEV_ID + "=\"" + string(groupConfig.m_groupList[i].m_InputSoundDevId.begin(), groupConfig.m_groupList[i].m_InputSoundDevId.end()) + "\" " +
            ATTR_OUTPUT_SOUND_DEV_ID + "=\"" + string(groupConfig.m_groupList[i].m_OutputSoundDevId.begin(), groupConfig.m_groupList[i].m_OutputSoundDevId.end()) + "\" " + ">\n";

        xml += "<" + NODE_AGC + " " +
            ATTR_ENABLE + "=\"" + string(itoa(groupConfig.m_groupList[i].m_AGC.m_enable, buffer, 10)) + "\" " +
            ATTR_GAIN_LEVEL + "=\"" + string(itoa(groupConfig.m_groupList[i].m_AGC.m_gainLevel, buffer, 10)) + "\" " +
            ATTR_MAX_INC + "=\"" + string(itoa(groupConfig.m_groupList[i].m_AGC.m_maxIncrement, buffer, 10)) + "\" " +
            ATTR_MAX_DEC + "=\"" + string(itoa(groupConfig.m_groupList[i].m_AGC.m_maxDecrement, buffer, 10)) + "\" " +
            ATTR_MAX_GAIN + "=\"" + string(itoa(groupConfig.m_groupList[i].m_AGC.m_maxGain, buffer, 10)) + "\" " + "/>\n";

        xml += "<" + NODE_VOICE_ACTIVATION + " " +
            ATTR_VOICE_ACTIVATION_ENABLE + "=\"" + string(itoa(groupConfig.m_groupList[i].m_EnableVoiceActivation, buffer, 10)) + "\" " +
            ATTR_VOICE_ACTIVATION_LEVEL + "=\"" + string(itoa(groupConfig.m_groupList[i].m_VoiceActivationLevel, buffer, 10)) + "\" " + "/>\n";

        xml += "</" + NODE_AUDIO_SETTINGS + ">\n";

        xml += "</" + nodeGroupName + ">\n";
    }

    xml += "</" + nodeGroupsName + + ">\n";

    return xml;
}

int BB_ConfigMgr::saveConfig()
{
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
    return GetGroupConfig(groupType)->m_ConnectionConfig;
}

void BB_ConfigMgr::AddGroupElement(GroupType groupType, const std::wstring name, const std::wstring nickName, const std::wstring channel)
{
    BB_GroupConfig *groups = GetGroupConfig(groupType);
    if (groups == NULL)
    {
        return;
    }

    BB_GroupElementConfig config;
    config.m_name = name;
    config.m_nickName = nickName;
    config.m_channelName = channel;
    groups->m_groupList.push_back(config);
}

void BB_ConfigMgr::RemoveGroupElement(GroupType groupType, const std::wstring name)
{
    BB_GroupConfig *groups = GetGroupConfig(groupType);
    if (groups == NULL)
    {
        return;
    }

    for (unsigned int i=0; i < groups->m_groupList.size(); i++)
    {
        if (groups->m_groupList[i].m_name == name)
        {
            groups->m_groupList.erase(groups->m_groupList.begin() + i);
            return;
        }
    }
}


BB_GroupConfig *BB_ConfigMgr::GetGroupConfig(GroupType groupType)
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
    BB_GroupConfig *group = GetGroupConfig(groupType);
    if (group == NULL)
    {
        return NULL;
    }

    for (unsigned int i=0; i < group->m_groupList.size(); i++)
    {
        if (group->m_groupList[i].m_name == name)
        {
            return &(group->m_groupList[i]);
        }
    }

    return NULL;
}

BB_GroupElementConfig BB_ConfigMgr::GetGroupElementConfig(GroupType groupType, const wstring name)
{
    BB_GroupConfig *group = GetGroupConfig(groupType);
    if (group == NULL)
    {
        THROW_EXCEPT("No Group Element found");
    }

    for (unsigned int i=0; i < group->m_groupList.size(); i++)
    {
        if (group->m_groupList[i].m_name == name)
        {
            return group->m_groupList[i];
        }
    }

    THROW_EXCEPT("No Group Element found");
}

void BB_ConfigMgr::SetIP(GroupType groupType, const wstring ip) { GetGroupConfig(groupType)->m_ConnectionConfig.m_IP = ip; }
void BB_ConfigMgr::SetTCP(GroupType groupType, int tcp) { GetGroupConfig(groupType)->m_ConnectionConfig.m_TCP = tcp; }
void BB_ConfigMgr::SetUDP(GroupType groupType, int udp) { GetGroupConfig(groupType)->m_ConnectionConfig.m_UDP = udp; }
void BB_ConfigMgr::SetSrvUser(GroupType groupType, const wstring srvUser) { GetGroupConfig(groupType)->m_ConnectionConfig.m_srvUser = srvUser; }
void BB_ConfigMgr::SetSrvUserPsw(GroupType groupType, const wstring srvUserPsw) { GetGroupConfig(groupType)->m_ConnectionConfig.m_srvUserPsw = srvUserPsw; }
void BB_ConfigMgr::SetSrvPsw(GroupType groupType, const wstring srvPsw) { GetGroupConfig(groupType)->m_ConnectionConfig.m_srvPsw = srvPsw; }
void BB_ConfigMgr::SetPath(GroupType groupType, const wstring path) { GetGroupConfig(groupType)->m_ConnectionConfig.m_srvPsw = path; }

void BB_ConfigMgr::SetGroupName(GroupType groupType, const wstring name)
{
    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_name = name;
}

void BB_ConfigMgr::SetGroupNickName(GroupType groupType, const wstring name, const wstring nickName)
{
    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_nickName = nickName;
}

void BB_ConfigMgr::SetGroupChannel(GroupType groupType, const wstring name, const wstring channel)
{
    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_channelName = channel;
}

void BB_ConfigMgr::SetGroupAGC(GroupType groupType, const wstring name, AGC agc)
{
    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_AGC = agc;
}

void BB_ConfigMgr::SetGroupEnableVoiceActivation(GroupType groupType, const wstring name, bool enable)
{
    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_EnableVoiceActivation = enable;
}

void BB_ConfigMgr::SetGroupVoiceActivationLevel(GroupType groupType, const wstring name, int level)
{
    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_VoiceActivationLevel = level;
}

void BB_ConfigMgr::SetGroupNoiseCancel(GroupType groupType, const wstring name, int noiseCancel)
{
    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_noiseCancel = noiseCancel;
}

void BB_ConfigMgr::SetGroupEchoCancel(GroupType groupType, const wstring name, bool echoCancel)
{
    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_echoCancel = echoCancel;
}

void BB_ConfigMgr::SetGroupMicGainLevel(GroupType groupType, const wstring name, int micGainLevel)
{
    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_MicGainLevel = micGainLevel;
}

void BB_ConfigMgr::SetGroupSrcVolumeLevel(GroupType groupType, const wstring name, int srcVolumeLevel)
{
    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_SrcVolumeLevel = srcVolumeLevel;
}

void BB_ConfigMgr::SetGroupSoundSystemWin(GroupType groupType, const wstring name, bool isSoundSystemWin)
{
    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_isSoundSystemWin = isSoundSystemWin;
}

void BB_ConfigMgr::SetGroupInputSoundDevId(GroupType groupType, const wstring name, const wstring inputSoundDevId)
{
    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_InputSoundDevId = inputSoundDevId;
}

void BB_ConfigMgr::SetGroupOutputSoundDevId(GroupType groupType, const wstring name, const wstring outputSoundDevId)
{
    BB_GroupElementConfig *groupElement = _GetGroupElementConfig(groupType, name);
    if (groupElement == NULL)
    {
        return;
    }
    groupElement->m_OutputSoundDevId = outputSoundDevId;
}

