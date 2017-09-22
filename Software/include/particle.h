#if !defined(PARTICLE_H)
#define PARTICLE_H

#include "vector3d.h"
#include "propagator.h"

#include<iostream>

class Particle {
public:
  Particle(double time, double energy, double mass, double charge,
	   const Vector3D& location, const Vector3D& momentum);
  inline double getTime() const { return time; }
  inline double getEnergy() const { return energy; }
  inline double getMass() const { return mass; }
  inline double getCharge() const { return charge; }
  inline Vector3D getLocation() const { return location; }
  inline Vector3D getMomentum() const { return momentum; }
  friend std::ostream &operator<<(std::ostream &os, const Particle &p);
  friend class Propagator;
private:
  double time;
  double energy;
  double mass;
  double charge;
  Vector3D location;
  Vector3D momentum;
};

std::ostream &operator<<(std::ostream &os, const Particle &p);

#endif
