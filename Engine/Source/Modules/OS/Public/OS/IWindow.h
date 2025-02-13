/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#pragma once

#include "OS/ModuleConfig.h"

typedef struct WindowCreateInfo
{
    const char* Name;
    void* ParentHandle;

    int32 Left, Top;
    int32 Width, Height;
} WindowCreateInfo;

C_ABI HG_OS_API bool HG_CDECL Window_Init(void* pWindowProcessFunc);
C_ABI HG_OS_API bool HG_CDECL Window_HandleMessages();
C_ABI HG_OS_API void* HG_CDECL Window_Create(WindowCreateInfo* pCreateInfo);
C_ABI HG_OS_API void HG_CDECL Window_Destroy(void* handle);