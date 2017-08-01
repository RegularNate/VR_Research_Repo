#pragma once


#include <memory>
#include <iostream>

#include "Window.h"
#include "Renderer.h"


//VR Engine
namespace vre {

	class EngineMain {

	public:
		EngineMain(const EngineMain&) = delete;
		EngineMain(EngineMain&&) = delete;
		EngineMain& operator=(const EngineMain&) = delete;
		EngineMain& operator=(EngineMain&&) = delete;

		static EngineMain* GetInstance();

		bool Initialize(HINSTANCE* hInstance_, LPSTR* lpCmdLine_, int& nCmdShow_);
		void Run();
		void Update();
		void Render();

		void Input();


	private:
		EngineMain();
		~EngineMain();

		static std::unique_ptr<EngineMain> engineInstance;
		friend std::default_delete<EngineMain>;

		Window* mainWindow;

		Renderer* mainRenderer;


		//**RETURN TO THIS AT A LATER DATE WHEN YOU KNOW MORE**//
		//These are all pointers because I'm not sure if these are
		//references to objects held in a special memory address like
		//in OpenGL, or if they're objects that the computer has linked
		//to and modify with events??? 
		HINSTANCE* hInstance;
		LPSTR* lpCmdLine;
		int nCmdShow;

		bool isRunning;

		MSG eventMessage;
	};
}