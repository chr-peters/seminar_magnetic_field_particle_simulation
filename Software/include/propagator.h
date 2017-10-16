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
  std::vector<Vector3D> getPoints(Particle particle, double maxDistance, Vector3D referencePoint);
  std::vector<Particle> getTrack(Particle particle, double maxDistance, Vector3D referencePoint);
  std::vector<Vector3D> getIntersectionPoints(Particle particle, const Plane3D &plane, double maxDistance, Vector3D referencePoint);
private:
  const FieldDescriptor &fieldDescriptor;
};


double getAlpha(Vector3D target, double eps = 1e-7);
double getBeta(Vector3D target, double eps = 1e-7);
double getGamma(Vector3D target, double eps = 1e-7);


#endif
