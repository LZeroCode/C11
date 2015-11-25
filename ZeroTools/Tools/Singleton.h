#pragma once

template<typename T>
class Singleton
{
public:
	template<typename... Args>
	static T* Instance(Args&&... args)
	{
		if (nullptr == m_pIntance)
		{
			m_pIntance = new T(std::forward<Args>(args)...);
		}

		return m_pIntance;
	}

	static void DestroyInstance()
	{
		if (nullptr != m_pIntance)
		{
			delete m_pIntance;
			m_pIntance = nullptr;
		}
	}
private:
	Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
	virtual ~Singleton()
	{
		if (nullptr != m_pIntance)
		{
			delete m_pIntance;
			m_pIntance = nullptr;
		}
	}

private:
	static T* m_pIntance;
};

template<typename T>
T* Singleton<T>::m_pIntance = nullptr;