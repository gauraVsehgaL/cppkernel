#pragma once

void* __cdecl operator new(size_t size, POOL_TYPE Pool, unsigned long Tag = 'ktd')
{
	return ExAllocatePoolWithTag(Pool, size, Tag);
}

void* __cdecl operator new[](size_t size, POOL_TYPE Pool, unsigned long Tag = 'ktd')
{
	return ExAllocatePoolWithTag(Pool, size, Tag);
}

//	Placement new
inline void* operator new(size_t, void* where)
{
	return where;
}

void __cdecl operator delete(void *ptr, size_t)
{
	ExFreePool(ptr);
}

void __cdecl operator delete(void *ptr)
{
	ExFreePool(ptr);
}

void __cdecl operator delete[](void *ptr, size_t)
{
	ExFreePool(ptr);
}

void __cdecl operator delete[](void *ptr)
{
	ExFreePool(ptr);
}

// TEMPLATE CLASS remove_reference
template<class _Ty>
struct remove_reference
{	// remove reference
	typedef _Ty type;
};

template<class _Ty>
struct remove_reference<_Ty&>
{	// remove reference
	typedef _Ty type;
};

template<class _Ty>
struct remove_reference<_Ty&&>
{	// remove rvalue reference
	typedef _Ty type;
};

template <typename T>
typename remove_reference<T>::type&& move(T&& arg)
{
	return static_cast<typename remove_reference<T>::type&&>(arg);
}

// TEMPLATE FUNCTION forward
template<class _Ty> inline
constexpr _Ty&& forward(
	typename remove_reference<_Ty>::type& _Arg)
{	// forward an lvalue as either an lvalue or an rvalue
	return (static_cast<_Ty&&>(_Arg));
}

template<class _Ty> inline
constexpr _Ty&& forward(
	typename remove_reference<_Ty>::type&& _Arg)
{	// forward an rvalue as an rvalue
	return (static_cast<_Ty&&>(_Arg));
}


