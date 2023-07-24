#pragma once
#include <d3d11.h>
#include "SwapChain.h"
#include <vector>

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* inD3d11DeviceContext);
	bool clearRenderTargetColor(SwapChain* swapChain, std::vector<float>& rgba);

	bool release();
	//~DeviceContext();
private:
	ID3D11DeviceContext* mD3d11DeviceContext;

};

