#include "vector3d.h"
#include "particle.h"
#include "fields.h"
#include "propagator.h"

#include <iostream>
#include <vector>

using namespace std;

int main () {
  Vector3D velocity(1, 1, 1);
  Vector3D location(0, 0, 0);
  Particle particle(0, 1, 2, 3.5, location, velocity);

  Vector3D fieldStrength(0, 0, 0);
  HomogenousField field(fieldStrength);
  Propagator propagator(field);
  vector<Vector3D> points = propagator.getPoints(particle, 100);

  for (auto p: points) {
    cout << p << ", ";
  }
  cout << endl;
}
