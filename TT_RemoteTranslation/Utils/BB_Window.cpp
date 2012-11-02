#include "BB_Window.h"

using namespace std;

BB_Window::BB_Window(wstring windowClassName, wstring title, HWND hEffectiveWnd) :
    m_windowClassName(windowClassName), m_title(title), m_hEffectiveWnd(hEffectiveWnd), m_hWnd(NULL)
{
}

BB_Window::~BB_Window(void)
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void BB_Window::BBCreateWindow()
{
    // Based on example from http://www.winprog.org/tutorial/simple_window.html

    HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hEffectiveWnd, GWL_HINSTANCE/*GWL_STYLE*/);

    // Registering the Window Class
    WNDCLASSEX wc;
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = m_windowClassName.c_str();
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        // TODO Throw exception "Window Registration Failed!"
        return;
    }

    // Creating the Window
    m_hWnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        m_windowClassName.c_str(),
        m_title.c_str(),
        WS_OVERLAPPEDWINDOW | WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
        NULL, NULL, hInstance, NULL);

    if(m_hWnd == NULL)
    {
        // TODO Throw exception "Window Creation Failed!"
        return;
    }

    ShowWindow(m_hWnd, SW_SHOWNORMAL);
    UpdateWindow(m_hWnd);
}

void BB_Window::run()
{
    BBCreateWindow();

    if (m_hWnd != NULL)
    {
        MSG Msg;
        while(GetMessage(&Msg, NULL, 0, 0) > 0)
        {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }

        if ((Msg.hwnd == m_hWnd || Msg.hwnd == NULL)
             &&
            ((Msg.message && WM_CLOSE != 0) || (Msg.message && WM_DESTROY != 0)))
        {
            m_hWnd = NULL;
        }
    }
}

void BB_Window::BBDestroy()
{
    DestroyWindow(m_hWnd);
}

bool BB_Window::IsActive()
{
    return (m_hWnd != NULL);
}
