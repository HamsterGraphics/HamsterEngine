/*
 * Copyright (c) 2025 HamsterGraphics
 *
 * https://github.com/HamsterGraphics/HamsterEngine
 *
 */

#include "Core/Assert.h"
#include "Core/BasicTypes.h"
#include "Core/TypeTraits.h"

#include <atomic>

namespace hg
{

/// <summary>
/// Thread-safe reference count object which can be used to inherit conveniently.
/// </summary>
class RefCountObject
{
public:
	RefCountObject() :
		m_refCount(0)
	{
	}

	RefCountObject(const RefCountObject& other) = delete;
	RefCountObject& operator=(const RefCountObject& other) = delete;
	// std::atomic doesn't define move constructor/assign operator.
	// https://stackoverflow.com/questions/14182258/c11-write-move-constructor-with-atomicbool-member
	RefCountObject(RefCountObject&& other) = delete;
	RefCountObject& operator=(RefCountObject&& other) = delete;

	virtual ~RefCountObject()
	{
		Assert(0 == m_refCount.load());
	}

	uint32 AddRef() const
	{
		return ++m_refCount;
	}

	uint32 Release() const
	{
		int32 refCount = --m_refCount;
		if (0 == refCount)
		{
			delete this;
		}

		return refCount;
	}

	uint32 GetRefCount() const
	{
		return m_refCount.load();
	}

private:
	mutable std::atomic<int32> m_refCount;
};

/// <summary>
/// RefCountPtr helps to manage lifetime of objects which use heap memory.
/// Windows ComPtr is platform specified implementation.
/// std::shared_ptr/std::weak_ptr may have different STL versions between user program and library.
/// </summary>
/// <typeparam name="T">Reference object type</typeparam>
template<typename T>
class RefCountPtr
{
public:
	// Contructors
	RefCountPtr() :
		m_ptr(nullptr)
	{
	}

	RefCountPtr(decltype(__nullptr)) :
		m_ptr(nullptr)
	{
	}

	RefCountPtr(T* pOther) :
		m_ptr(pOther)
	{
		InternalAddRef();
	}

	template<typename U,
		typename = std::enable_if<std::is_convertible_v<U*, T*>>>
	explicit RefCountPtr(U* pOther) :
		m_ptr(pOther)
	{
		InternalAddRef();
	}

	// Copy
	RefCountPtr(const RefCountPtr& other) :
		m_ptr(other.m_ptr)
	{
		InternalAddRef();
	}

	template<typename U,
		typename = std::enable_if<std::is_convertible_v<U*, T*>>>
	RefCountPtr(const RefCountPtr<U>& other) :
		m_ptr(other.m_ptr)
	{
		InternalAddRef();
	}

	// Move
	RefCountPtr(RefCountPtr&& other) :
		m_ptr(other.m_ptr)
	{
		other.m_ptr = nullptr;
	}

	template<typename U,
		typename = std::enable_if<std::is_convertible_v<U*, T*>>>
	RefCountPtr(RefCountPtr&& other) :
		m_ptr(other.m_ptr)
	{
		other.m_ptr = nullptr;
	}

	// Destroy
	~RefCountPtr()
	{
		InternalRelease();
	}

	// Assignment
	RefCountPtr& operator=(decltype(__nullptr))
	{
		InternalRelease();
		return *this;
	}

	RefCountPtr& operator=(T* pOther)
	{
		if (m_ptr != pOther)
		{
			RefCountPtr(pOther).Swap(*this);
		}
		return *this;
	}

	template<typename U,
		typename = std::enable_if<std::is_convertible_v<U*, T*>>>
	RefCountPtr& operator=(U* pOther)
	{
		RefCountPtr(pOther).Swap(*this);
		return *this;
	}

	RefCountPtr& operator=(const RefCountPtr& other)
	{
		return *this = other.m_ptr;
	}

	template<typename U,
		typename = std::enable_if<std::is_convertible_v<U*, T*>>>
	RefCountPtr& operator=(const RefCountPtr<U>& other)
	{
		return *this = other.m_ptr;
	}

	RefCountPtr& operator=(RefCountPtr&& other)
	{
		RefCountPtr(other).Swap(*this);
		return *this;
	}

	template<typename U,
		typename = std::enable_if<std::is_convertible_v<U*, T*>>>
	RefCountPtr& operator=(RefCountPtr<U>&& other)
	{
		return *this;
	}

	// Operations
	bool IsValid() const
	{
		return m_ptr != nullptr;
	}

	operator bool() const
	{
		return IsValid();
	}

	T* Get() const
	{
		return m_ptr;
	}

	operator T*() const
	{
		return m_ptr;
	}

	T* operator->() const
	{
		return m_ptr;
	}

	T** operator&()
	{
		return &m_ptr;
	}

	T** GetAddressOf()
	{
		return &m_ptr;
	}

	T* const* GetAddressOf() const
	{
		return &m_ptr;
	}

	[[nodiscard]] T** ReleaseAndGetAddressOf()
	{
		InternalRelease();
		return &m_ptr;
	}

	void Reset(T* ptr = nullptr)
	{
		T* pTemp = m_ptr;
		if (pTemp)
		{
			m_ptr = ptr;
			pTemp->Release();
		}
	}

	[[nodiscard]] T* Relinquish()
	{
		T* pTemp = m_ptr;
		m_ptr = nullptr;
		return pTemp;
	}

	uint32 GetRefCount() const
	{
		uint32 result = 0;
		if (m_ptr)
		{
			result = m_ptr->GetRefCount();
			Assert(result > 0);
		}

		return result;
	}

	void Swap(RefCountPtr& other)
	{
		T* pTemp = m_ptr;
		m_ptr = other.m_ptr;
		other.m_ptr = pTemp;
	}

	bool operator==(const RefCountPtr& other) const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const RefCountPtr& other) const
	{
		return m_ptr != other.m_ptr;
	}

	bool operator==(T* pOther) const
	{
		return m_ptr == pOther;
	}

	bool operator!=(T* pOther) const
	{
		return m_ptr != pOther;
	}

protected:
	template<class U> friend class RefCountPtr;

	void InternalAddRef()
	{
		if (m_ptr)
		{
			m_ptr->AddRef();
		}
	}

	void InternalRelease()
	{
		T* pTemp = m_ptr;
		if (pTemp)
		{
			m_ptr = nullptr;
			pTemp->Release();
		}
	}

private:
	T* m_ptr;
};

template<typename T, typename... Args>
RefCountPtr<T> MakeRefCountPtr(Args&&... args)
{
	return RefCountPtr<T>(new T(Forward<Args>(args)...));
}

}