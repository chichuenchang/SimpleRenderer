#pragma once
#include <Windows.h> // Windows API
#include <iostream>

class Window
{
public:
	Window();
		
	bool init();
	bool broadcast(); // forward the messages from Windows to our window
	bool release();
	bool isRun();

	RECT getClientWindowRect();

	//Events
	virtual void onCreate();
	virtual void onUpdate() = 0;
	virtual void onDestroy();
public:
	bool SetHwnd(const HWND& hwnd);

	//~Window();

protected:
	HWND mHwnd;
	bool mIsRun;
};

