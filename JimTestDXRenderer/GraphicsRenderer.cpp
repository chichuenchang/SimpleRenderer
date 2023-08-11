#include "GraphicsRenderer.h"
#include <d3dcompiler.h>

GraphicsRenderer::GraphicsRenderer(): 
	mDeviceContext(nullptr), mSwapChain(nullptr), mVertexBuffer(nullptr), 
	mVsblob(nullptr), mPsblob(nullptr)
{
}

bool GraphicsRenderer::init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_11_1,
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	ID3D11DeviceContext * tempDeviceContext;
	for (UINT i = 0; i < num_driver_types; i++)
	{
		HRESULT result = D3D11CreateDevice(NULL, driver_types[i], NULL, NULL, feature_levels, 
			num_feature_levels, D3D11_SDK_VERSION, &mD3d11Device, &mFeatureLevel, &tempDeviceContext);
		if (SUCCEEDED(result))
		{
			break;
		}
		else if (FAILED(result))
		{
			return false;
		}
	}

	mD3d11Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&mDxgiDevice);
	mDxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&mDxgiAdapter);
	mDxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&mDxgiFacotory);

	mDeviceContext = new DeviceContext(tempDeviceContext);

	return true;
}

bool GraphicsRenderer::release()
{
	if (mVertexBuffer) 
	{
		mVertexBuffer->release();
	}

	mDxgiFacotory->Release();
	mDxgiAdapter->Release();
	mDxgiDevice->Release();

	mDeviceContext->release();
	mD3d11Device->Release();

	return true;
}

GraphicsRenderer * GraphicsRenderer::getRendererInstance()
{
	static GraphicsRenderer renderer;
	return &renderer;
}

bool GraphicsRenderer::createSwapChain()
{
	mSwapChain = new SwapChain();
	return true;
}

bool GraphicsRenderer::createVertexBuffer()
{
	mVertexBuffer = new VertexBuffer();
	return true;
}

ID3D11Device * GraphicsRenderer::getD3d11Device()
{
	return mD3d11Device;
}

IDXGIDevice * GraphicsRenderer::getDxgiDevice()
{
	return mDxgiDevice;
}

IDXGIAdapter * GraphicsRenderer::getDxgiAdapter()
{
	return mDxgiAdapter;
}

IDXGIFactory * GraphicsRenderer::getDxgiFactory()
{
	return mDxgiFacotory;
}

DeviceContext * GraphicsRenderer::getDeviceContext()
{
	return mDeviceContext;
}

SwapChain * GraphicsRenderer::getSwapChain()
{
	return mSwapChain;
}

VertexBuffer * GraphicsRenderer::getVertexBuffer()
{
	return mVertexBuffer;
}

bool GraphicsRenderer::createShaders()
{
	ID3DBlob* errblob = nullptr;
	HRESULT result = D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &mVsblob, &errblob);
	if (FAILED(result))
	{
		std::cout << "[ERROR] Shader compile failed" << std::endl;
		if (errblob)
		{
			char* errorStr = static_cast<char*>(errblob->GetBufferPointer());
		}
	}
	result = D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &mPsblob, &errblob);
	if (FAILED(result))
	{
		std::cout << "[ERROR] Shader compile failed" << std::endl;
		if (errblob)
		{
			char* errorStr = static_cast<char*>(errblob->GetBufferPointer());
		}
	}
	result = mD3d11Device->CreateVertexShader(mVsblob->GetBufferPointer(), mVsblob->GetBufferSize(), nullptr, &mVertexShader);
	if (FAILED(result))
	{
		std::cout << "[ERROR] Shader compile failed" << std::endl;
		if (errblob)
		{
			char* errorStr = static_cast<char*>(errblob->GetBufferPointer());
		}
	}
	result = mD3d11Device->CreatePixelShader(mPsblob->GetBufferPointer(), mPsblob->GetBufferSize(), nullptr, &mPixelShader);
	if (FAILED(result))
	{
		std::cout << "[ERROR] Shader compile failed" << std::endl;
		if (errblob)
		{
			char* errorStr = static_cast<char*>(errblob->GetBufferPointer());
		}
	}
	return true;
}

bool GraphicsRenderer::setShaders()
{
	ID3D11DeviceContext* d3d11DeviceContext = mDeviceContext->getD3d11DeviceContext();
	d3d11DeviceContext->VSSetShader(mVertexShader, nullptr, 0);
	d3d11DeviceContext->PSSetShader(mPixelShader, nullptr, 0);
	return true;
}

bool GraphicsRenderer::getShaderBufferAndSize(void ** byteCode, UINT * size)
{
	*byteCode = this->mVsblob->GetBufferPointer();
	*size = (UINT)this->mVsblob->GetBufferSize();
	return true;
}
