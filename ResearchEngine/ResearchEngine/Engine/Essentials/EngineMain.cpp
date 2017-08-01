#include "EngineMain.h"


using namespace vre;


std::unique_ptr<EngineMain> EngineMain::engineInstance(nullptr);


EngineMain::EngineMain() : isRunning(false), eventMessage({ 0 }), mainWindow(nullptr), mainRenderer(nullptr), hInstance(nullptr), lpCmdLine(nullptr), nCmdShow(0) {


}


EngineMain::~EngineMain() {

	delete mainWindow;
	mainWindow = nullptr;

	delete mainRenderer;
	mainRenderer = nullptr;

	//They run out of scope when the application dies, so don't delete them
	hInstance = nullptr;
	lpCmdLine = nullptr;
}


EngineMain* EngineMain::GetInstance() {

	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new EngineMain);
	}

	return engineInstance.get();
}


bool EngineMain::Initialize(HINSTANCE* hInstance_, LPSTR* lpCmdLine_, int& nCmdShow_) {

	hInstance = hInstance_;
	lpCmdLine = lpCmdLine_;
	nCmdShow = nCmdShow_;

	mainWindow = new Window();
	mainRenderer = new Renderer();


	//If either the Window or the Render do not initialize then we'll need to return false so that the game quits out now
	if (!mainWindow->Initialize(hInstance, nCmdShow, 600, 400, "MainWindowClass", "DX11 Test Demo")) {
		std::cout << "Window Failed to Initialize. . ." << std::endl;
		return false;
	}
	
	if (!mainRenderer->Initialize(mainWindow->GetWindowHandle())) {
		std::cout << "Renderer Failed to Initialize. . ." << std::endl;
		return false;
	}


	return true;
}


void EngineMain::Run() {


	isRunning = true;

	while (isRunning) {
		Input();

		Update();

		Render();
	}
}


void EngineMain::Update() {

}


void EngineMain::Render() {

	mainRenderer->Render();
}


void EngineMain::Input() {

	
	if (PeekMessage(&eventMessage, NULL, 0, 0, PM_REMOVE)) {

		TranslateMessage(&eventMessage);

		DispatchMessage(&eventMessage);

		if (eventMessage.message == WM_QUIT) {
			isRunning = false;
			return;
		}
	}	
}