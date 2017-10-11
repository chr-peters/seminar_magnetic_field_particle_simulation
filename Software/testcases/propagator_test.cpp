#include "gtest/gtest.h"

#include "propagator.h"

TEST(PropagatorTest, TestHomogeneousField) {
  ASSERT_EQ(1, 1);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
