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

public:
	bool createSwapChain();
private:
	DeviceContext* mDeviceContext;
	SwapChain* mSwapChain;
public:
	DeviceContext* getDeviceContext();
	SwapChain* getSwapChain();
};

