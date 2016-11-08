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
#include <hash_map>
#include "..\ZeroTools\Tools\ScopeGuard.h"
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iosfwd>
#include <regex>
#include "..\ZeroTools\Tools\Timer.h"

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
	{
		int i = 10;
		std::cout << i << std::endl;
	}

	//using A::fun;//所在的访问权限决定了 外面能否使用
	void fun(int a)
	{
		std::cout << "B::fun" << std::endl;
	}
private:
	static A a;
};

//A B::a = A();

std::mutex g_mutex;
#define SQR(x) x*x
void Func(char* p)
{
	printf("%d\n", sizeof(p));
}
#define NONIUS_DETAIL_UNIQUE_NAME_HPP

#define NONIUS_DETAIL_UNIQUE_NAME_LINE_CAT(name, id) NONIUS_ ## name ## _ ## id
#define NONIUS_DETAIL_UNIQUE_NAME_LINE(name, id) NONIUS_DETAIL_UNIQUE_NAME_LINE_CAT(name, id)
#ifdef __COUNTER__
#define NONIUS_DETAIL_UNIQUE_NAME(name) NONIUS_DETAIL_UNIQUE_NAME_LINE(name, __COUNTER__)
#else // __COUNTER__
#define NONIUS_DETAIL_UNIQUE_NAME(name) NONIUS_DETAIL_UNIQUE_NAME_LINE(name, __LINE__)
#endif // __COUNTER__

#define SCOPECONTNAME class NONIUS_DETAIL_UNIQUE_NAME(aa)

class AAA
{
public:
	AAA();
	virtual ~AAA();

protected:
	virtual void func()
	{
	};
};

AAA::AAA()
{
}

AAA::~AAA()
{
	std::cout <<"~AAA"<< std::endl;
}

class BBB : public AAA
{
public:
	BBB();
	~BBB();

protected:
	virtual void func()
	{
		__super::func();
	};

};

BBB::BBB()
{
}

BBB::~BBB()
{
	std::cout << "~BBB" << std::endl;
}

struct DeleteObjectT
{
	template<typename T>
	void operator()(T* ptr) const
	{
		delete ptr;
	}
};
#include <numeric>

void swap(int& a, int& b)
{
	if (a != b)
	{
		a ^= b;
		b ^= a;
		a ^= b;
	}
}

int signreverse(int a)
{
	return ~a + 1;
}

int abs_ex(int val)
{
	int i = val >> 31;
	return (val^i) - i;
}

void getprime()
{
	const int MAXNUM = 100;
	bool flag[MAXNUM];
	memset(flag, false, sizeof(flag));
	int prime[MAXNUM / 3];

	int k = 0;
	for (int i = 2; i <= MAXNUM; ++i)
	{
		if (!flag[i])
		{
			prime[k++] = i;
			for (int j = i; j < MAXNUM; j += i)
				flag[j] = true;
		}
	}
	
	for (int i = 0; i < k; ++i)
	{
		std::cout << prime[i] << std::endl;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	std::map<int, int> map_int_int;
	for (int i = 0; i < 10000000; ++i)
	{
		map_int_int.insert(std::make_pair(i, i));
	}

	int nValue = 6666666;
	Timer ti;
	if (0 == map_int_int.count(nValue))
	{
	}
	std::cout << "count:" << ti.elapsed() << std::endl;

	ti.Reset();
	auto it = map_int_int.find(nValue);
	if (it != map_int_int.end())
	{
	}
	std::cout << "find:" << ti.elapsed() << std::endl;

	std::cout << "end" << std::endl;
	system("pause");

// 	getprime();
// 	int a = 1, b = 2;
// 	swap(a, b);
// 	std::cout << a << "--" << b << std::endl;
// 
// 	int val = -11;
// 	int absval = abs_ex(val);
// 	int rval = signreverse(val);
// 	std::cout << rval << std::endl;

#pragma region
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

	// 	A aaa;
	// 	B bbb;
	// 	//Visitor<A> visitor;
	// 
	// 	SimpleEvent<std::function<void(int)>> event;
	// 	int id1 = event.Connect([&aaa, &bbb](int i)
	// 	{
	// 		aaa.fun(i);
	// 	});
	// 	int id2 = event.Connect([&bbb](int i)
	// 	{
	// 		bbb.fun(i);
	// 	});
	// 	event.Notify(0);

	// 	int m = 5;
	// 	if(m++ > 5) 
	// 		printf("%d\n", m);
	// 	else
	// 		printf("%d\n", -m);

	//char p[] = "hello!";
	// 	void *p = malloc(100);
	// 	printf("%d\n", sizeof(p));
	// 	char p[100];
	// 	Func(p);
	// 
	// 	int a = 10; int k = 2; int m = 1;
	// 	a /= SQR(k + m) / SQR(k + m);
	// 
	// 	printf("%d\n", a);

	//int i = 0;
	//throw(1);
	//++i;
	//std::cout << i << std::endl;

	/*std::vector<AAA*> container;
	container.push_back(new AAA);
	container.push_back(new BBB);
	for_each(container.begin(), container.end(), DeleteObjectT());

	container.erase(std::remove(container.begin(), container.end(), new AAA), container.end());

	std::ifstream inputfile(_T("D:\\Work\\IndexingToolCheck\\校验修改.txt"));
	//inputfile.unsetf(std::ios::skipws);
	std::string str((std::istreambuf_iterator<char>(inputfile)), std::istreambuf_iterator<char>());

	std::vector<int> vecInt;

	vecInt.push_back(1);
	vecInt.push_back(2);
	vecInt.push_back(3);
	vecInt.push_back(99);
	vecInt.push_back(99);
	vecInt.push_back(99);
	vecInt.push_back(7);
	vecInt.push_back(8);
	vecInt.push_back(9);
	vecInt.push_back(99);

	vecInt.clear();
	char a = 'a';
	vecInt.erase(std::unique(vecInt.begin(), vecInt.end()), vecInt.end());
	//vecInt.erase(std::remove(vecInt.begin(), vecInt.end(), 99), vecInt.end());

	for (auto it = vecInt.begin(); it != vecInt.end(); ++it)
	{
		std::cout << *it << std::endl;
	}*/


	//std::regex_constants::syntax_option_type fl = std::regex::icase/* | std::regex::basic | std::regex::awk*/;
	//std::regex pattern("^([\\d]{1,5}) ([\\s\\S]*)$", fl);
	//std::string str("016 2.脊椎的曲度 像一只柔软的爬虫");
	//bool bRet = regex_match(str, pattern);
	//std::string sResult = regex_replace(str, pattern, "$2#$1"/*, std::regex_constants::match_flag_type::match_not_eol*/);
#pragma endregion

	std::string s("016 2.脊椎的曲度 像一只柔软 的爬虫");
	std::regex e("^([\\d]{1,5}) (([\\s]|[\\S])*)");   // matches words beginning by "sub"

	std::string result;
	std::regex_replace(std::back_inserter(result), s.begin(), s.end(), e, "$2#$1");
	std::cout << result << std::endl;

	std::cout << std::regex_replace(s, e, "$2 and $1"/*, std::regex_constants::format_no_copy*/);
	std::cout << std::endl;


// 	std::wifstream inputfile(_T("D:\\Work\\IndexingToolCheck\\校验修改.txt"));
// 	inputfile.unsetf(std::ios::skipws);
// 	std::wstring str((std::istream_iterator<wchar_t, wchar_t>(inputfile)), std::istream_iterator<wchar_t, wchar_t>());

	//for (int i = 0; i <= 100; ++i)
	//{
	//	if (0 == (i & 1))
	//	{
	//		std::cout << i << std::endl;
	//	}
	//}

	system("pause");
	return 0;
}

