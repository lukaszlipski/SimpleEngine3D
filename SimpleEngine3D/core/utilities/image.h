#pragma once
#include "../system/file.h"
#include "types.h"

namespace SE3D {

	class Image {

	private:
		int32 m_Width;
		int32 m_Height;
		void *m_Pixels;
		FILE m_File;

	public:
		~Image();
		Image(const char * filePath);

		inline int32 getWidth() { return m_Width; }
		inline int32 getHeight() { return m_Height; }
		inline void* getPixels() { return m_Pixels; }
		void Delete();

	private:
		void LoadBMP();

	};

}