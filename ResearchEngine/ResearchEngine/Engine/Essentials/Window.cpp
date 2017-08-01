#include "Window.h"


using namespace vre;

Window::Window() : windowHandle(HWND()), windowInformation(WNDCLASSEX()) {

}

Window::~Window() {

}


bool Window::Initialize(HINSTANCE* hInstance_, int& nCmdShow_, short width_, short height_, std::string name_, std::string title_) {

	//Clear out the window Info
	ZeroMemory(&windowInformation, sizeof(WNDCLASSEX));
	

	//--Populate Window Information--//
	//Size of the structure
	windowInformation.cbSize = sizeof(WNDCLASSEX);
	//Sets the window to redraw if the window is moved or resized in the X or Y directions
	windowInformation.style = CS_HREDRAW | CS_VREDRAW;
	//pointer to the window's event system
	windowInformation.lpfnWndProc = (WNDPROC)WindowProc;
	//Handle to the Windows(OS) Instance of this application
	windowInformation.hInstance = *hInstance_;
	//Handle to the cursor for use in this application
	windowInformation.hCursor = LoadCursor(NULL, IDC_ARROW);
	//Handle to the background brush, which fills the window
	windowInformation.hbrBackground = (HBRUSH)COLOR_WINDOW;
	//Registers the class name for this window, which needs to be a predefined name
	windowInformation.lpszClassName = name_.c_str();


	//--Quick Window Position Math--//
	RECT windowSize;
	RECT clientSize = {0, 0, width_, height_};

	GetWindowRect(GetDesktopWindow(), &windowSize);

	clientSize.left = (windowSize.right / 2) - (width_ / 2);
	clientSize.top = (windowSize.bottom / 2) - (height_ / 2);
	
	AdjustWindowRect(&clientSize, WS_OVERLAPPEDWINDOW, FALSE);

	//--Register the Window and then Create it--//
	RegisterClassEx(&windowInformation);

	//Create window
	windowHandle = CreateWindowEx(NULL,					//Extended Windows Style
									name_.c_str(),		//Class name for the Register
									title_.c_str(),		//Title at the top of the window
									WS_OVERLAPPEDWINDOW,	//Window style
									clientSize.left,					//x
									clientSize.top,					//y
									clientSize.right,					//Width
									clientSize.bottom,				//Height
									NULL,					//Handle to a parent window
									NULL,					//Handle to a menu window
									*hInstance_,				//Handle to application instance
									NULL);					//Pointer to a value to be passed in

	ShowWindow(windowHandle, nCmdShow_);

	return true;
}


LRESULT CALLBACK Window::WindowProc(HWND windowInstance_, UINT message_, WPARAM wParam_, LPARAM lParam_) {

	switch (message_) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		break;
	}

	return DefWindowProc(windowInstance_, message_, wParam_, lParam_);
}


HWND Window::GetWindowHandle() {

	return windowHandle;
}