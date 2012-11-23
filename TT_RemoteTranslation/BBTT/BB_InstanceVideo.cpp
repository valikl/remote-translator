#include "BB_InstanceVideo.h"
#include "Utils/BB_Exception.h"
#include "Utils.h"
#include <vector>

using namespace std;

BB_InstanceVideo::BB_InstanceVideo(const BB_InstanceContext &context) :
    BB_Instance(context)
{
    m_videoWinThread = NULL;
    m_videoLoopThread = NULL;
    m_stopThread = false;
}

BB_InstanceVideo::~BB_InstanceVideo(void)
{
	// We don't want to call TT functions in Dtor
	// Caller must call finalize()

    if (m_videoWinThread != NULL)
    {
        if (m_videoWin->IsActive())
        {
            m_videoWin->BBDestroy();
        }

        StopVideoThreads();
    }
}

int BB_InstanceVideo::GetVideoUserId()
{
    std::vector<BB_ChannelUser> userList;
    try
    {
        getUsers(userList);
    }
    catch(BB_Exception excp)
    {
        THROW_EXCEPT("Video stream does not exist");
    }

    // Check if Video User exists
    for (unsigned int i = 0; i < userList.size(); i++)
    {
        if (userList[i].m_isVideo)
        {
            return userList[i].m_id;
        }
    }

    THROW_EXCEPT("Video stream does not exist");
}

void BB_InstanceVideo::OpenVideoWindow(HWND hEffectiveWnd)
{
    // Check if Video User exists. If not exist - exception is thrown
    GetVideoUserId();

    if (m_videoWinThread != NULL)
    {
        if (m_videoWin->IsActive())
        {
            // Video window is already opened
            THROW_EXCEPT("Video window already opened");
        }
        else
        {
            // Window was closed/destroyed
            StopVideoThreads();
        }
    }
    m_stopThread = false;

    // Create window in thread
    m_videoWin = new BB_Window(BB_VIDEO_WINDOW_CLASS, BB_VIDEO_WINDOW_CHANNEL, hEffectiveWnd);
    m_videoWinThread = new Thread(m_videoWin);

    // Create video loop thread
    m_videoLoopThread = new Thread(this);
}

void BB_InstanceVideo::StopVideoThreads()
{
    // Caller must check whether Video window is active

    // Stop all the threads
    m_stopThread = true;
    m_videoLoopThread->Join();
    m_videoWinThread->Join();

    delete m_videoLoopThread;
    delete m_videoWinThread;
    delete m_videoWin;
    m_videoLoopThread = NULL;
    m_videoWinThread = NULL;
    m_videoWin = NULL;
}

void BB_InstanceVideo::run()
{
    int userId;
    TRY_BLOCK_RETURN_ON_ERR(
        userId = GetVideoUserId();
    );

    int cmdId = TT_DoSubscribe(m_ttInst, userId, (SUBSCRIBE_VIDEO | SUBSCRIBE_INTERCEPT_VIDEO));
    if(cmdId > 0)
    {
         cout << "Subscribing to video events from #" << userId << endl;
    }
    else
    {
         cout << "Failed to issue subscribe command" << endl;
    }

    // Wait in order to be sure video window was loaded
    Sleep(5000);

    HDC hDC = GetDC(m_videoWin->BBGetHandle());

    TTMessage msg;
    int wait_ms = 10000;
    int frameIdx = 0;
    int loopCnt = 0;
    vector<int> droppedFrames;

    while(!m_stopThread           &&
          m_videoWin->IsActive()  &&
          TT_GetMessage(m_ttInst, &msg, &wait_ms))
    {
        if (msg.wmMsg == WM_TEAMTALK_USER_VIDEOFRAME)
        {
            // Drop frames
            if (frameIdx == 101)
            {
                frameIdx = 0;
            }

            if (frameIdx == 0)
            {
                droppedFrames.clear();
                GetDroppedFrames(BB_ClientConfigMgr::Instance().getConfig().m_VideoQuality,
                    droppedFrames, loopCnt++);
            }           

            if (IsFrameDropped(frameIdx++, droppedFrames))
            {
                continue;
            }

            processTTMessage(msg);
            VideoFrame videoFrame;
            TT_AcquireUserVideoFrame(m_ttInst, userId, &videoFrame);

            // Calculate coordinates
            RECT rect;
            LONG width = 600;
            LONG height = 400;
            if (GetWindowRect(m_videoWin->BBGetHandle(), &rect))
            {
                width = rect.right - rect.left;
                height = rect.bottom - rect.top;
            }

            TT_PaintVideoFrame(m_ttInst, userId, hDC, 0, 0, width, height);
            TT_ReleaseUserVideoFrame(m_ttInst, userId);
        }
    }

    ReleaseDC(m_videoWin->BBGetHandle(), hDC);
}

void BB_InstanceVideo::GetDroppedFrames(int videoQuality, vector<int>& droppedFrames, int seed)
{
    droppedFrames.clear();
    //generates a new random set each time:
    srand(seed);
    for (int i = 0; i < 100 - videoQuality; ++i)
        droppedFrames.push_back(rand()%100);
}

bool BB_InstanceVideo::IsFrameDropped(int frameIdx, vector<int>& droppedFrames)
{
    vector<int>::iterator it = find(droppedFrames.begin(), droppedFrames.end(), frameIdx);
    return it != droppedFrames.end();
}

