#include <iostream>

#include <gtest/gtest.h>

int sampleTest(int a)
{
    return a*a;
}

TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(4, sampleTest(2));
    
}

using namespace std;

int test_main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}