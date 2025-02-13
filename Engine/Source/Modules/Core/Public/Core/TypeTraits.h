/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#pragma once

#include <type_traits>

namespace hg
{

// std::move is only valid for lvalue and non-const objects, but no compiler warnings if you make mistakes.
// MoveTemp will validate in compile time to avoid possible performance loss.
template<typename T>
[[nodiscard]] constexpr std::remove_reference_t<T>&& MoveTemp(T&& value) noexcept
{
	using CastType = std::remove_reference_t<T>;
	static_assert(std::is_lvalue_reference_v<T>, "T is lvalue reference object.");
	static_assert(!std::is_same_v<CastType&, const CastType&>, "For a const object, MoveTemp doesn't take effect.");
	return static_cast<CastType&&>(value);
}

// Reference(S):
// - https://web.archive.org/web/20181115035420/http://cnicholson.net/2011/01/stupid-c-tricks-a-better-sizeof_array/
//
template<typename T, size_t NumT>
char(&CountOfRequireArrayArgumentT(const T(&)[NumT]))[NumT];

}

#define COUNTOF(x) sizeof(hg::CountOfRequireArrayArgumentT(x))