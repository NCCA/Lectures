#include "Particle.h"
#include <iostream>
int Particle::m_id=0;

void Particle::init(double _x, double _y,double _xVel, double _yVel, int _lifetime)
{
  m_x = _x;
  m_y = _y;
  m_xVel = _xVel;
  m_yVel = _yVel;
  m_framesLeft = _lifetime;
  m_id++;
}


void Particle::animate()
{
  if (!inUse())
  {
    return;
  }
  m_framesLeft--;
  m_x += m_xVel;
  m_y += m_yVel;
  std::cout<<"Particle "<<m_x<<" "<<m_y<<std::endl;
}
