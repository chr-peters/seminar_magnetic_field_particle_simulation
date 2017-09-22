#if !defined(PROPAGATOR_H)
#define PROPAGATOR_H

#include "fields.h"
#include "particle.h"
#include "vector3d.h"

#include <vector>

class Particle;

class Propagator {
public:
  Propagator(const FieldDescriptor &fieldDescriptor): fieldDescriptor(fieldDescriptor){}
  std::vector<Vector3D> getPoints(Particle particle, double simulationTime);
private:
  const FieldDescriptor &fieldDescriptor;
};

#endif
