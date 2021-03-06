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

        Chal::Stream * GetStream(const char *) override { return Stream; } 
        Chal::Stream * GetStdin() override { return Stream; } 
        Chal::Stream * GetStout() override { return Stream; } 
        Chal::Stream * GetStderr() override { return Stream; } 
    
        static clock_t Clock;
        static time_t Time;
        static Chal::Stream *Stream;
    };
}