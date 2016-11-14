#include "win32_timer.h"

Win32_Time::Win32_Time()
{
	QueryPerformanceFrequency(&m_Frequency);
}

void Win32_Time::PlatformInit()
{
	QueryPerformanceFrequency(&m_Frequency);
	PlatformReset();
}

void Win32_Time::PlatformUpdate()
{
	LARGE_INTEGER CurrentCounter;
	QueryPerformanceCounter(&CurrentCounter);
	
	m_Timer = (DOUBLE)(CurrentCounter.QuadPart - m_StartCounter.QuadPart) / (DOUBLE)m_Frequency.QuadPart;
}
