// C++11.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <map>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <xtr1common>
#include <memory>
#include <thread>
#include "..\ZeroTools\Tools\Optional.h"
#include "..\ZeroTools\Tools\Lazy.h"
#include "..\ZeroTools\Tools\DllParser.h"
#include <chrono>
#include <mutex>
#include "Timer.h"
#include <hash_map>
#include "SimpleEvent.h"
#include "Visitor.h"

#define New   new(_NORMAL_BLOCK, __FILE__, __LINE__)  

template<typename T>
using map_str_T = std::map < std::string, T > ;
int func(int = 0, int = 0)
{
	return 0;
}

template<typename TR>
std::string/*&&*/ type_name()
{
	//typedef typename std::remove_reference<T>::type TR;
	std::string tn = typeid(TR).name();
	if (std::is_const<TR>::value)
	{
		tn += " const";
	}
	if (std::is_volatile<TR>::value)
	{
		tn += " volatile";
	}
	if (std::is_lvalue_reference<TR>::value)
	{
		tn += " &";
	}
	if (std::is_rvalue_reference<TR>::value)
	{
		tn += " &&";
	}

	return /*std::move*/(tn);
}

template<typename T>
void test(T&& t)
{
	std::cout << type_name<T>() << std::endl;
}

int fn(int)
{
	return int();
}

struct MyStruct
{
	MyStruct(int i)
		:m_i(i)
	{
		std::cout << "lazy" << m_i << std::endl;
	}
	~MyStruct()
	{
		std::cout << "destruct" << std::endl;
	}

	int m_i = 0;
};

int foo()
{
	return 2;
}

class A
{
public:
	A()
	{
		static int i = 0;
		std::cout << i << std::endl;
	}
	~A()
	{}

public:
	void fun(int a)
	{
		std::cout << "A::fun" << std::endl;
	}
};

class B /*: public A*/
{
public:
	B()
	{
		int i = 0;
		++i;
	}
	~B()
	{}

	//using A::fun;//所在的访问权限决定了 外面能否使用
	void fun(int a)
	{
		std::cout << "B::fun" << std::endl;
	}
private:
	static A a;
};

A B::a = A();

std::mutex g_mutex;

#define SQR(x) x*x
void Func(char* p)
{
	printf("%d\n", sizeof(p));
}
int _tmain(int argc, _TCHAR* argv[])
{
/*	map_str_T<int> mapInt;

	std::string str("abd");
	test(str);
	test(std::move(str));

	double db = atof("123");

	int* i = new int();
	typedef std::result_of<decltype(fn)&(int)>::type A;


	class TT
	{
	public:
		TT(int i, int j)
			: m_i(i)
			, m_j(j)
		{}
		~TT()
		{}

		int m_i = 0;
		int m_j = 0;
	};


	Optional<TT> ttt;
	ttt.Emplace(1, 2);
	if (ttt)
	{
		std::cout << "Init" << (*ttt).m_i << "  " << (*ttt).m_j << std::endl;
	}
	else
	{
		std::cout << "UnInit" << std::endl;
	}

	typedef std::shared_ptr<MyStruct> MyStructPtr;
	Lazy<MyStructPtr> qqq = lazy([]()->MyStructPtr
	{
		return std::make_shared<MyStruct>(10);
	});
	qqq.Value();


	DllParser dllparser;
	bool bRet = dllparser.Load("F:\\ZeroTools.dll");
	if (bRet)
	{
		std::cout << "ExcuteRet" << dllparser.ExcuteFunction<int(int, int)>("add", 1, 2);
		dllparser.UnLoad();
	}*/
// 	Timer t;
// 	//////////////////////////////////////////////////////////////////////////
// 	std::thread t1([]()
// 	{
// 		std::lock_guard<std::mutex> guard(g_mutex);
// 		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
// 		std::cout << "t1" << std::this_thread::get_id() << std::endl;
// 	});
// 	std::thread t2([]()
// 	{
// 		std::lock_guard<std::mutex> guard(g_mutex);
// 		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
// 		std::cout << "t2" << std::this_thread::get_id() << std::endl;
// 	});

	//std::thread t3(std::move(t1));
// 	std::cout << "elapsed:" << t.elapsed() << std::endl;
// 
// 	std::cout << "t1 start" << std::endl;
// 	t1.join();
// 	std::cout << "elapsed:" << t.elapsed() << std::endl;
// 
// 	std::cout << "t1 end" << std::endl;
// 
// 	std::cout << "t2 start" << std::endl;
// 	//t2.join();
// 	std::cout << "t2 end" << std::endl;
// 	//t3.join();

// 	stdext::hash_map<int, int> hash_int;
// 	hash_int.insert(std::make_pair(1, 1));

	A aaa;
	B bbb;
	//Visitor<A> visitor;

	SimpleEvent<std::function<void(int)>> event;
	int id1 = event.Connect([&aaa, &bbb](int i)
	{
		aaa.fun(i);
	});
	int id2 = event.Connect([&bbb](int i)
	{
		bbb.fun(i);
	});
	event.Notify(0);

// 	int m = 5;
// 	if(m++ > 5) 
// 		printf("%d\n", m);
// 	else
// 		printf("%d\n", -m);

	//char p[] = "hello!";
// 	void *p = malloc(100);
// 	printf("%d\n", sizeof(p));
	char p[100];
	Func(p);

	int a = 10; int k = 2; int m = 1;
	a /= SQR(k + m) / SQR(k + m);

	printf("%d\n", a);

	system("pause");
	return 0;
}

