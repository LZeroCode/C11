#pragma once

#include <string>
#include <wtypes.h>
#include <map>
#include <functional>
#include <exception>
#include "dll_ZeroTools.h"


extern "C" ZeroTool int add(int a, int b)
{
	return a + b;
}

class ZeroTool DllParser
{
	typedef std::map<std::string, FARPROC> mapNameFunc;
public:
	DllParser();
	~DllParser();

public:
	bool Load(const std::string& path);
	bool UnLoad();

	template<typename T>
	std::function<T> GetFunction(const std::string& name)
	{
		auto it = m_map.find(name);
		if (it == m_map.end())
		{
			/*加extern "C"的作用是强制该输出函数的名称保留C语言的命名方式。这是因为，
			如果不强制的话，VS就将你的函数编译成C++的命名方式，即在你的函数名后面加上一
			些特殊的符号。DLL输出的函数名字就不是你在代码里写的那个函数名了。当然，不加
			extern "C"，仍能调用该函数，只不过，你必须先查出DLL中的真实函数名才行
			（可以用VC提供的dumpbin工具查得DLL中的输出函数名）。这件事是C++语言本身的特性，
			和你使用何种工程向导无关。此外，在现在的WIN32环境中，cdecl和stdcall的调用方
			式是完全一样的，你不用担心它们不兼容。*/
			FARPROC/*无类型的指针*/ func = GetProcAddress(m_hModule, name.data());
			if (nullptr == func)
				return nullptr;

			m_map.insert(std::make_pair(name, func));
		}

		it = m_map.find(name);
		return std::function<T>((T*)(it->second));
	}

	template<typename T, typename... Args>
	typename std::result_of<std::function<T>(Args...)>::type ExcuteFunction(const std::string& name, Args&&... args)
	{
		auto f = GetFunction<T>(name);
		if (nullptr == f)
		{
			std::string errInfo("未找到此函数");
			throw std::exception(errInfo.data());
		}

		return f(std::forward<Args>(args)...);
	}

private:
	HMODULE				m_hModule = NULL;
	mapNameFunc			m_map;
};
