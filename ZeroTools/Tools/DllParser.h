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
			/*��extern "C"��������ǿ�Ƹ�������������Ʊ���C���Ե�������ʽ��������Ϊ��
			�����ǿ�ƵĻ���VS�ͽ���ĺ��������C++��������ʽ��������ĺ������������һ
			Щ����ķ��š�DLL����ĺ������־Ͳ������ڴ�����д���Ǹ��������ˡ���Ȼ������
			extern "C"�����ܵ��øú�����ֻ������������Ȳ��DLL�е���ʵ����������
			��������VC�ṩ��dumpbin���߲��DLL�е���������������������C++���Ա�������ԣ�
			����ʹ�ú��ֹ������޹ء����⣬�����ڵ�WIN32�����У�cdecl��stdcall�ĵ��÷�
			ʽ����ȫһ���ģ��㲻�õ������ǲ����ݡ�*/
			FARPROC/*�����͵�ָ��*/ func = GetProcAddress(m_hModule, name.data());
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
			std::string errInfo("δ�ҵ��˺���");
			throw std::exception(errInfo.data());
		}

		return f(std::forward<Args>(args)...);
	}

private:
	HMODULE				m_hModule = NULL;
	mapNameFunc			m_map;
};
