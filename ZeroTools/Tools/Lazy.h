#pragma once
#include <functional>


template <typename T>
class Lazy
{
public:
	Lazy(){}

	//可变参数模板可以表示0个参数
	template<typename Func, typename... Args>
	Lazy(const Func& func, Args&&... args)
	{
		m_func = [&func, &args...](){
			return func(std::forward<Args>(args)...);
		};
	}

	~Lazy(){}

public:
	const T& Value()
	{
		if (!m_value.IsInit())
		{
			m_value = m_func();
		}

		return *m_value;
	}

	bool IsInit() const
	{
		return m_value.IsInit();
	}

private:
	std::function<T()>	m_func; //用作延迟初始化
	Optional<T>			m_value;
};


template<typename Func, typename... Args>
Lazy<typename std::result_of<Func(Args...)>::type> lazy(Func&& func, Args&&...args)
{
	return Lazy<typename std::result_of<Func(Args...)>::type>(std::forward<Func>(func), std::forward<Args>(args)...);
}