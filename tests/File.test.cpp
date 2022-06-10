/**
 * @file File.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <libChal/Stdio.hpp>
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

TEST(FileTest, Fopen_Function)
{
    auto file = Chal::fopen("name", "not important");
    CHECK((Mock::Stream *)file == stream);
    CHECK(stream->InitalizeStatus);

    Mock::Hal::Stream = nullptr;
    file = Chal::fopen("a", "");
    CHECK(file == nullptr);

    Chal::SetHal(nullptr);
    Mock::Hal::Stream = stream;
    file = Chal::fopen("b", "");
    CHECK(file == nullptr);
}

TEST(FileTest, Fclose_Function)
{
    auto file = Chal::fopen("name", "not important");
    CHECK(stream->InitalizeStatus);

    auto result = Chal::fclose(nullptr);
    CHECK(EOF == result);

    result = Chal::fclose(file);
    CHECK_EQUAL(0, result);
    CHECK_FALSE(stream->InitalizeStatus);
}

TEST(FileTest, Freopen_Function)
{
    auto file = Chal::fopen("name", "not important");
    auto secondFile = Chal::freopen("a", "", file);

    CHECK(file == secondFile);
}

TEST(FileTest, Fread_Function)
{
    size_t count = 10;
    char data[128];
    char buffer[128];
    memset(data, 5, count);
    stream->Append((unsigned char *)data, count);

    auto file = Chal::fopen("", "");
    auto result = Chal::fread(buffer, sizeof(char), count, file);

    CHECK_EQUAL(count, result); 
    MEMCMP_EQUAL(data, buffer, count);
}

TEST(FileTest, Fwrite_Function)
{
    size_t count = 10;
    char data[128];
    memset(data, 5, count);

    auto file = Chal::fopen("", "");
    auto result = Chal::fwrite(data, sizeof(char), count, file);

    CHECK_EQUAL(count, result); 
    MEMCMP_EQUAL(data, stream->WriteBuffer, count);
}

TEST(FileTest, Setbuf_Function)
{
    char buffer[BUFSIZ];

    auto file = Chal::fopen("", "");
    Chal::setbuf(file, buffer);

    CHECK_EQUAL(buffer, stream->Buffer()); 
}