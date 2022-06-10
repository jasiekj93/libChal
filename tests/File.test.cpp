/**
 * @file File.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <stdio.h>
#include "MockHal.hpp"
#include "MockStream.hpp"
#include <CppUTest/CommandLineTestRunner.h>

TEST_GROUP(FileTest)
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

TEST(FileTest, Fopen)
{
    auto file = fopen("name", "not important");
    CHECK((Mock::Stream *)file == stream);
    CHECK(stream->InitalizeStatus);

    Mock::Hal::Stream = nullptr;
    file = fopen("a", "");
    CHECK(file == nullptr);

    Chal::SetHal(nullptr);
    Mock::Hal::Stream = stream;
    file = fopen("b", "");
    CHECK(file == nullptr);
}

TEST(FileTest, Fclose)
{
    auto file = fopen("name", "not important");
    CHECK(stream->InitalizeStatus);

    auto result = fclose(nullptr);
    CHECK(EOF == result);

    result = fclose(file);
    CHECK_EQUAL(0, result);
    CHECK_FALSE(stream->InitalizeStatus);
}

TEST(FileTest, Freopen)
{
    auto file = fopen("name", "not important");
    auto secondFile = freopen("a", "", file);

    CHECK(file == secondFile);
}

TEST(FileTest, Fread)
{
    size_t count = 10;
    char data[128];
    char buffer[128];
    memset(data, 5, count);
    stream->Append((unsigned char *)data, count);

    auto file = fopen("", "");
    auto result = fread(buffer, sizeof(char), count, file);

    CHECK_EQUAL(count, result); 
    MEMCMP_EQUAL(data, buffer, count);
}

TEST(FileTest, Fwrite)
{
    size_t count = 10;
    char data[128];
    memset(data, 5, count);

    auto file = fopen("", "");
    auto result = fwrite(data, sizeof(char), count, file);

    CHECK_EQUAL(count, result); 
    MEMCMP_EQUAL(data, stream->WriteBuffer, count);
}