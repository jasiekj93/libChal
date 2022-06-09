#pragma once

/**
 * @file IHal.hpp
 * @author Adrian Szczepanski
 * @date 07-06-2022
 * @brief 
 * @details
 */

#include <time.h>

//TODO
// typedef  FILE;

namespace Chal
{
    static constexpr size_t ReceiveBufferSize = 256;

    class IHal
    {
    public:
        virtual ~IHal() {}

        virtual clock_t GetClock() = 0;
        virtual time_t GetTime() = 0;

        virtual void Transmit(unsigned char *, size_t) = 0;

        virtual void DisableInterrupts() = 0;
        virtual void EnableInterrupts() = 0;
    };

    void ReceiveCallback(const unsigned char *, size_t);
    size_t ReadReceivedData(unsigned char *, size_t max);
    size_t ReadString(unsigned char *, size_t max);

    void SetHal(IHal *);
    IHal * GetHal();
}