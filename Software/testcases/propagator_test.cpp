#include "gtest/gtest.h"

#include "propagator.h"
#include "vector3d.h"

TEST(PropagatorTest, TestGetAlphaPositive) {
  Vector3D testVector(1, 1, 1);
  Vector3D zAxis(0, 0, 1);
  double alpha = getAlpha(testVector);
  Vector3D result = zAxis.rotateYX(alpha, 0);
  ASSERT_NEAR(result.x, 0.7071068, 1e-6);
  ASSERT_NEAR(result.y, 0, 1e-6);
  ASSERT_NEAR(result.z, 0.7071068, 1e-6);
}

TEST(PropagatorTest, TestGetAlphaNegative) {
  Vector3D testVector(-1, 1, 1);
  Vector3D zAxis(0, 0, 1);
  double alpha = getAlpha(testVector);
  Vector3D result = zAxis.rotateYX(alpha, 0);
  ASSERT_NEAR(result.x, -0.7071068, 1e-6);
  ASSERT_NEAR(result.y, 0, 1e-6);
  ASSERT_NEAR(result.z, 0.7071068, 1e-6);
}

TEST(PropagatorTest, TestGetBetaPositive) {
  Vector3D testVector(0, 1, 1);
  Vector3D zAxis(0, 0, 1);
  double beta = getBeta(testVector);
  Vector3D result = zAxis.rotateYX(0, beta);
  ASSERT_NEAR(result.x, 0, 1e-6);
  ASSERT_NEAR(result.y, 0.7071068, 1e-6);
  ASSERT_NEAR(result.z, 0.7071068, 1e-6);
}

TEST(PropagatorTest, TestGetBetaNegative) {
  Vector3D testVector(0, -1, 1);
  Vector3D zAxis(0, 0, 1);
  double beta = getBeta(testVector);
  Vector3D result = zAxis.rotateYX(0, beta);
  ASSERT_NEAR(result.x, 0, 1e-6);
  ASSERT_NEAR(result.y, -0.7071068, 1e-6);
  ASSERT_NEAR(result.z, 0.7071068, 1e-6);
}

TEST(PropagatorTest, TestGetAlphaBeta) {
  Vector3D testVector(1, 1, 1);
  Vector3D zAxis(0, 0, 1);
  double alpha = getAlpha(testVector);
  double beta = getBeta(testVector);
  Vector3D result = zAxis.rotateYX(alpha, beta);
  ASSERT_NEAR(result.x, 0.577350, 1e-6);
  ASSERT_NEAR(result.y, 0.577350, 1e-6);
  ASSERT_NEAR(result.z, 0.577350, 1e-6);
}

TEST(PropagatorTest, TestGetAlphaBetaBackwards) {
  Vector3D testVector(1, 1, 1);
  Vector3D zAxis(0, 0, 1);
  double alpha = getAlpha(testVector);
  double beta = getBeta(testVector);
  Vector3D result = testVector.rotateXY(-beta, -alpha);
  ASSERT_NEAR(result.x, 0, 1e-6);
  ASSERT_NEAR(result.y, 0, 1e-6);
  ASSERT_NEAR(result.z, 1.7320508, 1e-6);
}

TEST(PropagatorTest, TestGetGamma) {
  Vector3D testVector(1, 1, 1);
  Vector3D yAxis(0, 1, 0);
  double gamma = getGamma(testVector);
  Vector3D result = yAxis.rotateZ(gamma);
  ASSERT_NEAR(result.x, 0.7071068, 1e-6);
  ASSERT_NEAR(result.y, 0.7071068, 1e-6);
  ASSERT_NEAR(result.z, 0, 1e-6);
}

TEST(PropagatorTest, TestGetGammaNegative) {
  Vector3D testVector(-1, 1, 1);
  Vector3D yAxis(0, 1, 0);
  double gamma = getGamma(testVector);
  Vector3D result = yAxis.rotateZ(gamma);
  ASSERT_NEAR(result.x, -0.7071068, 1e-6);
  ASSERT_NEAR(result.y, 0.7071068, 1e-6);
  ASSERT_NEAR(result.z, 0, 1e-6);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
