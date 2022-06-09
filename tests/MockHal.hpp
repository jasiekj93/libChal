#pragma once

/**
 * @file MockHal.hpp
 * @author Adrian Szczepanski
 * @date 09-06-2022
 * @brief 
 * @details
 */

#include <libChal/Hal.hpp>

namespace Mock
{
    class Hal : public Chal::IHal
    {
    public:
        clock_t GetClock() override { return Clock; }
        time_t GetTime() override { return Time; }

        Chal::IStream * GetStream(const char *) override { return Stream; } 
    
        static clock_t Clock;
        static time_t Time;
        static Chal::IStream *Stream;
    };
}