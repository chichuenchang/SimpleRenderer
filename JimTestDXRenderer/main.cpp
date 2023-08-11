#pragma once
#include "JOSEApp.h"

#include <stdexcept>

//int main() 
//{
//	AppWindow app;
//	if (app.init())
//	{
//		while (app.isRun())
//		{
//			app.broadcast();
//			//app.release();
//		}
//	}
//
//	return 0;
//}

void RunApp(JOSEApp* app)
{
	if (app->initiate())
	{
		while (app->isRunning())
		{
			app->update();
			//app->release();
		}
	}
	else
	{
		throw std::exception("[JOSEException] App initiated failed");
	}
}

int main()
{
	JOSEApp* app = new JOSEApp();
	try
	{
		RunApp(app);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}
	catch (...) {
		// This catch block will catch any exceptions not caught by the preceding blocks.
		std::cerr << "Caught unknown exception!" << std::endl;
	}

}