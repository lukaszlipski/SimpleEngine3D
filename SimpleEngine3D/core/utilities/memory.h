#pragma once
#include "types.h"

#define OffsetOf(structure, member) (reinterpret_cast<int64>(&static_cast<structure*>(nullptr)->member))

namespace SE3D
{

	inline void CopyMem(void* dest, const void* src, uint32 size)
	{
		uint32 loops = static_cast<uint32>(size / sizeof(uint32));
		for (uint32 i = 0; i < loops; i++)
		{
			static_cast<uint32*>(dest)[i] = static_cast<const uint32*>(src)[i];
		}
		for (uint32 i = 0; i <= size % sizeof(uint32); i++)
		{
			static_cast<uint8*>(dest)[loops * 4 + i] = static_cast<const uint8*>(src)[loops * 4 + i];
		}
	}

}
