#include "Renderer.h"


using namespace vre;

Renderer::Renderer() : swapChain(nullptr), renderDevice(nullptr), renderDeviceContext(nullptr), 
						swapChainInformation({ 0 }), backBuffer(nullptr) {

}

Renderer::~Renderer() {

	swapChain->Release();
	swapChain = nullptr;

	backBuffer->Release();
	backBuffer = nullptr;

	renderDevice->Release();
	renderDevice = nullptr;

	renderDeviceContext->Release();
	renderDeviceContext = nullptr;


	ZeroMemory(&swapChainInformation, sizeof(DXGI_SWAP_CHAIN_DESC));
}


bool Renderer::Initialize(HWND windowHandle_) {

	////////////////// Initialize Direct 3D ///////////////////////////
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
													D3D11_CREATE_DEVICE_DEBUG,	//Runtime layers to enable
													NULL,						//Feature Level Ordering. NULL Sets it to Default
													NULL,						//Number of elements in the ordered Levels
													D3D11_SDK_VERSION,			//What version of Direct X to use
													&swapChainInformation,		//Pointer to the Swap Chain Description(Render buffer info)
													&swapChain,					//Pointer to the Swap Chain(Render Buffers)
													&renderDevice,				//Pointer to the Device being used by Direct X
													NULL,						//Feature levels supported by this device, setting NULL sets it to default
													&renderDeviceContext);		//Pointer to the context for the rendering pipeline

	if (!SUCCEEDED(result)) {
		return false;
	}



	////////////////// Set up Back Buffer Render Target ///////////////////////////

	//Create back buffer to render to, then store it in a texture pointer
	ID3D11Texture2D* backBufferTexture;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);

	//Then we use that information to link to the back buffer object we created earlier
	renderDevice->CreateRenderTargetView(backBufferTexture, NULL, &backBuffer);

	//Doesn't destroy the object linked to on the GPU, just closes and frees the memory for the
	//accessor here
	backBufferTexture->Release();

	renderDeviceContext->OMSetRenderTargets(1, &backBuffer, NULL);



	////////////////// Set up ViewPort for Rendering ///////////////////////////

	D3D11_VIEWPORT viewPort;
	ZeroMemory(&viewPort, sizeof(D3D11_VIEWPORT));

	RECT clientSize;

	GetClientRect(windowHandle_, &clientSize);

	viewPort.TopLeftX = clientSize.left;
	viewPort.TopLeftY = clientSize.top;
	viewPort.Width = clientSize.right;
	viewPort.Height = clientSize.bottom;

	renderDeviceContext->RSSetViewports(1, &viewPort);


	return true;
}


void Renderer::Render() {

	//Clear our Back Buffer
	renderDeviceContext->ClearRenderTargetView(backBuffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	//Render to the Back Buffer


	//Swap out the Front Buffer for the Back Buffer
	swapChain->Present(0, 0);

}