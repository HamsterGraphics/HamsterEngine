/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#pragma once

#include "Core/Platform.h"

#define Assert(expression, ...) assert(expression)

#if defined(HG_PLATFORM_WINDOWS)
#   define HG_BREAKPOINT __debugbreak()
#elif defined(HG_PLATFORM_MACOS) || defined(HG_PLATFORM_IPHONE)
#   if defined(HG_CPU_ARCH_X86)
#       define HG_BREAKPOINT __asm volatile ("int $0x3")
#   elif defined(HG_CPU_ARCH_ARM) || defined(HG_CPU_ARCH_AARCH64)
#       define HG_BREAKPOINT __builtin_trap()
#   endif
#endif

#define UNUSED(a) ((void)(a))