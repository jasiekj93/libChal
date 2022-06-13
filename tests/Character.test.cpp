/**
 * @file Character.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <libChal/Stdio.hpp>
#include "MockHal.hpp"
#include "MockStream.hpp"
#include <CppUTest/CommandLineTestRunner.h>

TEST_GROUP(CharacterTest)
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

TEST(CharacterTest, Fputc_Method)
{
    auto file = Chal::fopen("name", "");
    char digit = 5;

    Chal::fputc(digit, file);

    CHECK_EQUAL(digit, stream->WriteBuffer[0]);
}

TEST(CharacterTest, Fputs_Method)
{
    auto file = Chal::fopen("name", "");
    char string[] = "Hello";

    auto count = Chal::fputs(string, file);

    CHECK_EQUAL(strlen(string), count);
    MEMCMP_EQUAL(string, stream->WriteBuffer, strlen(string));
}

TEST(CharacterTest, Puts_Method)
{
    const char string[] = "Hello";
    const char expected[] = "Hello\r\n";

    auto count = Chal::puts(string);

    CHECK_EQUAL(strlen(expected), count);
    MEMCMP_EQUAL(expected, stream->WriteBuffer, strlen(expected));
}

TEST(CharacterTest, Fgetc_Method)
{
    char digit = 5;
    auto file = Chal::fopen("", "");
    stream->Append((unsigned char *)&digit, sizeof(char));

    auto result = Chal::fgetc(file);

    CHECK_EQUAL(digit, result);
}

TEST(CharacterTest, Getc_Method)
{
    char digit = 5;
    stream->Append((unsigned char *)&digit, sizeof(char));

    auto result = Chal::getc();

    CHECK_EQUAL(digit, result);
}

TEST(CharacterTest, Fgets_Method)
{
    const char string[] = "Hello";
    stream->Append((const unsigned char *)string, strlen(string));
    auto file = Chal::fopen("", "");
    char output[128];

    auto result = Chal::fgets(output, sizeof(output), file);

    CHECK(result == output);
    MEMCMP_EQUAL(string, output, strlen(string) + 1);
}

TEST(CharacterTest, Fgets_OneLine)
{
    const char string[] = "Hello\r\nWorld!";
    const char expected[] = "Hello\r\n";
    stream->Append((const unsigned char *)string, strlen(string));
    auto file = Chal::fopen("", "");
    char output[128];

    auto result = Chal::fgets(output, sizeof(output), file);

    CHECK(result == output);
    MEMCMP_EQUAL(expected, output, strlen(expected) + 1);
}

TEST(CharacterTest, Fgets_IsEmpty)
{
    auto file = Chal::fopen("", "");
    char output[128];

    auto result = Chal::fgets(output, sizeof(output), file);

    CHECK(result == nullptr);
    CHECK(stream->EndOfFile());
}

TEST(CharacterTest, Gets_OneLine)
{
    const char string[] = "Hello\r\nWorld!";
    const char expected[] = "Hello\r";
    stream->Append((const unsigned char *)string, strlen(string));
    char output[128];

    auto result = Chal::gets(output);

    CHECK(result == output);
    MEMCMP_EQUAL(expected, output, strlen(expected) + 1);
}