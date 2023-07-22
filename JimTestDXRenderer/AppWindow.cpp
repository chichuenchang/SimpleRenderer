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
	res = renderer->createSwapChain(&mSwapChain);
	if (!mSwapChain)
	{
		std::cout << "[INFO] mSwapChain is empty" << std::endl;
	}

	RECT rect = this->getClientWindowRect();
	if (mHwnd == NULL)
	{
		std::cout << "[INFO] mHwnd is empty" << std::endl;
	}
	mSwapChain->init(this->mHwnd, rect.right-rect.left, rect.bottom- rect.top);
}

void AppWindow::onUpdate()
{
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	bool result = mSwapChain->release();
	if (!result)
	{
		std::cout << "[TEMP] Cannot release SwapChain " << std::endl;
		
	}
	GraphicsRenderer::get()->release();
}
