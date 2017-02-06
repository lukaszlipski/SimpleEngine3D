//#include "win32_timer.h"
#include "../system/timer.h"
#include <Windows.h>

namespace SE3D
{
	void Timer::Startup()
	{
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);
		m_Frequency = freq.QuadPart;
		m_LastFrameTime = 0.0f;
		Reset();
	}

	void Timer::Shutown()
	{
	}

	void Timer::Update()
	{
		LARGE_INTEGER CurrentCounter;
		QueryPerformanceCounter(&CurrentCounter);

		m_Timer = static_cast<DOUBLE>(CurrentCounter.QuadPart - m_StartCounter) / static_cast<DOUBLE>(m_Frequency);

		m_DeltaTime = m_Timer - m_LastFrameTime;
		m_LastFrameTime = m_Timer;
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
