#pragma once

#include "dll_ZeroTools.h"
#include <chrono>
class ZeroTool Timer
{
public:
	Timer()
		: m_begin(std::chrono::high_resolution_clock::now())
	{
	}

	~Timer()
	{
	}

	void Reset()
	{
		m_begin = std::chrono::high_resolution_clock::now();
	}

	template<typename Duration = std::chrono::milliseconds>
	long elapsed() const
	{
		return (std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now() - m_begin)).count();
	}

	//√Î
	long elapsed_sec() const
	{
		return elapsed<std::chrono::seconds>();
	}

	//∑÷÷”
	long elapsed_minu() const
	{
		return elapsed<std::chrono::minutes>();
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock>		m_begin;
};
