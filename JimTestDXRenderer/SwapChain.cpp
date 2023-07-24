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

	ID3D11Device* d3d11Device = renderer->getD3d11Device();

	HRESULT result = renderer->getDxgiFactory()->CreateSwapChain(d3d11Device, &desc, &mDxgiSwapChain);
	if (FAILED(result))
	{
		return false;
	}

	ID3D11Texture2D* buffer = NULL;
	result = mDxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	if (FAILED(result))
	{
		return false;
	}

	result = d3d11Device->CreateRenderTargetView(buffer, NULL, &mD3d11RenderTargetView);
	buffer->Release();
	if (FAILED(result))
	{
		return false;
	}


	return true;
}

bool SwapChain::present(const bool & vsync)
{
	HRESULT result = mDxgiSwapChain->Present(vsync, NULL);
	if (FAILED(result))
	{
		return false;
	}
	return true;
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

ID3D11RenderTargetView * SwapChain::getD3d11RenderTargetView()
{
	return mD3d11RenderTargetView;
}
