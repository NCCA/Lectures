# Introduction to Modern OpenGL
Jon Macey

jmacey@bournemouth.ac.uk

---

## How OpenGL Works
- OpenGL uses a series of matrices to control the position and way primitives are drawn
- OpenGL 1.x - 2.x allows these primitives to be drawn in two ways
	- immediate mode 
	- core profile (this mode uses buffer objects to retain the data on the GPU)

--

## Immediate Mode
- In immediate mode the vertices to be processed are sent to the GPU (Graphics Card) one at a time.
- This means there is a bottleneck between CPU and GPU whilst data is sent
- This method is easy to use but not very efficient
- Immediate mode has become deprecated as part of OpenGL 3.x and is not available in OpenGL ES


--

## Core Profile Mode
- In this mode the data to be drawn is sent to the GPU and stored in graphics memory.
- A pointer to this object is returned to the user level program and this object reference is called when drawing etc.
- This requires a little more setup but does improve the Frame Rate considerably.
- For most of the examples we will use this mode.
- This is also the way DirectX works

--

## GLSL
- OpenGL Shading Language is a high level shading language based on C
- It allows us to program directly on the GPU and can be used for Shading calculations for vertex and fragment based processing.
- We will look at this in more detail later but to use the full OpenGL 3.x functionality we need to also create a GLSL shader and process the vertices on the GPU
- Using GLSL we can also manipulate the actual vertices of the system.

--

## Immediate Mode

- OpenGL provides tools for drawing many different primitives, including Points, Lines Quads etc.
- Most of them are described by one or more vertices. 
- In OpenGL we describe a list of vertices by using the ```glBegin()``` and ```glEnd()``` functions.
The argument to the ```glBegin()``` function determines how the vertices passed will be drawn.
We will not be using this mode and most examples on the web will use this

--

## OpenGL Profiles
- The current OpenGL version is 4.5, it has full compatibility with OpenGL ES 3.0 for embedded devices
- There are two profiles associated with this version
	- Core Profile
	- Compatibility profile

--

## OpenGL 4.5 Core
- Released 2014 (see https://www.opengl.org/wiki/History_of_OpenGL)
- The Core profile is very new and many GPU’s do not fully support this (Mac always behing currently 4.2)
- This profile doesn’t contain any of the immediate mode GL elements and has no backward compatibility
- What we are using in the lab.

--

## OpenGL 4 Compatibility
- The compatibility profile contains lots of OpenGL immediate mode elements as well as earlier GLSL structures and components
- This means legacy code will still work with the drivers but may not be optimal
- This year the ngl library has been ported to work with only OpenGL 3.2 core profile. 
- This needs Mac OSX Lion, linux or window with the latest drivers. There is now also a port for iOS 5 / OpenGL ES2.0 and Raspberry Pi /EGL

--

## Compatibility Profile
- The main problem with the compatibility profile is there are no clear guidelines on the implementation
- Different vendors behave differently
- Usually the whole system will fall back to the “software implementation” (not on the GPU)

---

## Programmers view of OpenGL
- To the programmer, OpenGL is a set of commands that allow the specification of geometric objects in two or three dimensions, together with commands that control how these objects are rendered into the framebuffer.
- A typical program that uses OpenGL begins with calls to open a window into the framebuffer. (in our case using Qt)
- Once a GL context is allocated, the programmer is free to issue OpenGL commands. 

--

## Programmers view of OpenGL

- Some calls are used to draw simple geometric objects (i.e. points, line segments, and polygons)
- Others affect the rendering of these primitives including how they are lit or coloured and how they are mapped from the user’s two- or three-dimensional model space to the two-dimensional screen. 
- There are also calls to effect direct control of the framebuffer, such as reading and writing pixels.

--

## Client Server Model
- The model for interpretation of OpenGL commands is client-server. 
- That is, a program (the client) issues commands, and these commands are interpreted and processed by the OpenGL (the server). 
- The server may or may not operate on the same computer as the client. 
- In this sense, the GL is “network-transparent.” 
- A server may maintain a number of OpenGL contexts, each of which is an encapsulation of current GL state. 

--

## OpenGL Context
- before we can use OpenGL we need to generate an OpenGL context
- This initialises the GL state and other elements of the library
- This is not the responsibility of OpenGL to create this and varies in the different Operating systems
- There are many ways to create the context but I will concentrate on two methods
	- Qt 5 
	- SDL 2
- There is also a new system called [EGL](https://www.khronos.org/egl) which will be avaliable on most platforms soon.

--

## OpenGL Context
- Both Qt and SDL work well on multiple platforms to create an OpenGL context
- Qt is best for GUI / Windowed based systems
- SDL is perfect for games and also has Joystick / Gamepad interfaces
- As Modern OpenGL is quite complex I will start with creating a compatibility profile OpenGL Demo and expand to core profile once we learn some more OpenGL

---

## SDL
>  "Simple DirectMedia Layer is a cross-platform multimedia library designed to provide low level access to audio, keyboard, mouse, joystick, 3D hardware via OpenGL, and 2D video framebuffer. It is used by MPEG playback software, emulators, and many popular games, including the award winning Linux port of "Civilization: Call To Power."

- SDL is ideal for games so if you want to do some games programming use SDL over Qt

--

## sdl2-config
- When sdl is installed a script called sdl2-config is placed in the /usr/bin directory
- This script can be run to get the correct build flags for sdl there is also an sdl-config for earlier SDL 1.x libs as well

```
$sdl2-config --cflags --libs
-I/usr/local/include/SDL2 -I/usr/X11R6/include -D_THREAD_SAFE
-L/usr/local/lib -lSDL2
```

--

## platform includes
- Depending upon platform gl.h is in different directories

```
#if defined (__linux__) || defined (WIN32)
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif
#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#endif
```

--

## [SDLCompat](https://github.com/NCCA/OpenGLCode/tree/master/SDLCompat)
```
int main()
{

  // Initialize SDL's Video subsystem
  if (SDL_Init(SDL_INIT_VIDEO) < 0 )
  {
    // Or die on error
    SDLErrorExit("Unable to initialize SDL");
  }

  // now get the size of the display and create a window we need to init the video
  SDL_Rect rect;
  SDL_GetDisplayBounds(0,&rect);
  // now create our window
  SDL_Window *window=SDL_CreateWindow("SDL 2 and compat OpenGL",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      rect.w/2,
                                      rect.h/2,
                                      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
                                     );
  // check to see if that worked or exit
  if (!window)
  {
    SDLErrorExit("Unable to create window");
  }

  // Create our opengl context and attach it to our window

   SDL_GLContext glContext=createOpenGLContext(window);
   if(!glContext)
   {
     SDLErrorExit("Problem creating OpenGL context");
   }
   // make this our current GL context (we can have more than one window but in this case not)
   SDL_GL_MakeCurrent(window, glContext);
  /* This makes our buffer swap syncronized with the monitor's vertical refresh */
  SDL_GL_SetSwapInterval(1);
  // now setup a basic camera for viewing
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(45,(float)rect.w/rect.h,0.5,100);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(2,2,2,0,0,0,0,1,0);
  // flag to indicate if we need to exit
  bool quit=false;
  // sdl event processing data structure
  SDL_Event event;
  while(!quit)
  {

    while ( SDL_PollEvent(&event) )
    {
      switch (event.type)
      {
        // this is the window x being clicked.
        case SDL_QUIT : quit = true; break;
        // if the window is re-sized pass it to the ngl class to change gl viewport
        // note this is slow as the context is re-create by SDL each time
        case SDL_WINDOWEVENT :
          int w,h;
          // get the new window size
          SDL_GetWindowSize(window,&w,&h);
        break;

        // now we look for a keydown event
        case SDL_KEYDOWN:
        {
          switch( event.key.keysym.sym )
          {
            // if it's the escape key quit
            case SDLK_ESCAPE :  quit = true; break;
            case SDLK_w : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
            case SDLK_s : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
            case SDLK_f :
            SDL_SetWindowFullscreen(window,SDL_TRUE);
            glViewport(0,0,rect.w,rect.h);
            break;

            case SDLK_g : SDL_SetWindowFullscreen(window,SDL_FALSE); break;
            default : break;
          } // end of key process
        } // end of keydown

        default : break;
      } // end of event switch
    } // end of poll events

    // now clear screen and render
      glClear(GL_COLOR_BUFFER_BIT);
    // draw a triangle
    drawTriangle();
    // swap the buffers
    SDL_GL_SwapWindow(window);

  }
  // now tidy up and exit SDL
 SDL_Quit();
}
```

--

## OpenGL Context Creation

```
SDL_GLContext createOpenGLContext(SDL_Window *window)
{
  // Request an opengl 3.2 context first we setup our attributes, if you need any
  // more just add them here before the call to create the context
  // SDL doesn't have the ability to choose which profile at this time of writing,
  // but it should default to the core profile
  // for some reason we need this for mac but linux crashes on the latest nvidia drivers
  // under centos
  #ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  #endif
 // set multi sampling else we get really bad graphics that alias
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,16);
  // Turn on double buffering with a 24bit Z buffer.
  // You may need to change this to 16 or 32 for your system
  // on mac up to 32 will work but under linux centos build only 16
  //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 48);
  // enable double buffering (should be on by default)
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  //
  return SDL_GL_CreateContext(window);

}
```

--

## draw triangle

```
void drawTriangle()
{
  glPointSize(10);
  glEnable(GL_MULTISAMPLE);
  static int rot=0;
  glPushMatrix();
    glRotated(rot,0,1,0);
    glBegin(GL_TRIANGLES);
      glColor3f(1,0,0);
      glVertex3d(0,1,0);
      glColor3f(0,1,0);
      glVertex3d(1,-1,0);
      glColor3f(0,0,1);
      glVertex3d(-1,-1,0);
    glEnd();
  glPopMatrix();
  ++rot;
}
```

---

## Qt 5.x
- Qt 4 had a specific GLWidget for creating an OpenGL context
- Qt 5 improves on this by extending the basic window to allow the usage of OpenGL rendering (as well as others)
- Qt5 uses a QSurface as an abstraction for a rendering surface all we have to do is setup an OpenGL context and create a surface
- Qt5 also has a number of OpenGL functions encapsulated into Qt itself we will not be using this as the ngl:: library already has these.

--

## [QSurfaceFormat](http://doc.qt.io/qt-5/qsurfaceformat.html)

```
/****************************************************************************
basic OpenGL demo modified from http://qt-project.org/doc/qt-5.0/qtgui/openglwindow.html
****************************************************************************/
#include "OpenGLWindow.h"

#include <QtGui/QGuiApplication>
#include <iostream>
int main(int argc, char **argv)
{
  QGuiApplication app(argc, argv);
  // create an OpenGL format specifier
  QSurfaceFormat format;
  // set the number of samples for multisampling
  // will need to enable glEnable(GL_MULTISAMPLE); once we have a context
  format.setSamples(4);
  format.setMajorVersion(4);
  format.setMinorVersion(5);
  // now we are going to set to Compat Profile OpenGL so we can use and old Immediate mode GL
  format.setProfile(QSurfaceFormat::CompatibilityProfile);
  // now set the depth buffer to 24 bits
  format.setDepthBufferSize(24);
  QSurfaceFormat::setDefaultFormat(format);
  // now we are going to create our scene window
  OpenGLWindow window;
  // and set the OpenGL format
  //window.setFormat(format);
  // we can now query the version to see if it worked
  std::cout<<"Profile is "<<format.majorVersion()<<" "<<format.minorVersion()<<"\n";
  // set the window size
  window.resize(1024, 720);
  // and finally show
  window.show();

  return app.exec();
}
```

--

## [QOpenGLWindow / Widget](http://doc.qt.io/qt-5/qopenglwindow.html)
- We inherit from these classes and implement our own OpenGL functions.
- The Window is a stand alone window class with an OpenGL context / drawing area
- The Widget is used within another window to allow use to develop GUI and OpenGL components together.
- Both are very similar and have the same virtual methods for us to override.

--

## [initalizeGL](http://doc.qt.io/qt-5/qopenglwindow.html#initializeGL)
- This is called once when the OpenGL context has been created (after the window has been created but before the first call to paintGL)
- We usually use this for initialisation of OpenGL specific things (loading shaders, creating geo etc) which will need to have an active context.
- Always start timers in this method and not the ctor as if the timer function called paint GL it may crash if not valid context is present.
- This is also where we will need to load extensions etc (usually using GLEW or   ngl::NGLInit::instance();

--

## [resizeGL(int _w, int _h)](http://doc.qt.io/qt-5/qopenglwindow.html#resizeGL)
- This is merely a convenience function in order to provide an API that is compatible with QOpenGLWidget. Unlike with QOpenGLWidget, derived classes are free to choose to override resizeEvent() instead of this function.
- Avoid issuing OpenGL commands from this function as there may not be a context current when it is invoked. If it cannot be avoided, call makeCurrent().
- Also worth noting we may need to take into account devicePixelRatio() for retina displays (for SDL you have to use platform specific function calls)

--

## [paintGL](http://doc.qt.io/qt-5/qopenglwindow.html#paintGL)
- This method is called every time update() is called on the window (and is usually synched to vsynch of the monitor but this can be changed).
- This is usually used for drawing our scene and other operations.
- Depending upon advanced OpenGL usage we may need to think about which context we are using as well as which RenderBuffer etc as Qt uses it’s own internal states as well.

--

## [OpenGLWindow.h](https://github.com/NCCA/OpenGLCode/blob/master/Qt5Compat/include/OpenGLWindow.h)

```
#ifndef OPENGLWINDOW_H__
#define OPENGLWINDOW_H__
#include <QOpenGLWindow>

class OpenGLWindow : public QOpenGLWindow
{
  // need to tell Qt to run the MOC
  Q_OBJECT
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor for OpenGL window must set the surface type to OpenGL
    //----------------------------------------------------------------------------------------------------------------------
    explicit OpenGLWindow();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor, remember to remove the device once finished
    //----------------------------------------------------------------------------------------------------------------------

    ~OpenGLWindow();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief render method called every update
    //----------------------------------------------------------------------------------------------------------------------
    void paintGL();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief pure virtual initialize method we override in our base class to do our drawing
    /// this is only called one time, just after we have a valid GL context use this to init any global GL elements
    //----------------------------------------------------------------------------------------------------------------------
   void initializeGL();

  private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief event called by the timer to allow use to re-draw / animate
    //----------------------------------------------------------------------------------------------------------------------
    void timerEvent(QTimerEvent *);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief process key events
    //----------------------------------------------------------------------------------------------------------------------
    void keyPressEvent(QKeyEvent *);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief resize event
    //----------------------------------------------------------------------------------------------------------------------
    void resizeGL(int _w, int _h);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief window width from resize event
    //----------------------------------------------------------------------------------------------------------------------
    int m_width;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief window height from resize event
    //----------------------------------------------------------------------------------------------------------------------
    int m_height;
    int rot=0;
};
#endif

```

--

## [OpenGLWindow.cpp](https://github.com/NCCA/OpenGLCode/blob/master/Qt5Compat/src/OpenGLWindow.cpp)
```

#include "OpenGLWindow.h"
#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <QKeyEvent>
#include <QApplication>
#include <iostream>
#ifdef __APPLE__
  #include <glu.h>
#else
  #include <GL/glu.h>
#endif

OpenGLWindow::OpenGLWindow()
{
  setTitle("Qt5 compat profile OpenGL 2.1");
}

OpenGLWindow::~OpenGLWindow()
{
}



void OpenGLWindow::initializeGL()
{

  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  int w=this->size().width();
  int h=this->size().height();
  gluPerspective(45,(float)w/h,0.5,100);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(2,2,2,0,0,0,0,1,0);

  glViewport(0,0,width(),height());
  startTimer(10);

}

void OpenGLWindow::paintGL()
{
  glViewport(0,0,m_width,m_height);
  glClear(GL_COLOR_BUFFER_BIT);
  //static int rot=0;
  glPushMatrix();
    glRotated(rot,0,1,0);
    glBegin(GL_TRIANGLES);
      glColor3f(1,0,0);
      glVertex3d(0,1,0);
      glColor3f(0,1,0);
      glVertex3d(1,-1,0);
      glColor3f(0,0,1);
      glVertex3d(-1,-1,0);
    glEnd();
  glPopMatrix();
 // ++rot;
}

void OpenGLWindow::timerEvent(QTimerEvent *)
{
  rot++;
  update();
}

void OpenGLWindow::keyPressEvent(QKeyEvent *_event)
{
  switch (_event->key())
  {
   case Qt::Key_Escape : QApplication::exit(EXIT_SUCCESS); break;
  }
}

void OpenGLWindow::resizeGL(int _w, int _h)
{
  m_width=_w;
  m_height=_h;
}
```

---

## References
- Segal M, Akeley K The OpenGL	Graphics System: A Specification (Version 4.0 (Core Profile) - March 11, 2010)
- F S. Hill  Computer Graphics Using Open GL (3rd Edition) 
- Shreiner Et Al OpenGL Programming Guide: The Official Guide to Learning OpenGL
- Foley & van Dam Computer Graphics: Principles and Practice in C (2nd Edition) 

