#pragma once
#include <Windows.h>

class Win32_Timer {

private:

	LARGE_INTEGER m_Frequency;
	LARGE_INTEGER m_StartCounter;
	DOUBLE m_Timer;

public:

	Win32_Timer();

	void PlatformInit();
	void PlatformUpdate();

	inline void PlatformReset()
	{
		QueryPerformanceCounter(&m_StartCounter);
	}

	inline unsigned int PlatformTimeMS()
	{
		return (unsigned int)(m_Timer * 1000);
	}

	inline double PlatformTimeSEC()
	{
		return (double)(m_Timer);
	}

};