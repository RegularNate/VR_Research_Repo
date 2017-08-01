#pragma once


#include <windows.h>
#include <windowsx.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>




//Be sure to have the DX SDK installed on your computer,
//unless working in Windows 8 or higher
//
//If you don't have it installed on a 7 machine, then you'll need to uninstall the base
//Windows 7 June 2010 update SDKs and replace them with the DX June 2010s SDK


//VR Engine
namespace vre {

	class Renderer {

	public:
		Renderer();
		~Renderer();

		bool Initialize(HWND windowHandle_);
		void Render();


	private:
		IDXGISwapChain* swapChain;				//This controls the draw buffers
		ID3D11Device* renderDevice;					//This IS the GPU
		ID3D11DeviceContext* renderDeviceContext;	//This is the context to the pipeline on the GPU

		DXGI_SWAP_CHAIN_DESC swapChainInformation;
	};
}