#pragma once
#include "../utilities/types.h"

namespace SE3D
{
	class Timer
	{
	private:
		int64 m_Frequency;
		int64 m_StartCounter;
		double m_Timer;

	public:
		Timer();
		void Init();
		void Update();
		void Reset();
		double TimeMS() const;
		double TimeSEC() const;
	};
}
