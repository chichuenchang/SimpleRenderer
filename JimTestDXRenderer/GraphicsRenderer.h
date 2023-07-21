#pragma once
#include <d3d11.h>
#include <iostream>


class GraphicsRenderer
{
public:
	GraphicsRenderer();
	bool init();
	bool release();

	//~GraphicsRenderer();
	
	static GraphicsRenderer* get();

private:
	ID3D11Device * mD3dDevice;
	D3D_FEATURE_LEVEL mFeatureLevel;
	ID3D11DeviceContext * mDeviceContext;
};

