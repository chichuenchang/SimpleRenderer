#pragma once
#include <d3d11.h>
#include <iostream>
#include "SwapChain.h"
//class SwapChain;

class GraphicsRenderer
{
public:
	GraphicsRenderer();
	bool init();
	bool release();

	//~GraphicsRenderer();
	static GraphicsRenderer* get();
public:
	bool createSwapChain(SwapChain** swapChain);
private:
	ID3D11Device * mD3dDevice;
	D3D_FEATURE_LEVEL mFeatureLevel;
	ID3D11DeviceContext * mDeviceContext;

private:
	IDXGIDevice* mDxgiDevice;
	IDXGIAdapter* mDxgiAdapter;
	IDXGIFactory* mDxgiFacotory;
private:
	friend class SwapChain;
};

