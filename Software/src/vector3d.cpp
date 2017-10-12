#include "vector3d.h"
#include<cmath>

std::ostream &operator<<(std::ostream &os, const Vector3D& v) {
  os << v.x << " " << v.y << " " << v.z;
  return os;
}

Vector3D& Vector3D::operator+=(const Vector3D &rhs) {
  this->x+=rhs.x;
  this->y+=rhs.y;
  this->z+=rhs.z;
  return *this;
}

Vector3D operator+(const Vector3D &lhs, const Vector3D &rhs) {
  Vector3D res(lhs);
  res+=rhs;
  return res;
}

Vector3D operator-(const Vector3D &lhs, const Vector3D &rhs) {
  return lhs + (-1 * rhs);
}

Vector3D& Vector3D::operator*=(double a) {
  this->x*=a;
  this->y*=a;
  this->z*=a;
  return *this;
}

Vector3D operator*(double a, const Vector3D &v) {
  Vector3D res(v);
  res*=a;
  return res;
}

double operator*(const Vector3D &lhs, const Vector3D &rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3D operator*(const Vector3D &v, double a) {
  return a*v;
}

Vector3D crossProduct(const Vector3D &a, const Vector3D &b) {
  Vector3D res;
  res.x = a.y * b.z - a.z * b.y;
  res.y = a.z * b.x - a.x * b.z;
  res.z = a.x * b.y - a.y * b.x;
  return res;
}

Vector3D Vector3D::rotateXY(double alpha, double beta) {
  Vector3D res;
  
  // helper variables
  double a = std::sin(alpha);
  double b = std::cos(alpha);
  double c = std::sin(beta);
  double d = std::cos(beta);

  // carry out the transformation
  res.x = d*x + c*z;
  res.y = a*c*x + b*y - a*d*z;
  res.z = -b*c*x + a*y + b*d*z;

  return res;
}

Vector3D Vector3D::rotateYX(double alpha, double beta) {
  Vector3D res;
  
  // helper variables
  double a = std::sin(alpha);
  double b = std::cos(alpha);
  double c = std::sin(beta);
  double d = std::cos(beta);

  // carry out the transformation
  res.x = b*x + a*c*y + a*d*z;
  res.y = d*y - c*z;
  res.z = -a*x + b*c*y + b*d*z;

  return res;
}

Vector3D Vector3D::rotateZ(double alpha) {
  Vector3D res;
  
  // helper variables
  double a = std::sin(alpha);
  double b = std::cos(alpha);

  res.x = b*x - a*y;
  res.y = a*x + b*y;
  res.z = z;

  return res;
}
