#include "string.h"

namespace SE3D
{
	String::String()
		: m_Length(0), m_HasStringID(false)
	{
		m_String = nullptr;
	}

	String::String(const String& string)
		: m_HasStringID(string.m_HasStringID), m_StringID(string.m_StringID)
	{
		m_Length = string.Length();
		char* newString = new char[m_Length + 1];

		for (uint32 i = 0; i <= m_Length; i++)
		{
			newString[i] = string[i];
		}
		m_String = newString;
	}

	String::String(const char* string)
		: m_HasStringID(false)
	{
		m_Length = 0;
		const char* tmp = string;
		while (*tmp++ != '\0')
		{
			m_Length++;
		}

		char* newString = new char[m_Length + 1];

		for (uint32 i = 0; i <= m_Length; i++)
		{
			newString[i] = string[i];
		}
		m_String = newString;
	}

	String::~String()
	{
		if (m_String != nullptr)
			delete[] m_String;
	}


	String operator+(String left, const String& right)
	{
		uint32 newLength = left.Length() + right.Length();
		char* newStringPtr = new char[newLength + 1];

		for (uint32 i = 0; i < left.Length(); i++)
		{
			newStringPtr[i] = left[i];
		}

		for (uint32 i = 0; i <= right.Length(); i++)
		{
			newStringPtr[i + left.Length()] = right[i];
		}
		return String(newStringPtr);
	}

	String& String::operator+=(const String& right)
	{
		uint32 newLength = Length() + right.Length();
		char* newStringPtr = new char[newLength + 1];

		for (uint32 i = 0; i < Length(); i++)
		{
			newStringPtr[i] = (*this)[i];
		}

		for (uint32 i = 0; i <= right.Length(); i++)
		{
			newStringPtr[i + Length()] = right[i];
		}
		delete[] m_String;
		m_String = newStringPtr;
		m_Length = newLength;
		m_HasStringID = false;
		return *this;
	}

	float String::ToFloat() const
	{
		return String::ToFloat(this->CString());
	}

	int32 String::ToInt32() const
	{
		return String::ToInt32(this->CString());
	}

	uint32 String::ToUInt32() const
	{
		return String::ToUInt32(this->CString());
	}

	uint32 String::GetStringID()
	{
		if (m_HasStringID)
			return m_StringID;

		m_HasStringID = true;
		return m_StringID = GenerateStringID();
	}

	float String::ToFloat(const char* string)
	{
		if (!string) { return 0; }
		const char* tmp = string;
		float intPart = 0;
		float fracPart = 0;
		float sign = 1;
		uint32 divFrac = 1;
		bool inFraction = false;

		if (tmp[0] == '-')
		{
			sign = -1;
			tmp++;
		}
		else if (tmp[0] == '+') { tmp++; }

		while (*tmp != '\0')
		{
			if (*tmp >= '0' && *tmp <= '9')
			{
				if (!inFraction) { intPart = intPart * 10 + (*tmp - '0'); }
				else
				{
					fracPart = fracPart * 10 + (*tmp - '0');
					divFrac *= 10;
				};
			}
			else if (*tmp == '.' || *tmp == ',')
			{
				if (!inFraction) { inFraction = true; }
				else { return sign * (intPart + fracPart / divFrac); }
			}
			else
			{
				return sign * (intPart + fracPart / divFrac);
			}
			tmp++;
		}
		return sign * (intPart + fracPart / divFrac);
	}

	int32 String::ToInt32(const char* string)
	{
		if (!string) { return 0; }
		const char* tmp = string;
		int32 intPart = 0;
		int32 sign = 1;

		if (tmp[0] == '-')
		{
			sign = -1;
			tmp++;
		}
		else if (tmp[0] == '+') { tmp++; }

		while (*tmp != '\0')
		{
			if (*tmp >= '0' && *tmp <= '9') { intPart = intPart * 10 + (*tmp - '0'); }
			else { return sign * intPart; }
			tmp++;
		}

		return sign * intPart;
	}

	uint32 String::ToUInt32(const char* string)
	{
		if (!string) { return 0; }
		const char* tmp = string;
		uint32 intPart = 0;

		if (tmp[0] == '-') { tmp++; }
		else if (tmp[0] == '+') { tmp++; }

		while (*tmp != '\0')
		{
			if (*tmp >= '0' && *tmp <= '9') { intPart = intPart * 10 + (*tmp - '0'); }
			else { return intPart; }
			tmp++;
		}

		return intPart;
	}

	uint32 String::GenerateStringID() const
	{
		uint32 stringID = 0;
		for (uint32 i = 0; i < m_Length; i++)
		{
			stringID ^= (m_String[i] << 24);
			for (uint8 j = 8; j > 0; j--)
			{
				if (stringID & (1 << 31))
				{
					stringID = (stringID << 1) ^ 0x04C11DB7;
				}
				else
				{
					stringID = stringID << 1;
				}
			}
		}
		return stringID;
	}
}
