/**
 * @file Formatted.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <libChal/Stdio.hpp>
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

TEST(FormattedTest, Fprintf_Function)
{
    const char expected[] = "My Dog is 5 years old."; 
    const char format[] = "My %s is %d years old.";
    int number = 5;
    const char dog[] = "Dog";

    auto file = Chal::fopen("", "");
    auto result = Chal::fprintf(file, format, dog, number);

    STRCMP_EQUAL(expected, (char *)stream->WriteBuffer);
}

TEST(FormattedTest, Printf_Function)
{
    const char expected[] = "My Dog is 5 years old."; 
    const char format[] = "My %s is %d years old.";
    int number = 5;
    const char dog[] = "Dog";

    auto result = Chal::printf(format, dog, number);

    STRCMP_EQUAL(expected, (char *)stream->WriteBuffer);
}

TEST(FormattedTest, Fscanf_Function)
{
    int expectedNumber = 5;
    const char *expectedString = "Dog";
    char buffer[128];
    int number;
    const char text[] = "My Dog is 5 years old."; 
    const char format[] = "My %s is %d years old.";
    stream->Append((unsigned char *)text, strlen(text));

    auto file = Chal::fopen("", "");
    auto result = Chal::fscanf(file, format, buffer, &number);

    CHECK_EQUAL(2, result);
    CHECK_EQUAL(expectedNumber, number);
    MEMCMP_EQUAL(expectedString, buffer, strlen(expectedString));
}

TEST(FormattedTest, Scanf_Function)
{
    int expectedNumber = 5;
    const char *expectedString = "Dog";
    char buffer[128];
    int number;
    const char text[] = "My Dog is 5 years old."; 
    const char format[] = "My %s is %d years old.";
    stream->Append((unsigned char *)text, strlen(text));

    auto result = Chal::scanf(format, buffer, &number);

    CHECK_EQUAL(2, result);
    CHECK_EQUAL(expectedNumber, number);
    MEMCMP_EQUAL(expectedString, buffer, strlen(expectedString));
}