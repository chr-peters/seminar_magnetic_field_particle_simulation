#include "propagator.h"

std::vector<Vector3D> Propagator::getPoints(Particle particle, double simulationTime) {
  std:: vector<Vector3D> res;
  double timeStep = simulationTime / 100;
  double startTime = 0;
  while (startTime <= simulationTime) {
    res.push_back(particle.location);
    particle.location.x+=0.1;
    particle.location.y+=0.1;
    particle.location.z+=0.1;
    startTime += timeStep;
  }
  return res;
}
