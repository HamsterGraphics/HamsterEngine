/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#pragma once

#include "Core/Assert.h"
#include "Core/BasicTypes.h"

#if defined(HG_APP_EXPORT)
#   define HG_APP_API API_EXPORT
#else
#   define HG_APP_API
#endif