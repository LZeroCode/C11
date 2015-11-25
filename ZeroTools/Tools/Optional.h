#pragma once
#include <type_traits>


//功能：初始化的概念
template<typename T>
class Optional
{
	//定义内存对齐的缓冲区类型
	using data_t = typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type;
	//typedef typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type data_t;
public:
	Optional(){};
	
	Optional(const T& v)
	{
		Create(v);
	}

	Optional(const Optional& other)
	{
		if (other.IsInit())
		{
			Copy(other.m_data);
			m_bInit = true;
		}
		else
		{
			assert(false);
		}
	}

	~Optional()
	{
		Destroy();
	}

public:
	bool IsInit() const
	{
		return m_bInit;
	}

	operator bool() const
	{
		return IsInit();
	}

	const T& operator* () const
	{
		if (IsInit())
		{
			return *(T*)(&m_data);
		}
		
		throw std::logic_error("is not init");
	}

	template<class... Args>
	void Emplace(Args&&... args)
	{
		Destroy();
		Create(std::forward<Args>(args)...);
	}

private:
	template<class... Args>
	void Create(Args&&... args)
	{
		new (&m_data) T(std::forward<Args>(args)...);//完美转发
		m_bInit = true;
	}

	void Destroy()
	{
		if (IsInit())
		{
			((T*)(&m_data))->~T();
			m_bInit = false;
		}
	}

	void Copy(const T& v)
	{
		Destroy();
		new (&m_data) T(v);
	}

private:
	bool	m_bInit = false;//是否初始化
	data_t	m_data;//内存对齐缓冲区
};