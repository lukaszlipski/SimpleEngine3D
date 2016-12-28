#pragma once
//if Windows
#include <Windows.h>

#include "../utilities/types.h"

namespace SE3D {

	class Window {

	private:
		//if Windows
		WINDOWPLACEMENT m_WindowPreviousPosition = { sizeof(m_WindowPreviousPosition) };
		HWND m_WindowHandle;

		int32 m_Width;
		int32 m_Height;
		int16 m_VSync;
		bool m_Cursor;
		bool m_FullScreen;
		static bool m_IsRunning;
		Window() {}

	public:
		static Window& GetInstance()
		{
			static Window *instance = new Window();
			return *instance;
		}
		bool Startup(const char * title, int width, int height, HINSTANCE hInstance);
		void Shutdown();
		void SetCursor(bool cursor);
		void SetFullScreen(bool fs);
		void SetWindowSize(int width, int height);
		inline int32 GetSizeX() { return m_Width; }
		inline int32 GetSizeY() { return m_Height; }
		inline bool ShouldWindowClose() { return !m_IsRunning; }
		inline void CloseWindow() { m_IsRunning = false; }

		// if Windows
		inline HWND GetWindowHandle() { return m_WindowHandle; }

	private:
		friend LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	};

}