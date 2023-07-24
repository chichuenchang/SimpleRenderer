#include "DeviceContext.h"
#include <iostream>

DeviceContext::DeviceContext(ID3D11DeviceContext * inD3d11DeviceContext):
	mD3d11DeviceContext(inD3d11DeviceContext)
{
}

bool DeviceContext::clearRenderTargetColor(SwapChain* swapChain, std::vector<float>& rgba)
{
	if (rgba.size() != 4)
	{
		std::cout << "[ERROR] rgba vector size must be 4" << std::endl;
		return false;
	}
	ID3D11RenderTargetView* renderTargetView = swapChain->getD3d11RenderTargetView();
	mD3d11DeviceContext->ClearRenderTargetView(renderTargetView, rgba.data());

	return true;
}

bool DeviceContext::release()
{
	mD3d11DeviceContext->Release();
	delete this;
	
	return true;
}
