// based on http://gameprogrammingpatterns.com/object-pool.html
#ifndef PARTICLEPOOL_H_
#define PARTICLEPOOL_H_

#include <array>
#include "Particle.h"
class ParticlePool
{
public:
  void create(double _x, double _y,double _xVel, double _yVel, int _lifetime);

  void animate();


private:
  static constexpr int PoolSize = 100;
  std::array<Particle,PoolSize> m_particles;
};



#endif
