#if !defined(PROPAGATOR_H)
#define PROPAGATOR_H

#include "fields.h"
#include "particle.h"
#include "vector3d.h"
#include "plane3d.h"

#include <vector>

class Particle;

class Propagator {
public:
  Propagator(const FieldDescriptor &fieldDescriptor): fieldDescriptor(fieldDescriptor){}
  std::vector<Vector3D> getPoints(Particle &particle, double simulationTime);
  std::vector<Vector3D> getIntersectionPoints(Particle &particle, const Plane3D &plane, double simulationTime);
private:
  const FieldDescriptor &fieldDescriptor;
};


double getAlpha(Vector3D target);
double getBeta(Vector3D target);
double getGamma(Vector3D target);


#endif
