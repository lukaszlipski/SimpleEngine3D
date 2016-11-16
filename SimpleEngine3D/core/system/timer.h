#pragma once
//if Windows
#include <Windows.h>

class Timer {

private:
	long long m_Frequency;
	long long m_StartCounter;
	double m_Timer;

public:
	Timer();
	void Init();
	void Update();
	void Reset();
	double TimeMS();
	double TimeSEC();

};