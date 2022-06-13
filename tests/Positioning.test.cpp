
/**
 * @file Positioning.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <libChal/Stdio.hpp>
#include "MockHal.hpp"
#include "MockStream.hpp"
#include <CppUTest/CommandLineTestRunner.h>

TEST_GROUP(PositioningTest)
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

TEST(PositioningTest, Fgetpos_Method)
{
    size_t offset = 5;
    stream->Offset = offset;
    Chal::fpos_t result;

    auto file = Chal::fopen("","");
    auto status = Chal::fgetpos(file, &result);

    CHECK_EQUAL(0, status);
    CHECK_EQUAL(offset, result);
}

TEST(PositioningTest, Fsetpos_Method)
{
    Chal::fpos_t offset = 5;

    auto file = Chal::fopen("","");
    auto status = Chal::fsetpos(file, &offset);

    CHECK_EQUAL(0, status);
    CHECK_EQUAL(offset, stream->Offset);
}

TEST(PositioningTest, Ftell_Method)
{
    Chal::fpos_t offset = 5;
    stream->Offset = offset;

    auto file = Chal::fopen("","");
    auto result = Chal::ftell(file);

    CHECK_EQUAL(result, offset);
}

TEST(PositioningTest, Rewind_Method)
{
    Chal::fpos_t offset = 5;
    stream->Offset = offset;

    auto file = Chal::fopen("","");
    Chal::rewind(file);

    CHECK_EQUAL(0, stream->Offset);
}

TEST(PositioningTest, Fseek_Method)
{
    Chal::fpos_t offset = 5;
    Chal::fpos_t begining = 15;
    stream->Offset = begining;

    auto file = Chal::fopen("","");
    auto result = Chal::fseek(file, offset, SEEK_CUR);

    CHECK_EQUAL(0, result);
    CHECK_EQUAL(begining + offset, stream->Offset);

    result = Chal::fseek(file, offset, SEEK_SET);

    CHECK_EQUAL(0, result);
    CHECK_EQUAL(offset, stream->Offset);

    result = Chal::fseek(file, offset, 4213742);
    CHECK_EQUAL(-1, result);
}