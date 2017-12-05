#include "plot.h"

#include "particle.h"
#include "vector3d.h"
#include "fields.h"
#include "propagator.h"
#include "conditions.h"

#include<vector>
#include<iostream>

int main () {
  Vector3D momentum(1, 1, 0);
  Vector3D location(0, 0, 0);
  Particle particle(0, 1, 1, -0.5, location, momentum);

  Vector3D fieldStrength(0.1, 0, 0);
  HomogeneousField field(fieldStrength);
  Propagator propagator(field);
  std::vector<Vector3D> points = propagator.getPoints(particle, MaximumDistanceCondition(700, location), 3);
  plot("Homogeneous Field Example", points, false);
}
