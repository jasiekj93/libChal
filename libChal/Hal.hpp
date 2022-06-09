#pragma once

/**
 * @file IHal.hpp
 * @author Adrian Szczepanski
 * @date 07-06-2022
 * @brief 
 * @details
 */

#include <time.h>
#include <libChal/Stream.hpp>

namespace Chal
{
    class IHal
    {
    public:
        virtual ~IHal() {}

        virtual clock_t GetClock() = 0;
        virtual time_t GetTime() = 0;

        virtual Stream * GetStream(const char *) = 0;
    };

    void SetHal(IHal *);
    IHal * GetHal();
}