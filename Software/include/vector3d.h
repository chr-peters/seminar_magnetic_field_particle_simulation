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

  //TODO division operator
  
  /**
   * Scalar multiplication.
   */
  Vector3D& operator*=(double a);
  /**
   * Vector addition.
   */
  Vector3D& operator+=(const Vector3D &rhs);
  /**
   * Prints the vector to the desired outstream.
   */
  friend std::ostream &operator<<(std::ostream &os, const Vector3D& v);
  /**
   * Cross product.
   */
  friend Vector3D crossProduct(const Vector3D &a, const Vector3D &b);
  double x;
  double y;
  double z;
};

/**
 * Prints the vector to the desired outstream.
 */
std::ostream &operator<<(std::ostream &os, const Vector3D& v);

/**
 * Multiplication scalar - vector, vector - scalar and vector - vector
 */
Vector3D operator*(double a, const Vector3D &v);
Vector3D operator*(const Vector3D &v, double a);
double operator*(const Vector3D &lhs, const Vector3D &rhs);

Vector3D operator+(const Vector3D &lhs, const Vector3D &rhs);

/**
 * Cross product.
 */
Vector3D crossProduct(const Vector3D &a, const Vector3D &b);

#endif
