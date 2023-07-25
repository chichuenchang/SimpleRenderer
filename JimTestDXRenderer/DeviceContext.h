#pragma once
#include <d3d11.h>
#include "SwapChain.h"
#include "VertexBuffer.h"

#include <vector>

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* inD3d11DeviceContext);

	bool release();
	//~DeviceContext();
public:
	bool clearRenderTargetColor(SwapChain* swapChain, std::vector<float>& rgba);
	bool setVertexBuffer(VertexBuffer* vertexBuffer);
	bool drawTriangleArray(UINT verticesCount, UINT startVertexIndex);
	bool setViewPortSize(UINT width, UINT height);

private:
	ID3D11DeviceContext* mD3d11DeviceContext;
public: 
	ID3D11DeviceContext* getD3d11DeviceContext();

};

