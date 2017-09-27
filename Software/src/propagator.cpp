#include "propagator.h"

std::vector<Vector3D> Propagator::getPoints(Particle &particle, double simulationTime) {
  std:: vector<Vector3D> res;
  double timeStep = simulationTime / 3000;
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
