/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#pragma once

#if defined(__clang__)
#   define HG_COMPILER_CLANG
#elif defined(_MSC_VER)
#   define HG_COMPILER_MSC
#elif defined(__GNUC__)
#   define HG_COMPILER_GCC
#endif

#if defined(HG_COMPILER_MSC)
#   define API_EXPORT __declspec(dllexport)
#   define API_IMPORT __declspec(dllimport)
#elif defined(HG_COMPILER_GCC)
#   define API_EXPORT __attribute__((visibility("default")))
#   define API_IMPORT
#else
#   define API_EXPORT
#   define API_IMPORT
#endif

#define HG_CDECL __cdecl

#if defined(__cplusplus)
#   define C_ABI extern "C"
#else
#   define C_ABI
#endif

#if defined(HG_CORE_EXPORT)
#   define HG_CORE_API API_EXPORT
#else
#   if defined(HG_MODULE_SHARED)
#       define HG_CORE_API API_IMPORT
#   else
#       define HG_CORE_API
#   endif
#endif