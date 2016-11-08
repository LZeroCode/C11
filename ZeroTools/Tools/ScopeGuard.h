#pragma once
#include <functional>

//2015��12��28�� 09:27:02 by lyj
//�뿪��������һЩ���⴦����������
//ʹ��eg. char* pCh = new char[10];
//			SCOPE_EXIT({
//			delete[] pCh;
//		});
class CScopeGuard
{
public:
	CScopeGuard(const std::function<void()>& func)
		: m_func(func)
	{

	}
	~CScopeGuard()
	{
		m_func();
	}

protected:
	CScopeGuard(const CScopeGuard&);
	CScopeGuard& operator=(const CScopeGuard&);

private:
	std::function<void()>	m_func;
};

#define SCOPENAME_CAT(id) name_##id 
#define SCOPENAME(id) SCOPENAME_CAT(id) 
#define SCOPE_EXIT(func) CScopeGuard SCOPENAME(__COUNTER__)([=]()func)
