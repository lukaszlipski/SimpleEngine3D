//#include "win32_timer.h"
#include "../system/global_timer.h"
#include <Windows.h>

namespace SE3D
{
	void GlobalTimer::Startup()
	{
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);
		m_Frequency = freq.QuadPart;
		m_StartCounter = 0;
		m_CurrentCounter = 0;
		m_DeltaTime = 0;
		m_Timer = 0;
		m_Scale = 1.0f;
		m_Pause = false;
		Reset();
	}

	void GlobalTimer::Shutown()
	{
	}

	void GlobalTimer::Update()
	{
		if (!m_Pause)
		{
			LARGE_INTEGER CurrentCounter;
			QueryPerformanceCounter(&CurrentCounter);

			int64 lastFrameCounter = m_CurrentCounter;
			m_CurrentCounter = CurrentCounter.QuadPart - m_StartCounter;
			m_DeltaTime = static_cast<float>(static_cast<double>(m_CurrentCounter - lastFrameCounter) / static_cast<double>(m_Frequency)) * m_Scale;
			m_Timer += m_DeltaTime;
		}
	}

	void GlobalTimer::Reset()
	{
		LARGE_INTEGER start;
		QueryPerformanceCounter(&start);
		m_StartCounter = start.QuadPart;
	}
}
