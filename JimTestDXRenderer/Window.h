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


	//Events
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();


	//~Window();

protected:
	HWND mHwnd;
	bool mIsRun;
};

