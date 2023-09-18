#include "AppWindow.h"
#include <vector>
#include <glm/glm.hpp>
#include "Utility.h"

AppWindow::AppWindow()
{

}

void AppWindow::onCreate()
{
	Window::onCreate();

	GraphicsRenderer* renderer = GraphicsRenderer::get();
	bool res = renderer->init();
	if (!res)
	{
		std::cout << "[TEMP] GraphicsRenderer initiate failed" << std::endl;
	}

	//mSwapChain = renderer->createSwapChain();
	res = renderer->createSwapChain();
	if (!res)
	{
		std::cout << "[TEMP] Swapchain created failed" << std::endl;
	}

	SwapChain* swapChain = renderer->getSwapChain();
	if (!swapChain)
	{
		std::cout << "[INFO] mSwapChain is empty" << std::endl;
	}

	if (mHwnd == NULL)
	{
		std::cout << "[INFO] mHwnd is empty" << std::endl;
	}
	RECT rect = this->getClientWindowRect();

	
	bool result = swapChain->init(this->mHwnd, rect.right-rect.left, rect.bottom- rect.top);
	if (!result)
	{
		std::cout << "[ERROR] Create Swapchain failed" << std::endl;
	}

	result = renderer->createVertexBuffer();
	VertexBuffer* vertexBuffer = renderer->getVertexBuffer();
	if (!vertexBuffer)
	{
		std::cout << "[ERROR] Vertex Buffer create failed" << std::endl;
	}

	std::vector<glm::vec3> vertices = 
	{
		{-0.5f, -0.5f, 0.0f},
		{0.0f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f}
	};

	renderer->createShaders();

	UINT verticesListSize = Utility::convert_sizet_to_uint(vertices.size());
	void* shaderByteCode = nullptr;
	UINT shaderSize = 0;
	renderer->getShaderBufferAndSize(&shaderByteCode, &shaderSize);
	UINT s = sizeof(vertices[0]);
	UINT a = sizeof(float);
	vertexBuffer->loadVerticesToDxVertexBuffer(vertices.data(), sizeof(vertices[0]), verticesListSize,
		shaderByteCode, shaderSize);
}

void AppWindow::onUpdate()
{
	GraphicsRenderer* renderer = GraphicsRenderer::get();

	Window::onUpdate();
	std::vector<float> clearcolor = { 1.0f, 0.0f, 0.0f, 1.0f };
	GraphicsRenderer::get()->getDeviceContext()->clearRenderTargetColor(renderer->getSwapChain(), clearcolor);


	RECT rect = this->getClientWindowRect();
	renderer->getDeviceContext()->setViewPortSize(rect.right - rect.left, rect.bottom - rect.top);
	renderer->setShaders();
	VertexBuffer* vertexBuffer = renderer->getVertexBuffer();
	renderer->getDeviceContext()->setVertexBuffer(vertexBuffer);
	renderer->getDeviceContext()->drawTriangleArray(vertexBuffer->getListSize(), 0);

	bool myResult = renderer->getSwapChain()->present(true);
	if (!myResult)
	{
		std::cout << "[ERROR] SwapChain Present Failed" << std::endl;
	}
}

void AppWindow::onDestroy()
{
	GraphicsRenderer* renderer = GraphicsRenderer::get();

	VertexBuffer* vBuffer = renderer->getVertexBuffer();
	if (vBuffer)
	{
		vBuffer->release();
	}


	Window::onDestroy();
	bool result = renderer->getSwapChain()->release();
	if (!result)
	{
		std::cout << "[TEMP] Cannot release SwapChain " << std::endl;
	}
	GraphicsRenderer::get()->release();
}
