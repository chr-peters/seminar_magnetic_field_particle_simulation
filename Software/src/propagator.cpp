#include "propagator.h"

std::vector<Vector3D> Propagator::getPoints(Particle &particle, double simulationTime) {
  std::vector<Vector3D> res;
  double timeStep = simulationTime / 1000;
  double startTime = 0;
  res.push_back(particle.location);
  while (startTime <= simulationTime) {
    // get the magnetic field at the position of the particle
    Vector3D magneticField = fieldDescriptor.getStrength(particle.location);
    // get the current momentum of the particle
    Vector3D initialMomentum = particle.momentum;
    // get the update of the momentum by calculating the lorentz force
    Vector3D momentumUpdate = particle.charge * crossProduct(initialMomentum, magneticField) * (timeStep / particle.mass);
    // get the update of the location
    Vector3D locationUpdate = initialMomentum * (timeStep/particle.mass) +  momentumUpdate * (timeStep/particle.mass);
    // update the parameters of the particle
    particle.location += locationUpdate;
    particle.momentum += momentumUpdate;
    particle.time += timeStep;
    
    startTime += timeStep;
    res.push_back(particle.location);
  }
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
