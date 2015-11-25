#pragma once

template<typename Func>
class SimpleEvent
{
public:
	SimpleEvent()
	{}
	~SimpleEvent()
	{
		m_id_func.clear();
	}
protected:
	SimpleEvent(const SimpleEvent&) = delete;
	SimpleEvent& operator= (const SimpleEvent&) = delete;

public:
	int Connect(const Func& func)
	{
		static int id = 0;
		++id;
		m_id_func.emplace(id, func);

		return id;
	}
	
	bool DisConnect(int id)
	{
		auto it = m_id_func.find(id);
		if (it != m_id_func.end())
		{
			m_id_func.erase(it);

			return true;
		}

		return false;
	}

	template<typename... Args>
	void Notify(Args&&... args)
	{
		for (auto it = m_id_func.begin(); it != m_id_func.end(); ++it)
		{
			it->second(std::forward<Args>(args)...);
		}
	}
private:
	std::map<int, Func> m_id_func;
};
