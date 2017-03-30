#include "image.h"

namespace SE3D
{
	Image::~Image()
	{
		Delete();
	}

	Image::Image(const char* filePath, bool srgb)
	{
		m_File = File::GetInstance().ReadSync(filePath);
		if (m_File.Size == 0) { File::GetInstance().Delete(m_File); }

		int16 Signature = reinterpret_cast<int16*>(m_File.Content)[0];
		if (Signature == 0x4d42)
		{
			int8 version = static_cast<int8*>(m_File.Content)[2];
			if (version == '8')
			{
				if (srgb)
					m_ColorSpaceFormat = InternalFormat::sRGBA;
				else
					m_ColorSpaceFormat = InternalFormat::RGBA;

				m_Format = ImageFormat::RGBA;
				m_Bytes = 4;
			}
			else
			{
				if (srgb)
					m_ColorSpaceFormat = InternalFormat::sRGB;
				else
					m_ColorSpaceFormat = InternalFormat::RGB;

				m_Format = ImageFormat::RGB;
				m_Bytes = 3;
			}
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

		if (File::GetInstance().IsLittleEndian())
		{
			for (uint32 i = 0; i < m_Width * m_Height * m_Bytes; i = i + m_Bytes)
			{
				int8 tmp = static_cast<int8*>(m_Pixels)[i];
				static_cast<int8*>(m_Pixels)[i] = static_cast<int8*>(m_Pixels)[i + 2];
				static_cast<int8*>(m_Pixels)[i + 2] = tmp;
			}
			//FlipX();
		}
	}

	void Image::FlipX() const
	{
		for (int32 y = 0; y < m_Height; y++)
		{
			for (int32 x = 0; x < static_cast<int32>(m_Width / 2); x++)
			{
				for (int32 i = 0; i < m_Bytes; i++)
				{
					int8 tmp = static_cast<int8*>(m_Pixels)[(x + y * m_Width) * m_Bytes + i];
					static_cast<int8*>(m_Pixels)[(x + y * m_Width) * m_Bytes + i] = static_cast<int8*>(m_Pixels)[(m_Width - 1 - x + y * m_Width) * m_Bytes + i];
					static_cast<int8*>(m_Pixels)[(m_Width - 1 - x + y * m_Width) * m_Bytes + i] = tmp;
				}
			}
		}
	}

	void Image::Delete() const
	{
		if (m_File.Content != nullptr)
			File::GetInstance().Delete(m_File);
	}
}
