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
	mD3d11DeviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

	return true;
}

bool DeviceContext::setVertexBuffer(VertexBuffer * vertexBuffer)
{
	UINT stride = vertexBuffer->getVertexSize();
	
	UINT offset = 0;

	ID3D11Buffer* buffer = vertexBuffer->getD3d11Buffer();
	mD3d11DeviceContext->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	mD3d11DeviceContext->IASetInputLayout(vertexBuffer->getInputLayout());

	return true;
}

bool DeviceContext::drawTriangleArray(UINT verticesCount, UINT startVertexIndex)
{
	mD3d11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	mD3d11DeviceContext->Draw(verticesCount, startVertexIndex);

	return true;
}

bool DeviceContext::setViewPortSize(UINT width, UINT height)
{
	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	mD3d11DeviceContext->RSSetViewports(1, &viewport);

	return true;
}

ID3D11DeviceContext * DeviceContext::getD3d11DeviceContext()
{
	return mD3d11DeviceContext;
}

bool DeviceContext::release()
{
	mD3d11DeviceContext->Release();
	delete this;
	
	return true;
}
