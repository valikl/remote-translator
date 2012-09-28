#include "BB_Thread.h"
#include <iostream>
using namespace std;

Thread::Thread(IRunnable *pJob) : m_pJob(pJob)
{
    m_hStartEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
    if( NULL == m_hStartEvent )
    {
        cout << "Failed to create sync event. GetLastError: " << ::GetLastError() << endl;
    }

    m_hThread = ::CreateThread(NULL, 0, Thread::ThreadProc, this, NULL, &m_nThreadID);
    if( NULL == m_hThread )
    {
        cout << "Failed to create thread. GetLastError: " << ::GetLastError() << endl;
    }
}

Thread::~Thread()
{
    //Wait for thread to initialize before destructing the object
    WaitForSingleObject(m_hStartEvent, INFINITE);
    ::CloseHandle(m_hStartEvent);

    ::CloseHandle(m_hThread);
}

BOOL Thread::Join(DWORD dwMilliseconds)
{
    return (WAIT_TIMEOUT != ::WaitForSingleObject(m_hThread, dwMilliseconds));
}

DWORD WINAPI Thread::ThreadProc(LPVOID lpParameter)
{
    Thread* pThread = reinterpret_cast<Thread*>(lpParameter);
    IRunnable *pJob = pThread->m_pJob;
    //Now it's safe to continue constructor execution
    ::SetEvent(pThread->m_hStartEvent);

    try
    {
        pJob->Run();
    }
    catch (const exception& e)
    {
        cout << "Exception: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Exception: Unknown exception " << endl;
    }
    return 0;
}



