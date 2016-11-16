#pragma once
#include "../system/file.h"
#include <cstdint>

namespace SE3D {

	struct IMAGE {
		int32_t Width;
		int32_t Height;
		void *Pixels;
		FILE File;
	};

	class Image {

	private:
		IMAGE m_Image;
	public:
		static IMAGE LoadBMP(const char* filePath);
		static void Delete(IMAGE img);

	};

}