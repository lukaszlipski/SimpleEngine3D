#pragma once
//if Windows
#include <Windows.h>

#include "../utilities/types.h"

namespace SE3D
{
	class Window
	{
	private:
		//if Windows
		WINDOWPLACEMENT m_WindowPreviousPosition = {sizeof(m_WindowPreviousPosition)};
		HWND m_WindowHandle;

		int32 m_Width;
		int32 m_Height;
		bool m_Cursor;
		bool m_FullScreen;
		static bool m_IsRunning;
		const char* m_Title;

		Window()
		{
		}

	public:
		static Window& GetInstance()
		{
			static Window* instance = new Window();
			return *instance;
		}

		bool Startup();
		void Shutdown() const;
		void SetCursor(bool cursor);
		bool GetCursor() const { return m_Cursor; }
		void SetFullScreen(bool fs);
		bool GetFullScreen() const { return m_FullScreen; }
		void SetSize(int width, int height);
		inline int32 GetSizeX() const { return m_Width; }
		inline int32 GetSizeY() const { return m_Height; }
		void SetTitle(const char* title);
		inline const char* GetTitle() const { return m_Title; }
		inline bool ShouldWindowClose() const { return !m_IsRunning; }
		inline void CloseWindow() const { m_IsRunning = false; }

		// if Windows
		inline HWND GetWindowHandle() const { return m_WindowHandle; }

	private:
		friend LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}
