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
		float m_LastFrameTime;
		float m_DeltaTime;

		Timer()
		{
		}

	public:
		static Timer& GetInstance()
		{
			static Timer* instance = new Timer();
			return *instance;
		}

		void Startup();
		void Shutown();
		void Update();
		void Reset();
		double TimeMS() const;
		double TimeSEC() const;

		inline float DeltaTime() const { return m_DeltaTime; }
	};
}
