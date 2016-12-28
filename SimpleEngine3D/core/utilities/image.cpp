#include "image.h"

namespace SE3D
{
	Image::~Image()
	{
		Delete();
	}

	Image::Image(const char* filePath)
	{
		m_File = File::GetInstance().ReadSync(filePath);
		if (m_File.Size == 0) { File::GetInstance().Delete(m_File); }

		int16 Signature = *static_cast<int16*>(m_File.Content);
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
		m_Width = *reinterpret_cast<int32*>(static_cast<int8*>(m_File.Content) + 18);
		m_Height = *reinterpret_cast<int32*>(static_cast<int8*>(m_File.Content) + 22);

		int8 offset = *(static_cast<int8*>(m_File.Content) + 10);
		m_Pixels = static_cast<int8*>(m_File.Content) + offset;
	}

	void Image::Delete() const
	{
		if (m_File.Content != nullptr)
			File::GetInstance().Delete(m_File);
	}
}
