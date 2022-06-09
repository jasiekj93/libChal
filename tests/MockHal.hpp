#pragma once

#include <libChal/Hal.hpp>

namespace Mock
{
    class Hal : public Chal::IHal
    {
    public:
        clock_t GetClock() override { return Clock; }
        time_t GetTime() override { return Time; }

        void Transmit(unsigned char *, size_t) override {}

        void DisableInterrupts() override {}
        void EnableInterrupts() override {}
    
        static clock_t Clock;
        static time_t Time;
    };
}