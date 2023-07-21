#include "Window.h"


//Window* window = nullptr;

Window::Window()
{
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		// Event when window is created
		Window* window = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		std::cout << "[TEMP] Windows Procedure gets message CREATE " << std::endl;
		window->onCreate();
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

bool Window::init()
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
	wc.lpfnWndProc = &WinProc;

	if (!::RegisterClassEx(&wc))
	{
		return false;
	}

	mHwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "JimTempWindowClass", "JimTestDXRenderer", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);
	// "JimTempWindowClass" must be the same string to wc.lpszClassName

	if (!mHwnd) 
	{
		// display error message if hwnd created failed
		DWORD errorCode = GetLastError();
		LPVOID lpMsgBuf;

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			errorCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

		LocalFree(lpMsgBuf);

		return false;
	}

	// show window
	::ShowWindow(mHwnd, SW_SHOW);
	::UpdateWindow(mHwnd);

	mIsRun = true;

	return true;
}

bool Window::broadcast()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
	{
		//  examine the application's message queue from Windows
		if (msg.message == WM_QUIT)
			break;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	this->onUpdate();
	Sleep(0);

	return false;
}

bool Window::release()
{
	if (mHwnd)
	{
		if (!::DestroyWindow(mHwnd))
		{
			return false;
		}
	}

	return true;
}

bool Window::isRun()
{
	return mIsRun;
}

void Window::onCreate()
{
	std::cout << "[TEMP] Window::onCreate() is called" << std::endl;
}

void Window::onDestroy()
{
	std::cout << "[TEMP] Destroy window is called " << std::endl;
	mIsRun = false;
}
