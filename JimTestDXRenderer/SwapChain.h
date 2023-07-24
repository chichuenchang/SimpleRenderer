#pragma once
#include "d3d11.h"

class SwapChain
{
public:
	SwapChain();

	bool init(HWND hwnd, UINT width, UINT height);
	bool present(const bool& vsync);

	bool release();
	//~SwapChain();
private:
	IDXGISwapChain* mDxgiSwapChain;
	ID3D11RenderTargetView* mD3d11RenderTargetView;
public:
	ID3D11RenderTargetView* getD3d11RenderTargetView();

};

