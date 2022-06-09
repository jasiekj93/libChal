/**
 * @file Time.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <time.h>
#include <string.h>
#include "MockHal.hpp"
#include <CppUTest/CommandLineTestRunner.h>

TEST_GROUP(TimeTest)
{
    Mock::Hal *hal;

    void setup()
    {
        hal = new Mock::Hal();
        Chal::SetHal(hal);
    }

    void teardown()
    {
        Chal::SetHal(nullptr);
        delete hal;
    }
};

TEST(TimeTest, Clock)
{
    clock_t expected = 500;

    Mock::Hal::Clock = expected;

    CHECK_EQUAL(expected, clock());
}

TEST(TimeTest, Clock_NoHal)
{
    clock_t expected = -1;
    Chal::SetHal(nullptr);

    CHECK_EQUAL(expected, clock());
}

TEST(TimeTest, Time)
{
    time_t expected = 500;

    Mock::Hal::Time = expected;

    time_t result;
    time(&result);

    CHECK(expected == result);
}

TEST(TimeTest, Time_NoHal)
{
    time_t expected = -1;
    Chal::SetHal(nullptr);

    time_t result;
    time(&result);

    CHECK(expected == result);
}

TEST(TimeTest, Ctime)
{
    time_t seconds = 0;
    const char *expected = "Thu Jan  1 01:00:00 1970\n"; //UTC+1
    auto result = ctime(&seconds);

    MEMCMP_EQUAL(expected, result, strlen(expected));
}