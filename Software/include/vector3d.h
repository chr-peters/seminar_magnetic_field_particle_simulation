#if !defined(VECTOR3D_H)
#define VECTOR3D_H

#include<iostream>

class Vector3D {
public:
  Vector3D(double x, double y, double z): x(x), y(y), z(z) {}
  Vector3D(const Vector3D &v): x(v.x), y(v.y), z(v.z){}
  /**
   * Creates the null vector.
   */
  Vector3D(): x(0), y(0), z(0) {}
  /**
   * Prints the vector to the desired outstream.
   */
  friend std::ostream &operator<<(std::ostream &os, const Vector3D& v);
  double x;
  double y;
  double z;
};

/**
 * Prints the vector to the desired outstream.
 */
std::ostream &operator<<(std::ostream &os, const Vector3D& v);

#endif
