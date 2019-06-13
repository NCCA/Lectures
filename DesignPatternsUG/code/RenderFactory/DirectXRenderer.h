#ifndef DIRECTXRENDERER_H
#define DIRECTXRENDERER_H
#include <iostream>
#include "Renderer.h"

class DirectXRenderer : public Renderer
{
public:

  bool loadScene(const std::string &_filename) {return true;}
  void setViewportSize(int _w, int _h) {;}
  void setCameraPos(double _x, double _y, double _z) {;}
  void setLookAt(double _x, double _y, double _z) {;}
  void render() {std::cout<<"DirectX Render\n";}
  ~DirectXRenderer(){std::cout<<"Direct X dtor called\n";}
};

#endif
