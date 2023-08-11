#pragma once
//#include "AppWindow.h"
//#include "JOSEGameEngine.h"

class AppWindow;
class JOSEGameEngine;

class JOSEApp
{
public:
	JOSEApp();
	//~JOSEApp();

public:
	bool initiate();
	bool isRunning();
	bool release();
	bool update();

public:
	bool onCreate();
	bool onUpdate();
	bool onRelease();

public:
	AppWindow* getAppWindow();
private:
	AppWindow* mAppWindow;

	bool mIsRunning;


};

