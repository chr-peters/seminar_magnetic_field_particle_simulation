#if !defined(FIELDS_H)
#define FIELDS_H

#include "vector3d.h"

class FieldDescriptor {
public:
  virtual Vector3D getStrength(const Vector3D &location) const =0;
};

class HomogenousField: public FieldDescriptor {
public:
  HomogenousField(const Vector3D &strength): strength(strength) {}
  Vector3D getStrength(const Vector3D &location) const override {
    return strength;
  }
private:
  Vector3D strength;
};

#endif
