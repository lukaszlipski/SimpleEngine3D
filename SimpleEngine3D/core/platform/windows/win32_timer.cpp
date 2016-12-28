//#include "win32_timer.h"
#include "../system/timer.h"
#include <Windows.h>

namespace SE3D
{
	Timer::Timer()
	{
		Init();
	}

	void Timer::Init()
	{
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);
		m_Frequency = freq.QuadPart;
		Reset();
	}

	void Timer::Update()
	{
		LARGE_INTEGER CurrentCounter;
		QueryPerformanceCounter(&CurrentCounter);

		m_Timer = static_cast<DOUBLE>(CurrentCounter.QuadPart - m_StartCounter) / static_cast<DOUBLE>(m_Frequency);
	}

	void Timer::Reset()
	{
		LARGE_INTEGER start;
		QueryPerformanceCounter(&start);
		m_StartCounter = start.QuadPart;
	}

	double Timer::TimeMS() const
	{
		return m_Timer * 1024;
	}

	double Timer::TimeSEC() const
	{
		return m_Timer;
	}
}
