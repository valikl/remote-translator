#pragma once
#include "windows.h"
#include "IRunnable.h"

// Usage
// VideoWindow *obj = new VideoWindow();
// Thread thread = new Thread(obj);

class Thread
{
public:

    Thread(IRunnable *pJob);
    ~Thread();

    // Waits for this thread to die. Returns FALSE if dwMilliseconds != INFINITE and
    // returned status is WAIT_TIMEOUT
    BOOL Join(DWORD dwMilliseconds = INFINITE);

protected:
    static DWORD WINAPI ThreadProc(LPVOID lpParameter);

    IRunnable *m_pJob;
    HANDLE m_hThread;
    HANDLE m_hStartEvent;
    DWORD m_nThreadID;
};





