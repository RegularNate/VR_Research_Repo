#pragma once


#include <windows.h>
#include <windowsx.h>

#include <string>


//VR Engine
namespace vre {

	class Window {

	public:
		Window();
		~Window();

		bool Initialize(HINSTANCE* hInstance_, int& nCmdShow_, short width_, short height_, std::string name_, std::string title_);

		HWND GetWindowHandle();

		
	private:
		HWND windowHandle;
		WNDCLASSEX windowInformation;

		static LRESULT CALLBACK WindowProc(HWND windowInstance_, UINT message_, WPARAM wParam_, LPARAM lParam_);
	};
}