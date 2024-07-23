#include "test.hpp"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  // sleep(10000);
  return RUN_ALL_TESTS();
}