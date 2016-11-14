#include "win32_time.h"

Win32_Time::Win32_Time()
{
	QueryPerformanceFrequency(&m_Frequency);
}

void Win32_Time::Init()
{
	QueryPerformanceFrequency(&m_Frequency);
	Reset();
}

void Win32_Time::Update()
{
	LARGE_INTEGER CurrentCounter;
	QueryPerformanceCounter(&CurrentCounter);
	
	m_Timer = (DOUBLE)(CurrentCounter.QuadPart - m_StartCounter.QuadPart) / (DOUBLE)m_Frequency.QuadPart;
}
