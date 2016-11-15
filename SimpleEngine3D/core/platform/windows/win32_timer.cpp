#include "win32_timer.h"

Win32_Timer::Win32_Timer()
{
	QueryPerformanceFrequency(&m_Frequency);
}

void Win32_Timer::PlatformInit()
{
	QueryPerformanceFrequency(&m_Frequency);
	PlatformReset();
}

void Win32_Timer::PlatformUpdate()
{
	LARGE_INTEGER CurrentCounter;
	QueryPerformanceCounter(&CurrentCounter);
	
	m_Timer = (DOUBLE)(CurrentCounter.QuadPart - m_StartCounter.QuadPart) / (DOUBLE)m_Frequency.QuadPart;
}
