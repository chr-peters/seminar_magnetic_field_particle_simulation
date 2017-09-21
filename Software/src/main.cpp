#include "vector3d.h"
#include "particle.h"
#include "fields.h"

#include <iostream>

using namespace std;

int main () {
  Vector3D velocity(1, 1, 1);
  cout << velocity << endl;
  Vector3D location(2, 3, 4);
  Particle p(0, 1, 2, 3.5, location, velocity);
  cout << p << endl;
}
