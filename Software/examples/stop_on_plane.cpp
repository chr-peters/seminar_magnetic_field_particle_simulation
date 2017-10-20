#include "plot.h"

#include "particle.h"
#include "vector3d.h"
#include "fields.h"
#include "propagator.h"
#include "plane3d.h"
#include "conditions.h"

#include<vector>
#include<iostream>

int main () {
  // initialize the particle
  Vector3D momentum(1, 1, 1);
  Vector3D location(1, 1, 1);
  Particle particle(0, 1, 1, 0.5, location, momentum);

  // initialize the field
  Vector3D fieldStrength(0.1, 0.1, 0);
  HomogeneousField field(fieldStrength);

  // initialize the plane
  Vector3D normalVector(0, 0, 1);
  Vector3D pointInPlane(60, 200, -10);
  Plane3D plane(pointInPlane, normalVector);

  // get the relevant points
  Propagator propagator(field);
  std::vector<Vector3D> points = propagator.getPoints(particle, PlaneIntersectionCondition(plane));
  std::vector<Vector3D> intersectionPoints = propagator.getIntersectionPoints(particle, plane, PlaneIntersectionCondition(plane));
  plot("Homogeneous field with plane intersection", points, intersectionPoints, plane);
}
