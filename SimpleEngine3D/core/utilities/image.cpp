#include "image.h"

namespace SE3D {

	Image::~Image()
	{
		Delete();
	}

	Image::Image(const char * filePath)
	{
		m_File = File::GetInstance().ReadSync(filePath);
		if (m_File.Size == 0) { File::GetInstance().Delete(m_File); }

		int16 Signature = *((int16*)m_File.Content);
		if (Signature == 0x4d42) 
		{
			LoadBMP();
		}
		else
		{ 
			File::GetInstance().Delete(m_File); 
		}

	}

	void Image::LoadBMP()
	{

		m_Width = *( (int32*)( (int8*)m_File.Content + 18 ) );
		m_Height = *( (int32*)( (int8*)m_File.Content + 22 ) );

		int8 offset = *((int8*)m_File.Content + 10);
		m_Pixels = (int8*)m_File.Content + offset;

	}

	void Image::Delete()
	{
		if (m_File.Content != nullptr)
			File::GetInstance().Delete(m_File);
	}

}