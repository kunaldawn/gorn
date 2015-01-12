
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

namespace gorn
{
	RenderContext _render;


	Application::Application()
	{
	}

	void Application::load()
	{
#ifdef GORN_PLATFORM_LINUX
		_render.getFiles()
            .addDefaultLoader<LocalFileLoader>("../%s");
		_render.getImages()
            .addLoader<PngImageLoader>();
#elif GORN_PLATFORM_ANDROID
		_render.getFiles()
            .addDefaultLoader<BundleFileLoader>("%s");
		_render.getImages()
            .addLoader<GraphicsImageLoader>();
#endif

        RenderSystem2D render2d(_render);

        _render.getTextures().define("font.png")
            .withParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST)
            .withParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	}

	void Application::unload()
	{
	}

	void Application::update(double dt)
	{

	}

}
