#include "JOSEGameEngine.h"
#include "GraphicsRenderer.h"

JOSEGameEngine::JOSEGameEngine()
{
}

JOSEGameEngine * JOSEGameEngine::getEngineInstance()
{
	static JOSEGameEngine engineInstance;
	return &engineInstance;
}

GraphicsRenderer * JOSEGameEngine::getRendererInstance()
{
	return GraphicsRenderer::getRendererInstance();
}
