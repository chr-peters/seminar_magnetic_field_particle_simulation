#include "gtest/gtest.h"

#include<cmath>
#include<iostream>

#include "vector3d.h"

const double PI = 4 * std::atan(1);

TEST(Vector3DTest, TestRotateXY) {
  Vector3D testVector(1, 1, 1);
  Vector3D result = testVector.rotateXY(-0.61547970867, -3.92699081699);
  ASSERT_NEAR(result.x, 0, 1e-6);
  ASSERT_NEAR(result.y, 0, 1e-6);
  ASSERT_NEAR(result.z, -1.73205, 1e-6);
}

TEST(Vector3DTest, TestRotateXYPI) {
  Vector3D testVector(0, 0, 1);
  Vector3D result = testVector.rotateXY(PI, 0);
  ASSERT_NEAR(result.x, 0, 1e-6);
  ASSERT_NEAR(result.y, 0, 1e-6);
  ASSERT_NEAR(result.z, -1, 1e-6);
}

TEST(Vector3DTest, TestRotateYXPI) {
  Vector3D testVector(0, 0, -1);
  Vector3D result = testVector.rotateYX(0, -PI);
  ASSERT_NEAR(result.x, 0, 1e-6);
  ASSERT_NEAR(result.y, 0, 1e-6);
  ASSERT_NEAR(result.z, 1, 1e-6);
}

TEST(Vector3DTest, TestRotateYX) {
  Vector3D testVector(0, 0, 1);
  Vector3D result = testVector.rotateYX(-PI/2, -PI/2);
  ASSERT_NEAR(result.x, 0, 1e-6);
  ASSERT_NEAR(result.y, 1, 1e-6);
  ASSERT_NEAR(result.z, 0, 1e-6);
}

TEST(Vector3DTest, TestRotateZ) {
  Vector3D testVector(1, 0, 1);
  Vector3D result = testVector.rotateZ(PI/4);
  ASSERT_NEAR(result.x, 0.7071068, 1e-6);
  ASSERT_NEAR(result.y, 0.7071068, 1e-6);
  ASSERT_NEAR(result.z, 1, 1e-6);
}

TEST(Vector3DTest, TestRotateBoth) {
  Vector3D testVector(0, 0, 1);
  Vector3D result = testVector.rotateXY(1, 2).rotateYX(-2, -1);
  ASSERT_NEAR(result.x, 0, 1e-6);
  ASSERT_NEAR(result.y, 0, 1e-6);
  ASSERT_NEAR(result.z, 1, 1e-6);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
