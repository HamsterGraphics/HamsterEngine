/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#pragma once

#include "OS/ModuleConfig.h"

///////////////////////////////////////////////////////////////////////////////////
// CPU
///////////////////////////////////////////////////////////////////////////////////
typedef struct CPUInfo
{
	char Vendor[128];
	char Brand[128];

	// Processor
	int16 PhyscialProcessorCount;
	int16 LogicalProcessorCount;

	// Cache
	uint32 L1CacheSize;
	uint32 L2CacheSize;
	uint32 L3CacheSize;
} CPUInfo;

C_ABI HG_OS_API bool HG_CDECL CPU_InitInfo(CPUInfo* pInfo);

///////////////////////////////////////////////////////////////////////////////////
// DRAM
///////////////////////////////////////////////////////////////////////////////////
typedef struct DRAMInfo
{
	uint64 TotalSize;
	uint64 AvailableSize;
} DRAMInfo;

C_ABI HG_OS_API bool HG_CDECL DRAM_InitInfo(DRAMInfo* pInfo);

///////////////////////////////////////////////////////////////////////////////////
// Power
///////////////////////////////////////////////////////////////////////////////////
typedef struct PowerInfo
{
	float BatteryLifePercent;

	bool IsACMode;
	bool IsBatteryMode;
} PowerInfo;

C_ABI HG_OS_API bool HG_CDECL Power_UpdateStatus(PowerInfo* pInfo);