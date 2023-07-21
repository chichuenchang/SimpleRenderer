#include "GraphicsRenderer.h"

GraphicsRenderer::GraphicsRenderer()
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


	for (UINT i = 0; i < num_driver_types; i++)
	{
		HRESULT result = D3D11CreateDevice(NULL, driver_types[i], NULL, NULL, feature_levels, 
			num_feature_levels, D3D11_SDK_VERSION, &mD3dDevice, &mFeatureLevel, &mDeviceContext);
		if (SUCCEEDED(result))
		{
			break;
		}
		else if (FAILED(result))
		{
			return false;
		}
	}

	return true;
}

bool GraphicsRenderer::release()
{
	mDeviceContext->Release();
	mD3dDevice->Release();

	return true;
}

GraphicsRenderer * GraphicsRenderer::get()
{
	static GraphicsRenderer renderer;
	return &renderer;

}
