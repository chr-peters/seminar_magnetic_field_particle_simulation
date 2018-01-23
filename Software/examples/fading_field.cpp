#include "plot.h"

#include "particle.h"
#include "vector3d.h"
#include "fields.h"
#include "propagator.h"
#include "plane3d.h"
#include "conditions.h"

#include<vector>
#include<iostream>

class FadingField: public FieldDescriptor {
public:
  FadingField(Vector3D strength):strength(strength) {}
  Vector3D getStrength(const Vector3D &location) const override {
    static Vector3D tmpStrength(strength);
    tmpStrength*=0.999;
    return tmpStrength;
  }
private:
  Vector3D strength;
};

int main () {
  // initiate the particle
  Vector3D momentum(2, 2, 0);
  Vector3D location(1, 1, 1);
  Particle particle(0, 1, 1, 0.5, location, momentum);

  // initiate the magnetic field
  Vector3D fieldStrength(0.075, 0, 0);
  FadingField field(fieldStrength);

  // propagate the particle through the field
  Propagator propagator(field);
  std::vector<Vector3D> points = propagator.getPoints(particle, MaximumDistanceCondition(4000, location), 2.5);
  plot("Two Homogeneous Fields Example", points);
}
