#include "Renderer.h"


using namespace vre;

Renderer::Renderer() : swapChain(nullptr), renderDevice(nullptr), renderDeviceContext(nullptr), swapChainInformation({ 0 }) {

}

Renderer::~Renderer() {

	swapChain->Release();
	swapChain = nullptr;

	renderDevice->Release();
	renderDevice = nullptr;

	renderDeviceContext->Release();
	renderDeviceContext = nullptr;

	ZeroMemory(&swapChainInformation, sizeof(DXGI_SWAP_CHAIN_DESC));
}


bool Renderer::Initialize(HWND windowHandle_) {

	ZeroMemory(&swapChainInformation, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainInformation.BufferCount = 1;										//Number of Back Buffers
	swapChainInformation.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		//Use 32 bit color
	swapChainInformation.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;			//How to use Swap Chain
	swapChainInformation.OutputWindow = windowHandle_;							//Window to be Used
	swapChainInformation.SampleDesc.Count = 4;									//How many multisamples(Built in MSAA)
	swapChainInformation.Windowed = TRUE;										//Windowed(TRUE) / fullscreen(FALSE) Mode


	HRESULT result = D3D11CreateDeviceAndSwapChain(	NULL,						//Use default adapter
													D3D_DRIVER_TYPE_HARDWARE,	//Driver implemented on Hardware
													NULL,						//DLL for use in Rasterizer (NULL if using Hardware)
													D3D11_CREATE_DEVICE_DEBUG,						//Runtime layers to enable
													NULL,						//Feature Level Ordering. NULL Sets it to Default
													NULL,						//Number of elements in the ordered Levels
													D3D11_SDK_VERSION,			//What version of Direct X to use
													&swapChainInformation,			//Pointer to the Swap Chain Description(Render buffer info)
													&swapChain,			//Pointer to the Swap Chain(Render Buffers)
													&renderDevice,			//Pointer to the Device being used by Direct X
													NULL,						//Feature levels supported by this device, setting NULL sets it to default
													&renderDeviceContext);	//Pointer to the context for the rendering pipeline

	if (!SUCCEEDED(result)) {
		return false;
	}

	return true;
}


void Renderer::Render() {

}