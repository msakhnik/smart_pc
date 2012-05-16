#include <iostream>
#include "../src/HandDetector.h"
#include <gtest/gtest.h>

HandDetector detector;

TEST(AsfFileTest, ReadFrame)
{
    ASSERT_TRUE(detector.Start());
}

using namespace std;

int test_main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}