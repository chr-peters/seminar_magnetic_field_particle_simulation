#include "plot.h"

#include "particle.h"
#include "vector3d.h"
#include "fields.h"
#include "propagator.h"

#include<vector>

int main () {
  Vector3D momentum(1, 1, 1);
  Vector3D location(0, 0, 0);
  Particle particle(0, 1, 2, 3.5, location, momentum);

  Vector3D fieldStrength(0, 0, 0);
  HomogenousField field(fieldStrength);
  Propagator propagator(field);
  std::vector<Vector3D> points = propagator.getPoints(particle, 100);
  plot(points);
}
