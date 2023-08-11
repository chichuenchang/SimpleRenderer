#pragma once
#include "JOSEApp.h"
#include "AppWindow.h"
#include "JOSEGameEngine.h"
//#include "GraphicsRenderer.h"

#include "Utility.h"

#include <vector>
#include <glm/glm.hpp>

LRESULT CALLBACK WindowsProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		// Event when window is created
		JOSEApp* app = (JOSEApp*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)app);
		std::cout << "[TEMP] Windows Procedure gets message CREATE " << std::endl;

		app->onCreate();

		app->getAppWindow()->SetHwnd(hwnd);
		//app->getAppWindow()->onCreate();
		break;
	}
	
	case WM_DESTROY:
	{
		// Event when window is destoyed
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}

	default:
	{
		return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	case WM_CLOSE:
	{
		::PostQuitMessage(0);
		return 0;
	}
	}

	// For messages we don't handle, call the default window procedure.
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


JOSEApp::JOSEApp(): mAppWindow(new AppWindow()), mIsRunning(false)
{
}

bool JOSEApp::initiate()
{
	WNDCLASSEXA wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "JimTempWindowClass";
	wc.lpszMenuName = "JimMenu";
	wc.style = NULL;
	wc.lpfnWndProc = WindowsProcedure;

	if (!::RegisterClassEx(&wc))
	{
		return false;
	}

	if (mAppWindow)
	{
		mAppWindow->initiate(this);
	}
	else
	{
		return false;
	}

	mIsRunning = true;

	return true;
}

bool JOSEApp::isRunning()
{
	return true;
}

bool JOSEApp::release()
{
	mAppWindow->release();
	delete mAppWindow;
	return true;
}

bool JOSEApp::update()
{
	return onUpdate();
}

bool JOSEApp::onCreate()
{
	if (!mAppWindow)
	{
		throw std::exception("[EXCEPTION] AppWindows is not initiated");
	}
	mAppWindow->onCreate();

	JOSEGameEngine* engine = JOSEGameEngine::getEngineInstance();
	GraphicsRenderer* renderer = engine->getRendererInstance();

	bool res = renderer->init();
	if (!res)
	{
		throw std::exception( "[EXCEPTION] GraphicsRenderer initiate failed" );
	}

	res = renderer->createSwapChain();
	if (!res)
	{
		throw std::exception( "[EXCEPTION] Swapchain created failed" );
	}

	SwapChain* swapChain = renderer->getSwapChain();
	if (!swapChain)
	{
		throw std::exception( "[EXCEPTION] mSwapChain is empty" );
	}

	if (mAppWindow->mHwnd == NULL)
	{
		std::cout << "[INFO] mHwnd is empty" << std::endl;
	}
	RECT rect = this->getClientWindowRect();


	bool result = swapChain->init(this->mHwnd, rect.right - rect.left, rect.bottom - rect.top);
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

	return true;
}

bool JOSEApp::onUpdate()
{

	GraphicsRenderer* renderer = GraphicsRenderer::getRendererInstance();

	std::vector<float> clearcolor = { 1.0f, 0.0f, 0.0f, 1.0f };
	GraphicsRenderer::getRendererInstance()->getDeviceContext()->clearRenderTargetColor(renderer->getSwapChain(), clearcolor);


	RECT rect = mAppWindow->getClientWindowRect();
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


	mAppWindow->broadcast();
	return true;
}

bool JOSEApp::onRelease()
{
	return false;
}

AppWindow * JOSEApp::getAppWindow()
{
	return mAppWindow;
}
