#if !defined(PLANE3D_H)
#define PLANE3D_H

#include "vector3d.h"

class Plane3D {
public:
  Plane3D(const Vector3D &pointInPlane, const Vector3D &normalVector): pointInPlane(pointInPlane), normalVector(normalVector) {}
  inline Vector3D getPointInPlane() const { return pointInPlane; }
  inline Vector3D getNormalVector() const { return normalVector; }
private:
  Vector3D pointInPlane;
  Vector3D normalVector;
};

#endif
