#pragma once
#include "JOSEApp.h"

#include <Windows.h> // Windows API
#include <iostream>

class Window
{
public:
	Window();
		
	//bool initiate(LRESULT (*WindowsPrcedure)(HWND, UINT, WPARAM , LPARAM));
	bool initiate(JOSEApp* appInstance);
	bool broadcast(); // forward the messages from Windows to our window
	bool release();
	bool isRun();

	RECT getClientWindowRect();

	//Events
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
public:
	bool SetHwnd(const HWND& hwnd);
	bool getHwnd(HWND** hwndOut);
	//~Window();

protected:
	HWND mHwnd;
	bool mIsRun;
};

