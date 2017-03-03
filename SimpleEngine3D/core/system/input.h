#pragma once
#include "../utilities/types.h"
#include "../math/vector2d.h"

// if Windows
#include "../platform/windows/win32_keys_defines.h"

#define SE3D_KEYBOARD_KEYS 1024
#define SE3D_MOUSE_BUTTONS 3

namespace SE3D
{
	class Input
	{
	private:
		bool m_Keyboard[SE3D_KEYBOARD_KEYS];
		bool m_Mouse[SE3D_MOUSE_BUTTONS];
		uint32 m_MousePositionX;
		uint32 m_MousePositionY;

		Input()
		{
		}

	public:
		static Input& GetInstance()
		{
			static Input* instance = new Input();
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

		inline uint32 GetMousePositionX() const { return m_MousePositionX; }
		inline uint32 GetMousePositionY() const { return m_MousePositionY; }
		inline Vector2D GetMousePosition() const { return Vector2D(static_cast<float>(m_MousePositionX), static_cast<float>(m_MousePositionY)); }

		void SetMousePosition(uint32 x, uint32 y) const;
		void SetMousePosition(const Vector2D& position) const;
	};
}
