#ifndef MAININSTANCE_H
#define MAININSTANCE_H

#include "../Utils/IRunnable.h"
#include "../Utils/BB_Thread.h"
#include "../Interfaces/BB_Instance.h"

class MainInstance : public BB_Instance,public IRunnable
{
public:
    MainInstance(const BB_InstanceContext &context);

    ~MainInstance();

    virtual void run();

    virtual void init();
    virtual void finalize();
};

#endif // MAININSTANCE_H
