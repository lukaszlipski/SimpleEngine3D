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

		int16 Signature = reinterpret_cast<int16*>(m_File.Content)[0];
		if (Signature == 0x4d42)
		{
			int8 version = static_cast<int8*>(m_File.Content)[2];
			if (version == '8')
			{
				LoadBMP8();
				m_Format = RGBA;
			}
			else
			{
				LoadBMP();
				m_Format = RGB;
			}
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

		if (File::GetInstance().IsLittleEndian())
		{
			for (uint32 i = 0; i < m_Width * m_Height * 3; i = i + 3)
			{
				int8 tmp = static_cast<int8*>(m_Pixels)[i];
				static_cast<int8*>(m_Pixels)[i] = static_cast<int8*>(m_Pixels)[i + 2];
				static_cast<int8*>(m_Pixels)[i + 2] = tmp;
			}
		}
	}

	void Image::LoadBMP8()
	{
		m_Width = *reinterpret_cast<int32*>(static_cast<int8*>(m_File.Content) + 18);
		m_Height = *reinterpret_cast<int32*>(static_cast<int8*>(m_File.Content) + 22);

		int8 offset = *(static_cast<int8*>(m_File.Content) + 10);
		m_Pixels = static_cast<int8*>(m_File.Content) + offset;

		if (File::GetInstance().IsLittleEndian())
		{
			for (uint32 i = 0; i < m_Width * m_Height * 4; i = i + 4)
			{
				int8 tmp = static_cast<int8*>(m_Pixels)[i];
				static_cast<int8*>(m_Pixels)[i] = static_cast<int8*>(m_Pixels)[i + 2];
				static_cast<int8*>(m_Pixels)[i + 2] = tmp;
			}
		}
	}

	void Image::Delete() const
	{
		if (m_File.Content != nullptr)
			File::GetInstance().Delete(m_File);
	}
}
