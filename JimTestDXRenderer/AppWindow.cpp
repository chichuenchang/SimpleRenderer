#include "AppWindow.h"

AppWindow::AppWindow()
{

}

void AppWindow::onCreate()
{
	std::cout << "[TEMP] AppWindows::onCreate() is called" << std::endl;
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

	RECT rect = this->getClientWindowRect();
	if (mHwnd == NULL)
	{
		std::cout << "[INFO] mHwnd is empty" << std::endl;
	}
	
	bool result = swapChain->init(this->mHwnd, rect.right-rect.left, rect.bottom- rect.top);
	if (!result)
	{
		std::cout << "[ERROR] Create Swapchain failed" << std::endl;
	}
}

void AppWindow::onUpdate()
{
	GraphicsRenderer* renderer = GraphicsRenderer::get();

	Window::onUpdate();
	std::vector<float> clearcolor = { 1.0f, 0.0f, 0.0f, 1.0f };
	GraphicsRenderer::get()->getDeviceContext()->clearRenderTargetColor(renderer->getSwapChain(), clearcolor);

	bool myResult = renderer->getSwapChain()->present(true);
	if (!myResult)
	{
		std::cout << "[ERROR] SwapChain Present Failed" << std::endl;
	}
}

void AppWindow::onDestroy()
{
	GraphicsRenderer* renderer = GraphicsRenderer::get();

	Window::onDestroy();
	bool result = renderer->getSwapChain()->release();
	if (!result)
	{
		std::cout << "[TEMP] Cannot release SwapChain " << std::endl;
	}
	GraphicsRenderer::get()->release();
}
