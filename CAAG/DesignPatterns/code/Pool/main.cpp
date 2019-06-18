#include "ParticlePool.h"

int main()
{
  ParticlePool pool;
  for(int i=0; i<100; ++i)
  {
    pool.create(0, 0, 1, 1, 10);
  //  pool.create(1, 0, 1, 1, 10);
  //  pool.create(2, 0, 1, 1, 10);
  }
  while(1)
  {
    static int i=0;
    pool.animate();
    pool.create(++i, 0, 1, 1, 10);
  }

}
