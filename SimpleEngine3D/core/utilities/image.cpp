#include "image.h"

namespace SE3D {

	IMAGE Image::LoadBMP(const char * filePath)
	{
		IMAGE img;

		img.File = File::GetInstance().ReadSync(filePath);

		if (img.File.Size == 0)
		{
			File::GetInstance().Delete(img.File);
			return IMAGE{ -1,-1,nullptr,FILE{} };
		}

		int16_t Signature = *((int16_t*)img.File.Content);
		if (Signature != 0x4d42)
		{
			File::GetInstance().Delete(img.File);
			return IMAGE{ -1,-1,nullptr,FILE{} };
		}

		img.Width = *( (int32_t*)( (int8_t*)img.File.Content + 18 ) );
		img.Height = *( (int32_t*)( (int8_t*)img.File.Content + 22 ) );

		int8_t offset = *((int8_t*)img.File.Content + 10);
		img.Pixels = (int8_t*)img.File.Content + offset;

		return img;

	}

	void Image::Delete(IMAGE img)
	{
		if (img.File.Content != nullptr)
			File::GetInstance().Delete(img.File);
	}

}