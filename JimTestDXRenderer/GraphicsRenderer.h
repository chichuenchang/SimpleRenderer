#pragma once
#include <d3d11.h>
#include <iostream>
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
//class SwapChain;

class GraphicsRenderer
{
public:
	GraphicsRenderer();
	bool init();
	bool release();

	//~GraphicsRenderer();
	static GraphicsRenderer* getRendererInstance();
public:
	bool onCreate();
	bool onUpdate();

private:
	ID3D11Device* mD3d11Device;
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
	bool createVertexBuffer();

private:
	DeviceContext* mDeviceContext;
	SwapChain* mSwapChain;
	VertexBuffer* mVertexBuffer;
public:
	DeviceContext* getDeviceContext();
	SwapChain* getSwapChain();
	VertexBuffer* getVertexBuffer();


private:
	ID3DBlob* mVsblob;
	ID3DBlob* mPsblob;
	ID3D11VertexShader* mVertexShader;
	ID3D11PixelShader* mPixelShader;
public:
	bool createShaders();
	bool setShaders();
	bool getShaderBufferAndSize(void** byteCode, UINT* size);
};

