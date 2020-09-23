#include <iostream>
#include "RenderFactory.h"
#include "OpenGLRenderer.h"
#include "DirectXRenderer.h"
#include "GLES.h"

int main()
{
  // register the various 3D renderers with the factory object
  RendererFactory::registerRenderer("opengl", OpenGLRenderer::create);
  RendererFactory::registerRenderer("DirectX", DirectXRenderer::create);
  RendererFactory::registerRenderer("GLES", GLES::create);
  // create an OpenGL renderer
  Renderer *ogl = RendererFactory::createRenderer("opengl");
  ogl->render();
  delete ogl;

  // create a DirectX software renderer
  Renderer *DirectX = RendererFactory::createRenderer("DirectX");
  DirectX->render();
  delete DirectX;

  // create a DirectX software renderer
  Renderer *gles = RendererFactory::createRenderer("GLES");
  gles->render();
  delete gles;
  // unregister the DirectX renderer
  RendererFactory::unregisterRenderer("DirectX");
  DirectX = RendererFactory::createRenderer("DirectX");
  if (!DirectX)
  {
    std::cout << "DirectX renderer unregistered" << std::endl;
  }
  return EXIT_SUCCESS;
}

