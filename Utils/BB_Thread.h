#pragma once
#include "windows.h"
#include "IRunnable.h"

// Usage
// VideoJob *obj = new VideoJob();
// Thread thread = new Thread(obj);

class Thread
{
public:

    Thread(IRunnable *pJob);
    ~Thread();

    // Waits for this thread to die. Returns FALSE if dwMilliseconds != INFINITE and
    // returned status is WAIT_TIMEOUT
    BOOL Join(DWORD dwMilliseconds = INFINITE);

    HANDLE GetThreadHandle() { return m_hThread; }

protected:
    static DWORD WINAPI ThreadProc(LPVOID lpParameter);

    IRunnable *m_pJob;
    HANDLE m_hThread;
    HANDLE m_hStartEvent;
    DWORD m_nThreadID;
};





