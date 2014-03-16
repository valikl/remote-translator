#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "BB_Instance.h"
#include "maininstance.h"
#include "Utils/Lock.h"
#include "Utils/BB_Exception.h"
#include "configmanager.h"

class Controller
{
public:

    ~Controller(void);

    // Returns the instance of the singleton
    static Controller &Instance();

    // connect to the server
    void init();

    // disconnect etc.
    void finalize();
private:
        Controller();
        MainInstance* _mainInstance;
        void initInstanceContext(BB_InstanceContext &context);
};

#endif // CONTROLLER_H
