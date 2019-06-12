// based on http://gameprogrammingpatterns.com/object-pool.html
#ifndef PARTICLE_H_
#define PARTICLE_H_

class Particle
{
public:
  Particle()  : m_framesLeft(0){}

  void init(double _x, double _y,double _xVel, double _yVel, int _lifetime);
  void animate();
  bool inUse() const { return m_framesLeft > 0; }
  int id()const {return m_id;}
private:
  int m_framesLeft;
  double m_x, m_y;
  double m_xVel, m_yVel;
  static int m_id;

};


#endif
