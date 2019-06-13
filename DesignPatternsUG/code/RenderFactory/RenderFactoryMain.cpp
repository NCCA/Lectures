#include <iostream>
#include <RenderFactory.h>
#include "OpenGLRenderer.h"
int main()
{
    // create the factory object
    RenderFactory *f = new RenderFactory;

    // create an OpenGL renderer
    Renderer *renderType = f->createRenderer("OpenGL");
    renderType->render();
    delete renderType;

    //Renderer *directX =
    renderType=f->createRenderer("DirectX");
    renderType->render();
    delete renderType;

    delete f;

    Renderer *unknown= f->createRenderer("raytracer");
    if(unknown == 0)
    {
      std::cout<<"don't know how to create a raytracer\n";
    }

    return EXIT_SUCCESS;

}

