#include "Essentials\EngineMain.h"

#include <windows.h>


int WINAPI WinMain(HINSTANCE hInstance, 
					HINSTANCE hPrevInstance, 
					LPSTR lpCmdLine, 
					int nCmdShow) {

	
	if (!vre::EngineMain::GetInstance()->Initialize(&hInstance, &lpCmdLine, nCmdShow)) {
		std::cout << "Engine Failed to Initialize. . ." << std::endl;
		return 0;
	}


	vre::EngineMain::GetInstance()->Run();

	return 0;
}