#pragma once
//#include "GraphicsRenderer.h"
class GraphicsRenderer;

class JOSEGameEngine
{
public:
	JOSEGameEngine();
	bool initiate();
	bool release();
	bool run();
	//JOSEGameEngine(JOSEGameEngine const&) = delete;
	//~JOSEGameEngine();
	static JOSEGameEngine* getEngineInstance();
	static GraphicsRenderer* getRendererInstance();

public:
	bool onCreate();
	bool onUpdate();

private:
};

