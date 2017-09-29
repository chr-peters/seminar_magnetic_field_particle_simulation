#include "plot.h"

#include "particle.h"
#include "vector3d.h"
#include "fields.h"
#include "propagator.h"
#include "plane3d.h"

#include<vector>
#include<iostream>

int main () {
  // initialize the particle
  Vector3D momentum(1, 1, 1);
  Vector3D location(1, 1, 1);
  Particle particle(0, 1, 1, 0.5, location, momentum);
  Particle particle2(particle);

  // initialize the field
  Vector3D fieldStrength(0.1, 0.1, 0);
  HomogeneousField field(fieldStrength);

  // initialize the plane
  Vector3D normalVector(1, 1, 20);
  Vector3D pointInPlane(60, 200, -10);
  Plane3D plane(pointInPlane, normalVector);

  // get the relevant points
  Propagator propagator(field);
  std::vector<Vector3D> points = propagator.getPoints(particle, 200);
  std::vector<Vector3D> intersectionPoints = propagator.getIntersectionPoints(particle2, plane, 200);
  plot("Homogeneous field with plane intersection", points, intersectionPoints, plane);
}
