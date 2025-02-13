/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#include "Application/IApplication.h"
#include "OS/IHardware.h"

#include <memory>

class TriangleApp : public hg::IApplication
{
public:
	virtual bool PreInit(hg::AppConfig* pConfig) override
	{
		pConfig->WindowPosX = 0;
		pConfig->WindowPosY = 0;
		pConfig->WindowWidth = 1920;
		pConfig->WindowWidth = 1080;

		CPU_InitInfo(&m_cpuInfo);
		DRAM_InitInfo(&m_dramInfo);
		Power_UpdateStatus(&m_powerInfo);
		return true;
	}

	virtual bool Init(void* pNativeWindowHandle) override
	{
		return true;
	}

	virtual void Shutdown() override
	{
	}

	virtual void Update(float deltaTime) override
	{
	}

	virtual void Render() override
	{
	}

	virtual const char* GetName() const override
	{
		return "00_Triangle";
	}

private:
	CPUInfo m_cpuInfo;
	DRAMInfo m_dramInfo;
	PowerInfo m_powerInfo;
};

DEFINE_APP_MAIN(TriangleApp);
