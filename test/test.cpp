#include <iostream>
#include "../src/CommandProcess.h"
#include <gtest/gtest.h>

cCommandProcess command;

TEST(cCommandProcess, ShowCommand)
{
    ASSERT_TRUE(command.Init());
    ASSERT_NO_FATAL_FAILURE(command.ShowCommands());
}

TEST(cCommandProcess, ValidateInputData)
{
    ASSERT_FALSE(command.ValidateInputData(command.GetArraySize() + 1));
    ASSERT_FALSE(command.ValidateInputData(-1));
    ASSERT_TRUE(command.ValidateInputData(command.GetArraySize()));
}

TEST(cCommandProcess, ExecCommand)
{
    ASSERT_NO_FATAL_FAILURE(command.ExecCommand(command.GetArraySize()));
//    ASSERT_ANY_THROW(command.ExecCommand(command.GetArraySize()));
}

using namespace std;

int test_main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}