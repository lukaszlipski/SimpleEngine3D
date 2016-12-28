#pragma once
#include "../utilities/types.h"

#define SE3D_KEYBOARD_KEYS 1024
#define SE3D_MOUSE_BUTTONS 3

namespace SE3D {

	class Input {

	private:
		bool m_Keyboard[SE3D_KEYBOARD_KEYS];
		bool m_Mouse[SE3D_MOUSE_BUTTONS];
		int16 m_MousePositionX;
		int16 m_MousePositionY;

		Input() {}
	public:
		static Input& GetInstance()
		{
			static Input *instance = new Input();
			return *instance;
		}

		bool Startup();
		void Shutown();
		void Update();
		bool GetKey(const char key);
		/**
		Left mouse button - 0
		Right mouse button - 1
		Middle mouse button - 2
		*/
		bool GetMouseButton(byte mouse);

		int16 GetMousePositionX();
		int16 GetMousePositionY();

	};

}