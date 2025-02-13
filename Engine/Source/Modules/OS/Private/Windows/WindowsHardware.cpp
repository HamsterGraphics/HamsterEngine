/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#include "OS/IHardware.h"

///////////////////////////////////////////////////////////////////////////////////
// CPU
///////////////////////////////////////////////////////////////////////////////////
bool CPU_InitInfo(CPUInfo* pInfo)
{
    return true;
}

///////////////////////////////////////////////////////////////////////////////////
// DRAM
///////////////////////////////////////////////////////////////////////////////////
bool DRAM_InitInfo(DRAMInfo* pInfo)
{
	MEMORYSTATUSEX stat;
	stat.dwLength = sizeof(stat);
	::GlobalMemoryStatusEx(&stat);

	pInfo->TotalSize = stat.ullTotalPhys;
	pInfo->AvailableSize = stat.ullAvailPhys;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////
// Power
///////////////////////////////////////////////////////////////////////////////////
bool Power_UpdateStatus(PowerInfo* pInfo)
{
	static SYSTEM_POWER_STATUS status;
	BOOL result = ::GetSystemPowerStatus(&status);

	pInfo->IsACMode = status.ACLineStatus == 1;
	pInfo->IsBatteryMode = status.ACLineStatus == 0;

	if (pInfo->IsBatteryMode)
	{
		pInfo->BatteryLifePercent = status.BatteryLifePercent / 100.0f;
	}

	return result != 0;
}