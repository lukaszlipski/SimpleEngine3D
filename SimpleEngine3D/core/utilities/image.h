#pragma once
#include "../system/file.h"
#include <cstdint>

namespace SE3D {

	class Image {

	private:
		int32_t m_Width;
		int32_t m_Height;
		void *m_Pixels;
		FILE m_File;

	public:
		~Image();
		Image(const char * filePath);

		inline int32_t getWidth() { return m_Width; }
		inline int32_t getHeight() { return m_Height; }
		inline void* getPixels() { return m_Pixels; }
		void Delete();

	private:
		void LoadBMP();

	};

}