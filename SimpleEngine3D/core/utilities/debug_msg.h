#pragma once
#include "types.h"
#include <Windows.h>
#include <stdio.h>

namespace SE3D
{
#if _DEBUG
	inline void DebugOutputMSG(const char* msg, ...)
	{
		const uint32 MAX_CHARS = 1024;
		static char buffer[MAX_CHARS];

		va_list argList;
		va_start(argList, msg);
		vsnprintf(buffer, MAX_CHARS, msg, argList);
		va_end(argList);
		OutputDebugString(buffer);
	}
#else
	inline void DebugOutputMSG(const char* format, ...) {}
#endif
}