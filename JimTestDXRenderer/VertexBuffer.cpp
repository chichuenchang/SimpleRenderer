#include "VertexBuffer.h"
#include "GraphicsRenderer.h"

VertexBuffer::VertexBuffer():
	mD3d11Buffer(nullptr),
	mInputLayout(nullptr)
{
}

bool VertexBuffer::loadVerticesToDxVertexBuffer(void* verticesList, UINT vertexSize, UINT listSize,
	void * shaderByteCode, UINT shaderByteSize)
{
	if (mInputLayout)
	{
		mInputLayout->Release();
	}
	if (mD3d11Buffer) 
	{
		mD3d11Buffer->Release();
	}

	D3D11_BUFFER_DESC bufferInfo = {};
	bufferInfo.Usage = D3D11_USAGE_DEFAULT;
	bufferInfo.ByteWidth = vertexSize * listSize;
	bufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferInfo.CPUAccessFlags = false;
	bufferInfo.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA subResrcData = {};
	subResrcData.pSysMem = verticesList;

	mVertexSize = vertexSize;
	mListSize = listSize;

	GraphicsRenderer* renderer = GraphicsRenderer::get();
	HRESULT result = renderer->getD3d11Device()->CreateBuffer(&bufferInfo, &subResrcData,
		&mD3d11Buffer);
	if (FAILED(result))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		//Semantic Name, Semantic Index, Format, Input Slot, Aligned Byte offset, Input Slot Class,	Instance Data Step Rate
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	UINT layoutSize = ARRAYSIZE(layout);

	result = renderer->getD3d11Device()->CreateInputLayout(layout, layoutSize, shaderByteCode,
		shaderByteSize, &mInputLayout);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool VertexBuffer::release()
{
	mInputLayout->Release();
	mD3d11Buffer->Release();
	delete this;
	return false;
}

UINT VertexBuffer::getVertexSize()
{
	return mVertexSize;
}

UINT VertexBuffer::getListSize()
{
	return mListSize;
}

ID3D11Buffer * VertexBuffer::getD3d11Buffer()
{
	return mD3d11Buffer;
}

ID3D11InputLayout * VertexBuffer::getInputLayout()
{
	return mInputLayout;
}
