#pragma once

template<typename... Types>
struct Visitor;

template<typename T, typename... Types>
struct Visitor<T, Types...> : Visitor<Types...>
{
	using Visitor<Types...>::visitor;
	virtual void visitor(T&) = 0;
};

template<typename T>
struct Visitor<T>
{
	virtual void visitor(T&) = 0;
};