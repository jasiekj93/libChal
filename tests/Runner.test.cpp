/**
 * @file Runner.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include "MockHal.hpp"
#include <CppUTest/CommandLineTestRunner.h>

int main(int argc, char *argv[])
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}