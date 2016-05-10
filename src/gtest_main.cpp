#include
#include "gtest/gtest.h"

GTEST_API_int main(int argc, char **argv) {
printf("Running main() from gtest_main.cc\n");
testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}
