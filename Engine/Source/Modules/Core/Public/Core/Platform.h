/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#pragma once

// Platform
#if defined(__ANDROID__)
#   define HG_PLATFORM_ANDROID
#elif defined(_WIN64) || defined(_WIN32)
#   define HG_PLATFORM_WINDOWS
#elif defined(__apple__) || defined(__APPLE__) || defined(__MACH__)
#   include "TargetConditionals.h" // See https://stackoverflow.com/a/49560690.
#   if defined(TARGET_OS_OSX)
#       define HG_PLATFORM_MACOS
#   endif
#   if defined(TARGET_OS_IPHONE)
#       define HG_PLATFORM_IPHONE // This is set for any non-Mac Apple products (IOS, TV, WATCH)
#   endif
#endif

// PTR_SIZE
#if defined(__WORDSIZE) // Defined by some variations of GCC.
#   define HG_PLATFORM_PTR_SIZE ((__WORDSIZE) / 8)
#elif defined(_WIN64) || defined(__LP64__) || defined(_LP64) || defined(_M_IA64) || defined(__ia64__) || defined(__arch64__) || defined(__aarch64__) || defined(__mips64__) || defined(__64BIT__) || defined(__Ptr_Is_64)
#   define HG_PLATFORM_PTR_SIZE 8
#elif defined(__CC_ARM) && (__sizeof_ptr == 8)
#   define HG_PLATFORM_PTR_SIZE 8
#else
#   define HG_PLATFORM_PTR_SIZE 4
#endif

// MIN_ALIGNMENT
#if defined(HG_PLATFORM_MACOS)
#   define HG_MALLOC_MIN_ALIGNMENT 16
#elif defined(HG_PLATFORM_ANDROID)
#   define HG_MALLOC_MIN_ALIGNMENT 8
#elif defined(HG_PLATFORM_WINDOWS)
#   define HG_MALLOC_MIN_ALIGNMENT (HG_PLATFORM_PTR_SIZE * 2)
#endif