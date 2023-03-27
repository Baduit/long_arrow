#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

namespace long_arrow 
{
/*
** Proxy
*/
#define LONG_ARROW_GENERATE_PROXY(function)                                                                         \
	[]<typename... Args>(Args&&... args)                                                                            \
	{                                                                                                               \
		return [&args...]<typename T>(T&& t) { return function(std::forward<T>(t), std::forward<Args>(args)...); }; \
	}


/*
** Wrappers
*/
// For equivalent to const member function
template <typename T>
struct LongArrowObjectConstWrapper
{
	const T& wrapped;
};

// For equivalent to non const member function
template <typename T>
struct LongArrowObjectMutWrapper
{
	T& wrapped;
};

// For equivalent to member function with the rvalue ref-qualifier (the token && after the parameter list)
template <typename T>
struct LongArrowObjectMoveWrapper
{
	T&& wrapped;
};

/*
** Help overload --(int) to return the 
*/
#define LONG_ARROW_GENERATE_OPERATOR_POST_DECREMENT(Type)                         \
	long_arrow::LongArrowObjectConstWrapper<Type> operator--(const Type& t, int)  \
	{                                                                             \
		return long_arrow::LongArrowObjectConstWrapper<Type>{ .wrapped = t };     \
	}                                                                             \
                                                                                  \
	long_arrow::LongArrowObjectMutWrapper<Type> operator--(Type& t, int)          \
	{                                                                             \
		return long_arrow::LongArrowObjectMutWrapper<Type>{ .wrapped = t };       \
	}                                                                             \
                                                                                  \
	long_arrow::LongArrowObjectMoveWrapper<Type> operator--(Type&& t, int)        \
	{                                                                             \
		return long_arrow::LongArrowObjectMoveWrapper<Type>{ .wrapped = std::move(t) };      \
	}                                                                             \


/*
** Overload of >
*/
template <typename T, std::invocable<T> Proxy>
constexpr auto operator>(LongArrowObjectConstWrapper<T> wrapper, Proxy&& p)
{
	return p(wrapper.wrapped);
}

template <typename T, std::invocable<T&> Proxy>
constexpr auto operator>(LongArrowObjectMutWrapper<T> wrapper, Proxy&& p)
{
	return p(wrapper.wrapped);
}

template <typename T, std::invocable<T&&> Proxy>
constexpr auto operator>(LongArrowObjectMoveWrapper<T>&& wrapper, Proxy&& p)
{
	return p(std::move(wrapper.wrapped));
}



} // namespace long_arrow 