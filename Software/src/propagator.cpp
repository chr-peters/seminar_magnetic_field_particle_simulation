#include "propagator.h"

#include<cmath>

const double PI = 4*atan(1);

std::vector<Particle> Propagator::getTrack(Particle particle, const Condition &stoppingCondition, double initialTimeStep) {
  std::vector<Particle> res;
  double startTime = 0;
  double timeStep = initialTimeStep;
  res.push_back(particle);

  while (!stoppingCondition.check(res)) {

    // get the magnetic field at the position of the particle
    Vector3D originalMagneticField = fieldDescriptor.getStrength(particle.location);
    // get the current momentum of the particle
    Vector3D originalInitialMomentum = particle.momentum;

    // transform the relevant vectors
    double alpha = getAlpha(originalMagneticField);
    double beta = getBeta(originalMagneticField);
    Vector3D magneticField = originalMagneticField.rotateXY(-beta, -alpha);
    Vector3D initialMomentum = originalInitialMomentum.rotateXY(-beta, -alpha);
    double gamma = getGamma(initialMomentum);
    initialMomentum = initialMomentum.rotateZ(-gamma);

    // in the new base, the current location of the particle is at the origin
    Vector3D curLocation;

    // get the radius of the circle
    double r = std::abs(initialMomentum.y / (particle.charge * magneticField.z));
    // get the angular velocity
    double w = std::abs(particle.charge * magneticField.z / particle.mass);
    // the angle the particle moves on the circle
    double phi = w * timeStep;

    // get the new position of the particle
    curLocation.z = initialMomentum.z * timeStep / particle.mass;
    curLocation.x = r * std::sin(phi) - r;
    curLocation.y = r * std::cos(phi);

    // transform the position back to where it was initially
    curLocation = curLocation.rotateZ(gamma).rotateYX(alpha, beta);
    
    particle.location.x += curLocation.x;
    particle.location.y += curLocation.y;
    particle.location.z += curLocation.z;

    // remove rounding errors before transforming back
    initialMomentum.x = 0;

    particle.momentum = initialMomentum.rotateZ(gamma+phi).rotateYX(alpha, beta);

    // update the time
    particle.time += timeStep;

    res.push_back(particle);
    startTime += timeStep;
  }

  return res;
}

std::vector<Vector3D> Propagator::getPoints(Particle particle, const Condition &stoppingCondition, double initialTimeStep) {
  std::vector<Vector3D> res;
  for (auto curParticle: this->getTrack(particle, stoppingCondition)) {
    res.push_back(curParticle.location);
  }
  return res;
}

std::vector<Vector3D> Propagator::getIntersectionPoints(Particle particle, const Plane3D& plane, const Condition &stoppingCondition, double initialTimeStep) {
  // the result
  std::vector<Vector3D> res;
  // first get the points
  std::vector<Vector3D> points = getPoints(particle, stoppingCondition);
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

double getAlpha(Vector3D target, double eps) {
  // project the target onto the xz-plane
  target.y = 0;

  if (target.norm() < eps) {
    return 0;
  }

  // get the angle between the projection and the z-axis
  double alpha = std::acos(target.z/target.norm());
  if (target.x < 0)
    return -alpha;
  else
    return alpha;
}

double getBeta(Vector3D target, double eps) {
  if (target.norm() < eps) {
    return 0;
  }
  
  if (target.y < 0)
    return PI/2 - std::acos(-target.y/target.norm());
  else
    return std::acos(target.y/target.norm()) - PI/2;
}

double getGamma(Vector3D target, double eps) {
  // project the target onto the xy-plane
  target.z = 0;

  if(target.norm() < eps) {
    return 0;
  }

  // get the angle between the projection and the y-axis
  double gamma = std::acos(target.y/target.norm());
  if (target.x < 0)
    return gamma;
  else
    return -gamma;
}
