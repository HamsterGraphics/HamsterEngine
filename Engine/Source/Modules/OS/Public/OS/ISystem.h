/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#pragma once

#include "OS/ModuleConfig.h"

///////////////////////////////////////////////////////////////////////////////////
// Environment Variable
///////////////////////////////////////////////////////////////////////////////////
C_ABI HG_OS_API bool HG_CDECL EnvironmentVariable_Contains(const char* key);
C_ABI HG_OS_API const char* HG_CDECL EnvironmentVariable_Get(const char* key);
C_ABI HG_OS_API bool HG_CDECL EnvironmentVariable_Set(const char* key, const char* value);

///////////////////////////////////////////////////////////////////////////////////
// Module
///////////////////////////////////////////////////////////////////////////////////
C_ABI HG_OS_API void* HG_CDECL Module_Load(const char* pFilePath);
C_ABI HG_OS_API void HG_CDECL Module_Unload(void* pModule);
C_ABI HG_OS_API void* HG_CDECL Module_GetFunctionAddress(void* pModule, const char* pFunctionName);

///////////////////////////////////////////////////////////////////////////////////
// Time
///////////////////////////////////////////////////////////////////////////////////
typedef struct TimeInfo
{
	int64 Frequency;
	float SecondsPerCycle;
} TimeInfo;

C_ABI HG_OS_API bool HG_CDECL Time_Init(TimeInfo* pInfo);
C_ABI HG_OS_API int64 HG_CDECL Time_QueryCounter();