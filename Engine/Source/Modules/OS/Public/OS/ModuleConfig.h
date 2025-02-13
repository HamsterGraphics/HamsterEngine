/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#pragma once

#include "Core/Assert.h"
#include "Core/BasicTypes.h"
#include "Core/CPU.h"
#include "Core/Platform.h"
#include "Core/TypeTraits.h"

#include <cstdlib>

#if defined(HG_OS_EXPORT)
#   define HG_OS_API API_EXPORT
#else
#   if defined(HG_OS_IMPORT)
#       define HG_OS_API API_IMPORT
#   else
#       define HG_OS_API
#   endif
#endif

#if defined(HG_PLATFORM_WINDOWS)
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   ifndef NOMINMAX
#       define NOMINMAX
#   endif
#   include <windows.h>

#   define HG_WINDOW_CLASS_NAME L"HamsterEngine"
#endif