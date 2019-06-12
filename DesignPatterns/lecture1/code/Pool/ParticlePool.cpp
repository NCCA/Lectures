#include "ParticlePool.h"
#include <iostream>
void ParticlePool::animate()
{
  for (auto &p : m_particles)
  {
    p.animate();
  }
}

void ParticlePool::create(double _x, double _y,double _xVel, double _yVel, int _lifetime)
{
  // Find an available particle.
  for (auto &p : m_particles)
  {
    if (!p.inUse())
    {
      std::cout<<p.id()<<'\n';
      p.init(_x, _y, _xVel, _yVel, _lifetime);
      return;
    }
  }
}
