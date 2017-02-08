#pragma once
#include "../containers/dynamic_array.h"

namespace SE3D
{
	class String
	{
	private:
		const char* m_String;
		uint32 m_Length;
		bool m_HasStringID;
		uint32 m_StringID;

	public:
		String();
		String(const String& string);
		String(const char* string);
		~String();

		inline const char* CString() const { return m_String; }
		inline uint32 Length() const { return m_Length; }
		char operator[](uint32 index) const { return m_String[index]; }

		friend String operator+(String left, const String& right);
		String& operator+=(const String& right);

		float ToFloat() const;
		int32 ToInt32() const;
		uint32 ToUInt32() const;
		int32 GetStringID();
		static float ToFloat(const char* string);
		static int32 ToInt32(const char* string);
		static uint32 ToUInt32(const char* string);

	private:
		//CRC32
		uint32 GenerateStringID() const;
	};
}
