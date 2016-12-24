#pragma once
#include "../utilities/types.h"
#include "../utilities/assertion.h"

namespace SE3D {

	template <class T>
	class DynamicArray {

		uint32 m_Size;
		uint32 m_Capacity;
		T* m_Data;

	public:

		DynamicArray() {
			m_Size = 0;
			m_Capacity = 0;
			m_Data = nullptr;
		}

		~DynamicArray() { delete[] m_Data; }

		void Push(const T& element)
		{
			if (m_Size != m_Capacity)
			{
				m_Data[m_Size++] = element;
				return;
			}

			uint32 newCap;
			if (m_Capacity)	{ newCap = ((m_Capacity * 3)/2) + 1; } else { newCap = 1; }
			T* newData = new T[newCap];
			for (uint32 i = 0; i < m_Size; i++)
			{
				newData[i] = m_Data[i];
			}
			
			delete[] m_Data;
			m_Data = newData;
			m_Capacity = newCap;
			m_Data[m_Size++] = element;
		}

		void Insert(uint32 index, const T& element)
		{
			if (index < 0 || index > m_Size) { return; }
			if (m_Size != m_Capacity)
			{
				for (uint32 i = m_Size; i > index; i--)
				{
					m_Data[i] = m_Data[i-1];
				}
				m_Data[index] = element;
				m_Size += 1;
				return;
			}
			if (m_Size == 0)
			{
				Push(element);
				return;
			}

			uint32 newCap = ((m_Capacity * 3) / 2) + 1;
			T* newData = new T[newCap];

			for (uint32 i = 0; i < index; i++)
			{
				newData[i] = m_Data[i];
			}
			newData[index] = element;
			for (uint32 i = index; i < m_Size; i++)
			{
				newData[i+1] = m_Data[i];
			}

			m_Size += 1;
			delete[] m_Data;
			m_Data = newData;
			m_Capacity = newCap;

		}

		void Remove(uint32 index)
		{
			if (index < 0 || index >= m_Size) { return; }
			m_Size -= 1;
			if (m_Size > m_Capacity / 2)
			{
				for (uint32 i = index; i < m_Size; i++)
				{
					m_Data[i] = m_Data[i + 1];
				}
				return;
			}

			m_Capacity = ((m_Size * 3) / 2) + 1;
			T* newData = new T[m_Capacity];

			for (uint32 i = 0; i < index; i++)
			{
				newData[i] = m_Data[i];
			}

			for (uint32 i = index; i < m_Size; i++)
			{
				newData[i] = m_Data[i + 1];
			}

			delete[] m_Data;
			m_Data = newData;
		}

		inline uint32 Size() { return m_Size; }

		T& operator[](uint32 index) const { return m_Data[index]; }

	};
	
}