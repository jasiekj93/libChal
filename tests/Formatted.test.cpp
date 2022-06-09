/**
 * @file Formatted.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <stdio.h>
#include "MockHal.hpp"
#include "MockStream.hpp"
#include <CppUTest/CommandLineTestRunner.h>

TEST_GROUP(FormattedTest)
{
    Mock::Hal *hal;
    Mock::Stream *stream;

    void setup()
    {
        hal = new Mock::Hal();
        stream = new Mock::Stream(128);
        Chal::SetHal(hal);
        Mock::Hal::Stream = stream;
    }

    void teardown()
    {
        Chal::SetHal(nullptr);
        Mock::Hal::Stream = nullptr;
        delete stream;
        delete hal;
    }
};

TEST(FormattedTest, Fprintf)
{
    const char expected[] = "My Dog is 5 years old."; 
    const char format[] = "My %s is %d years old.";
    int number = 5;
    const char dog[] = "Dog";

    auto file = fopen("", "");
    auto result = fprintf(file, format, dog, number);

    STRCMP_EQUAL(expected, (char *)stream->WriteBuffer);
}

TEST(FormattedTest, Printf)
{
    const char expected[] = "My Dog is 5 years old."; 
    const char format[] = "My %s is %d years old.";
    int number = 5;
    const char dog[] = "Dog";

    auto result = printf(format, dog, number);

    STRCMP_EQUAL(expected, (char *)stream->WriteBuffer);
}