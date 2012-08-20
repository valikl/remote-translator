#include "BB_Translator.h"
#include "Utils.h"

using namespace std;

BB_Translator::BB_Translator(const BB_TranslatorContext &context) : m_context(context)
{
}

BB_Translator::~BB_Translator(void)
{
	/*
	delete m_channelOrigIn;
	delete m_channelOrigOut;
	delete m_channelLangFrom;
	delete m_channelLangTo;
	*/
}

int BB_Translator::init()
{
	// Get Dummy Instance
	BB_InstanceContext context;
	context.m_TCP = m_context.m_TCP;
	context.m_IP = m_context.m_IP;
	context.m_UDP = m_context.m_UDP;
	context.m_srvPsw = m_context.m_srvPsw;
	context.m_srvUser = m_context.m_srvUser;
	context.m_srvUserPsw = m_context.m_srvUserPsw;

	BB_Instance inst(context);

	std::vector<BB_Channel> channels;
	int ret = inst.getChannels(channels);
	if (ret != EXIT_SUCCESS)
	{
		return ret;
	}

	// Find Source Channel Id
	INT32 sourceChannelId = ROOT_PARENT_ID;
	for (int i=0; i < channels.size(); i++)
	{
		if (channels[i].name == SOURCE_CHANNEL_NAME)
		{
			sourceChannelId = channels[i].id;
			break;
		}
	}

	if (sourceChannelId == ROOT_PARENT_ID)
	{
		// Source Channel was not found;
		return EXIT_FAILURE;
	}

	// Build Happening
	// NOTE: We currently support only 1 Happening under root.
	Happening hap;
	for (int i=0; i < channels.size(); i++)
	{
		if (channels[i].parentId == ROOT_PARENT_ID  &&
			channels[i].name != SOURCE_CHANNEL_NAME &&
			channels[i].name != SOUND_CHECK_CHANNEL_NAME)
		{
			// This is Destination Channel. 
			// Convert from wstring to string and save
			string name;
			name.assign(channels[i].name.begin(), channels[i].name.end());
			hap.m_dstChannels.push_back(name);
			continue;
		}

		if (channels[i].parentId == sourceChannelId)
		{
			// This is Source
			string name;
			name.assign(channels[i].name.begin(), channels[i].name.end());
			hap.m_srcChannels.push_back(name);
		}
	}

	// Add Video channel. 
	// NOTE: It is currently hard coded.
	hap.m_videoChannel = VIDEO_CHANNEL_NAME;

	// Add Happening
	m_hapList.push_back(hap);
	return EXIT_SUCCESS;
}

