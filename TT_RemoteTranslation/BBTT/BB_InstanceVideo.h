#pragma once

#ifdef WIN32
#include <windows.h>
#endif
#include <../TeamTalk/TeamTalk4.h>
#include "IRunnable.h"
#include "BB_Thread.h"
#include "Utils/BB_Window.h"
#include "BB_Instance.h"

const std::wstring BB_VIDEO_WINDOW_CLASS(L"BBVideoWindowClass");
const std::wstring BB_VIDEO_WINDOW_CHANNEL(L"Video Channel");

class BB_InstanceVideo : public BB_Instance, public IRunnable
{
public:
    BB_InstanceVideo(const BB_InstanceContext &context);
    ~BB_InstanceVideo(void);

    // the thread procedure
    virtual void run();

    // Operations
    void OpenVideoWindow(HWND hWnd);
    void KeepAlive();

private:
		
    static void GetDroppedFrames(int videoQuality, std::vector<int>& droppedFrames, int seed);
    static bool IsFrameDropped(int frameIdx, std::vector<int>& droppedFrames);

    void StopVideoThreads();
    int GetVideoUserId();

    BB_Window *m_videoWin;
    Thread *m_videoWinThread;
    Thread *m_videoLoopThread;
    bool m_stopThread;
    HWND m_hWnd;
};


