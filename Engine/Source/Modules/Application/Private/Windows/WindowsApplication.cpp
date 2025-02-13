/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#include "Application/IApplication.h"
#include "OS/IHardware.h"
#include "OS/ISystem.h"
#include "OS/IWindow.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

int AppMain(int argc, char** argv, hg::IApplication* pApp)
{
	UNUSED(argc);
	UNUSED(argv);

    hg::AppConfig config;
    if (!pApp->PreInit(&config))
    {
        return 1;
    }

    Window_Init(WindowProc);
    WindowCreateInfo windowCI;
    memset(&windowCI, 0, sizeof(windowCI));
    windowCI.Name = pApp->GetName();
    windowCI.Left = config.WindowPosX;
    windowCI.Top = config.WindowPosY;
    windowCI.Width = config.WindowWidth;
    windowCI.Height = config.WindowHeight;
    void* windowHandle = Window_Create(&windowCI);
    if (!pApp->Init(windowHandle))
    {
        return 1;
    }

    TimeInfo timeInfo;
    Time_Init(&timeInfo);

    int64 lastCounter = Time_QueryCounter();
	bool quit = false;
	while (!quit)
    {
        int64 currentCounter = Time_QueryCounter();
        int64 deltaCounter = currentCounter - lastCounter;
        float deltaSeconds = static_cast<float>(deltaCounter) * timeInfo.SecondsPerCycle;
        lastCounter = currentCounter;

        quit = Window_HandleMessages();
		pApp->Update(deltaSeconds);
		pApp->Render();        
    }

    pApp->Shutdown();
    return 0;
}