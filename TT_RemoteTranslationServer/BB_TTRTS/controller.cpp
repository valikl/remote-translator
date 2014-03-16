#include "controller.h"


Controller::Controller():_mainInstance(NULL)
{
    TT_SetLicenseInformation(L"Bnei Baruch", 1600664704);
}

Controller::~Controller(){

}

void Controller::init(){
    BB_InstanceContext context;
    initInstanceContext(context);

    _mainInstance = new MainInstance(context);
    try
    {
        _mainInstance->login();
    }
    catch(BB_Exception excp)
    {
        delete _mainInstance;
        _mainInstance = NULL;
        THROW_EXCEPT(excp.GetInfo());
    }
}

void Controller::finalize(){


}

Controller& Controller::Instance()
{
    static Controller instance;
    return instance;
}

void Controller::initInstanceContext(BB_InstanceContext &context)
{
    ClientConfig config = ConfigManager::Instance().getConfig();
    context.m_TCP = config.m_TCP;
    context.m_IP = config.m_IP;
    context.m_UDP = config.m_UDP;
    context.m_srvPsw = config.m_srvPsw;
    context.m_srvUser = config.m_srvUser;
    context.m_srvUserPsw = config.m_srvUserPsw;
    context.m_audioDir = DEFAULT_AUDIO_STORAGE;
}
