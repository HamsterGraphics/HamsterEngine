/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#pragma once

#include "ModuleConfig.h"

namespace hg
{

typedef struct AppConfig
{
	int32 WindowPosX;
	int32 WindowPosY;
	int32 WindowWidth;
	int32 WindowHeight;
} AppConfig;

class HG_APP_API IApplication
{
public:
	virtual bool PreInit(AppConfig* pConfig) = 0;
	virtual bool Init(void* pNativeWindowHandle) = 0;
	virtual void Shutdown() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;

	virtual const char* GetName() const = 0;
};

}

#define DEFINE_APP_MAIN(AppClass) \
	int AppMain(int argc, char** argv, hg::IApplication* pApp); \
	int main(int argc, char** argv) \
	{ \
		static AppClass app = {}; \
		return AppMain(argc, argv, &app); \
	}
