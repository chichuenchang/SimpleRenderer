#pragma once
#include <d3d11.h>
#include <iostream>
#include "SwapChain.h"
#include "DeviceContext.h"
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
	ID3D11Device* mD3dDevice;
	D3D_FEATURE_LEVEL mFeatureLevel;

	IDXGIDevice* mDxgiDevice;
	IDXGIAdapter* mDxgiAdapter;
	IDXGIFactory* mDxgiFacotory;
public:
	ID3D11Device* getD3d11Device();
	IDXGIDevice* getDxgiDevice();
	IDXGIAdapter* getDxgiAdapter();
	IDXGIFactory* getDxgiFactory();
private:
	DeviceContext* mDeviceContext;
public:
	DeviceContext* getDeviceContext();
};

