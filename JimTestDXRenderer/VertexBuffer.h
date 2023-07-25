#pragma once
#include <d3d11.h>
class VertexBuffer
{
public:
	VertexBuffer();
	bool loadVerticesToDxVertexBuffer(void* verticesList, UINT vertexSize, UINT listSize, 
		void * shaderByteCode, UINT shaderByteSize);
	bool release();
	//~VertexBuffer();

private:
	UINT mVertexSize;
	UINT mListSize;
public:
	UINT getVertexSize();
	UINT getListSize();
private:
	ID3D11Buffer* mD3d11Buffer;
	ID3D11InputLayout* mInputLayout;
public:
	ID3D11Buffer* getD3d11Buffer();
	ID3D11InputLayout* getInputLayout();


};

