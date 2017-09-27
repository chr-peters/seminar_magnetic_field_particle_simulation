#include "vector3d.h"

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

Vector3D& Vector3D::operator*=(float a) {
  this->x*=a;
  this->y*=a;
  this->z*=a;
  return *this;
}

Vector3D operator*(float a, const Vector3D &v) {
  Vector3D res(v);
  res*=a;
  return res;
}

Vector3D operator*(const Vector3D &v, float a) {
  return a*v;
}

Vector3D crossProduct(const Vector3D &a, const Vector3D &b) {
  Vector3D res;
  res.x = a.y * b.z - a.z * b.y;
  res.y = a.z * b.x - a.x * b.z;
  res.z = a.x * b.y - a.y * b.x;
  return res;
}
