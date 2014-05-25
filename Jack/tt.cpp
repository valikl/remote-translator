#ifdef WIN32
#include <windows.h>
#endif
#include <sys/stat.h>
#include "TeamTalk4.h"
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

#include "Instance.h"

#ifdef UNICODE
#define cout wcout
#define cin wcin
#define string wstring
#define ostringstream wostringstream
#define istringstream wistringstream
#define _T(x) L ## x
#else
#define _T
#endif


void processTTMessage(const TTMessage& msg);
string get_str(const string& input);
int get_int(int value);

//int main(int argc, TTCHAR* argv[])
int main(int argc, const char *argv[], const char *env[])
{
	if(argc != 10){
        cout << "wrong number of parameters" << endl << "1)(to_merkaz / to_internet) 2)ip_addr 3)server_password 4)username" << endl;
        cout << " 5)password 6)channel path 7)channel password 8)Username" << endl;
        cout << "for empty put \"\"" << endl;
        exit(0);
	}

    string    jack_chan = _T(argv[9]);
    string    my_app_name = _T(argv[0]);

    BB_InstanceContext context;
    context.m_IP = _T(argv[2]);
    context.m_TCP = 10333;
    context.m_UDP = 10333;
    context.m_srvPsw = _T(argv[3]);
    context.m_srvUser = _T(argv[4]);
    context.m_srvUserPsw = _T(argv[5]);
    context.m_nickName = _T(argv[8]);
    context.m_channelPath = _T(argv[6]);
    context.m_channelPsw = _T(argv[7]);

    TT_SetLicenseInformation(_T("Bnei Baruch"), 1600664704);

	string role = _T(argv[1]);
    bool role_to_internet = (role == "to_internet");
    BB_Instance * inst = new BB_Instance(context, role_to_internet);
    if (!inst->init())
    {
        cout << "Cannot continue. Program terminated." << endl;
        exit(0);
    }

    if (role_to_internet)
    {
        inst->setClassroom();
        sleep(5);
        sleep(5);
		system(("/usr/local/bin/jack_connect system:capture_"+jack_chan+" `basename "+my_app_name+"`:in1").c_str());
		system(("/usr/local/bin/jack_connect system:capture_"+jack_chan+" `basename "+my_app_name+"`:in2").c_str());
        inst->enableTransmission();
	}
    else
    {
        inst->startSoundLoopbackTest();
		system("echo sound_test_start");
        system(("/usr/local/bin/jack_connect `basename "+my_app_name+"`:out1  system:playback_"+jack_chan).c_str());
		system("echo sound_test_stop");
        inst->stopSoundLoopbackTest();
	}

    while (1)
    {
        bool killInst = inst->loop();

        while (1)
        {
            inst->finalize();
			bool initOk;
            if (killInst)
			{			
				delete inst;
				inst = new BB_Instance(context, role_to_internet);
				initOk = inst->init();
			}
			else
			{
				initOk = inst->connect();	
			}
            if (initOk)
            {
                if (role_to_internet)
                {
                    inst->setClassroom();
                    inst->enableTransmission();
                }
                else
                {
                    inst->startSoundLoopbackTest();
                    inst->stopSoundLoopbackTest();
                }
                break;
            }
			// Wait 10 sec
			for (int i = 0; i < 10; i++)
			{
				sleep(1);
			}
        }
    }

/*
    while(1)
    {
        // Every 10 sec.
        for (int i = 0; i < 10; i++)
        {
            sleep(1);
        }

        if (!inst->isInstExist())
        {
           cout << "Instance not found" << endl;
           inst->finalize();
           delete inst;
           inst = new BB_Instance(context, role_to_internet);
           inst->init();
        }

        if (!inst->isUserExist())
        {
           cout << "User not found" << endl;
           inst->finalize();
           delete inst;
           inst = new BB_Instance(context, role_to_internet);
           inst->init();
        }

        if (role_to_internet)
        {
            inst->setClassroom();
        }
    }
*/

}



