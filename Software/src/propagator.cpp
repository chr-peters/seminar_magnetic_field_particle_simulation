#include "propagator.h"

#include<cmath>

const double PI = 4*atan(1);

std::vector<Vector3D> Propagator::getPoints(Particle &particle, double simulationTime) {
  std::vector<Vector3D> res;
  double timeStep = simulationTime / 50;
  double startTime = 0;
  res.push_back(particle.location);

  // TODO transform the relevant vectors

  // get the magnetic field at the position of the particle
  Vector3D magneticField = fieldDescriptor.getStrength(particle.location);
  // get the current momentum of the particle
  Vector3D initialMomentum = particle.momentum;

  // get the radius of the circle
  double r = std::abs(initialMomentum.y / (particle.charge * magneticField.z));
  // get the angular velocity
  double w = std::abs(particle.charge * magneticField.z / particle.mass);

  // get the new position of the particle
  particle.location.z = initialMomentum.z * startTime / particle.mass;
  particle.location.x = r * sin(w * startTime) - r;
  particle.location.y = r * cos(w * startTime);

  // transform the position back to where it was initially

  res.push_back(particle.location);

  return res;
}

std::vector<Vector3D> Propagator::getIntersectionPoints(Particle &particle, const Plane3D& plane, double simulationTime) {
  // the result
  std::vector<Vector3D> res;
  // first get the points
  std::vector<Vector3D> points = getPoints(particle, simulationTime);
  // get plane properties
  Vector3D normalVector = plane.getNormalVector();
  double d = normalVector * plane.getPointInPlane();
  // iterate over the points and check if the line between two points intersects with the plane
  for (unsigned int i=0; i<points.size()-1; i++) {
    double t0 = d - normalVector * points[i];
    double t1 = d - normalVector * points[i+1];
    if (t0 * t1 <= 0) {
      // The sign of t0 and t1 is not the same so an intersection occured
      // get the intersection point of the line between points i and i+1 and the plane
      Vector3D deltaP = points[i+1] - points[i];
      double t = (d - normalVector * points[i])/(normalVector * deltaP);
      res.push_back(points[i] + t * deltaP);
    }
  }
  return res;
}

double getAlpha(Vector3D target) {
  // project the target onto the xz-plane
  target.y = 0;

  // get the angle between the projection and the z-axis
  double alpha = std::acos(target.z/target.norm());
  if (target.x < 0)
    return -alpha;
  else
    return alpha;
}

double getBeta(Vector3D target) {
  if (target.y < 0)
    return PI/2 - std::acos(-target.y/target.norm());
  else
    return std::acos(target.y/target.norm()) - PI/2;
}

double getGamma(Vector3D target) {
  // project the target onto the xy-plane
  target.z = 0;

  // get the angle between the projection and the y-axis
  double gamma = std::acos(target.y/target.norm());
  if (target.x < 0)
    return gamma;
  else
    return -gamma;
}
