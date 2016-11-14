#pragma once
#include <Windows.h>

class Win32_Time {

private:

	LARGE_INTEGER m_Frequency;
	LARGE_INTEGER m_StartCounter;
	DOUBLE m_Timer;

public:

	Win32_Time();

	void Init();
	void Update();

	inline void Reset()
	{
		QueryPerformanceCounter(&m_StartCounter);
	}

	inline unsigned int TimeMS()
	{
		return (unsigned int)(m_Timer * 1000);
	}

	inline double TimeSEC()
	{
		return (double)(m_Timer);
	}

};