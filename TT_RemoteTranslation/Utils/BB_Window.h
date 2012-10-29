#pragma once

#include <windows.h>
#include <string>
#include "../BBTT/IRunnable.h"

class BB_Window : public IRunnable
{
public:
    BB_Window(std::wstring windowClassName, std::wstring title, HWND hEffectiveWnd);
    ~BB_Window(void);

    // the thread procedure
    virtual void run();

    HWND BBGetHandle() { return m_hWnd; }
    void BBDestroy();

private:
    void BBCreateWindow();

    std::wstring m_windowClassName;
    std::wstring m_title;
    HWND m_hEffectiveWnd;
    HWND m_hWnd;
};
