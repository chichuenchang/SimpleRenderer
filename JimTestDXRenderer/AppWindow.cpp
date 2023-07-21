#include "AppWindow.h"

AppWindow::AppWindow()
{

}

void AppWindow::onCreate()
{
	std::cout << "[TEMP] AppWindows::onCreate() is called" << std::endl;
	Window::onCreate();
	bool res = GraphicsRenderer::get()->init();
	if (!res)
	{
		std::cout << "[TEMP] GraphicsRenderer initiate failed" << std::endl;
	}
}

void AppWindow::onUpdate()
{
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	GraphicsRenderer::get()->release();
}
