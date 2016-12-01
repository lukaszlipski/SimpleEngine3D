#pragma once
#include <Windows.h>

#include "../utilities/types.h"

namespace SE3D {

	class Win32_Input {

	private:
		bool m_Keyboard[1024];
		bool m_Mouse[3];
		int16 m_MousePositionX;
		int16 m_MousePositionY;

	public:
		void ProcessInput(MSG Message);
		bool getKey(const char key);
		bool getMouseButton(byte mouse);

		int16 getMousePositionX();
		int16 getMousePositionY();

	};
}