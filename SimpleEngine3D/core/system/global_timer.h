#pragma once
#include "../utilities/types.h"

namespace SE3D
{
	class GlobalTimer
	{
	private:
		int64 m_Frequency;
		int64 m_StartCounter;
		int64 m_CurrentCounter;
		double m_Timer;
		float m_DeltaTime;
		float m_Scale;
		bool m_Pause;

		GlobalTimer()
		{
		}

	public:
		static GlobalTimer& GetInstance()
		{
			static GlobalTimer* instance = new GlobalTimer();
			return *instance;
		}

		void Startup();
		void Shutown();
		void Update();
		void Reset();

		inline double TimeSEC() const { return m_Timer; }
		inline int64 GetCycles() const { return m_CurrentCounter; }
		inline float DeltaTime() const { return m_DeltaTime; }
		inline void SetPause(bool pause) { m_Pause = pause; }
		inline bool GetPause() const { return m_Pause; }
		inline void SetScale(float scale) { m_Scale = scale; }
		inline float GetScale() const { return m_Scale; }
	};
}
