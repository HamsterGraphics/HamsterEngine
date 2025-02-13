/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#include "OS/IWindow.h"

bool Window_Init(void* pWindowProcessFunc)
{
    WNDCLASSW windowClass;
    memset(&windowClass, 0, sizeof(windowClass));
    windowClass.style = 0;
    windowClass.lpfnWndProc = (WNDPROC)pWindowProcessFunc;
    windowClass.hInstance = (HINSTANCE)::GetModuleHandle(NULL);
    windowClass.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = HG_WINDOW_CLASS_NAME;
    ::RegisterClassW(&windowClass);
    return true;
}

bool Window_HandleMessages()
{
    MSG msg;
    msg.message = NULL;
    bool quit = false;
    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);

        if (WM_CLOSE == msg.message ||
            WM_QUIT == msg.message)
        {
            quit = true;
        }
    }
    return quit;
}

void* Window_Create(WindowCreateInfo* pCreateInfo)
{
    size_t charConverted = 0;
    WCHAR appName[256] = {};
    mbstowcs_s(&charConverted, appName, pCreateInfo->Name, COUNTOF(appName));
    
    HWND hwnd = ::CreateWindowW(HG_WINDOW_CLASS_NAME, appName, WS_OVERLAPPEDWINDOW,
        pCreateInfo->Left, pCreateInfo->Top, pCreateInfo->Width, pCreateInfo->Height,
        (HWND)pCreateInfo->ParentHandle, NULL, (HINSTANCE)GetModuleHandle(NULL), 0);

    ::ShowWindow(hwnd, SW_SHOW);
    return hwnd;
}

void Window_Destroy(void* handle)
{
    ::DestroyWindow((HWND)handle);
}