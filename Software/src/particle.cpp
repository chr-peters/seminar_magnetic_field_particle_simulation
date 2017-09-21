#include "particle.h"

Particle::Particle(double time, double energy, double mass, double charge,
		   const Vector3D& location,
		   const Vector3D& momentum): time(time), energy(energy),
					      mass(mass), charge(charge),
					      location(location),
					      momentum(momentum) {
  //
}

std::ostream &operator<<(std::ostream &os, const Particle &p) {
  os << "{location: " << p.location << ", momentum: " << p.momentum <<
    ", mass: " << p.mass << ", charge: " << p.charge << ", energy: " << p.energy
     << ", time: " << p.time << "}";
}
