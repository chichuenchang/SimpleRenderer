#include "SwapChain.h"
#include "GraphicsRenderer.h"

SwapChain::SwapChain()
{
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	GraphicsRenderer* renderer = GraphicsRenderer::get();

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferCount = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.Width = width;  // set to window width
	desc.BufferDesc.Height = height;  // set to window height
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;  // handle to the window
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGIDevice* mDxgiDevice = renderer->mDxgiDevice;


	HRESULT result = renderer->mDxgiFacotory->CreateSwapChain(mDxgiDevice, &desc, &mDxgiSwapChain);
	if (FAILED(result))
	{
		return false;
	}
	return false;
}

bool SwapChain::release()
{
	HRESULT result = mDxgiSwapChain->Release();
	if (FAILED(result))
	{
		return false;
	}
	delete this;
	return true;
}
