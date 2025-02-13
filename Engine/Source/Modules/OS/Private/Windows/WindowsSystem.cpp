/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#include "OS/ISystem.h"

///////////////////////////////////////////////////////////////////////////////////
// Environment Variable
///////////////////////////////////////////////////////////////////////////////////
bool EnvironmentVariable_Contains(const char* key)
{
	return ::GetEnvironmentVariableA(key, NULL, 0) > 0;
}

const char* EnvironmentVariable_Get(const char* key)
{
	// Limit according to http://msdn.microsoft.com/en-us/library/ms683188.aspx
	const DWORD buffSize = 65535;
	static char buffer[buffSize];
	return ::GetEnvironmentVariableA(key, buffer, buffSize) ? buffer : nullptr;
}

bool EnvironmentVariable_Set(const char* key, const char* value)
{
	return ::SetEnvironmentVariableA(key, value);
}

///////////////////////////////////////////////////////////////////////////////////
// Module
///////////////////////////////////////////////////////////////////////////////////
void* Module_Load(const char* pFilePath)
{
	return ::LoadLibraryA(pFilePath);
}

void Module_Unload(void* pModule)
{
	::FreeLibrary((HMODULE)pModule);
}

void* Module_GetFunctionAddress(void* pModule, const char* pFunctionName)
{
	return ::GetProcAddress((HMODULE)pModule, pFunctionName);
}

///////////////////////////////////////////////////////////////////////////////////
// Time
///////////////////////////////////////////////////////////////////////////////////
bool Time_Init(TimeInfo* pInfo)
{
	LARGE_INTEGER frequency;
	bool result = ::QueryPerformanceFrequency(&frequency);
	pInfo->Frequency = frequency.QuadPart;
	pInfo->SecondsPerCycle = 1.0f / static_cast<float>(pInfo->Frequency);
	return result;
}

int64 Time_QueryCounter()
{
	LARGE_INTEGER counter;
	::QueryPerformanceCounter(&counter);
	return counter.QuadPart;
}