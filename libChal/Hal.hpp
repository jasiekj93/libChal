#pragma once

/**
 * @file IHal.hpp
 * @author Adrian Szczepanski
 * @date 07-06-2022
 * @brief 
 * @details
 */

#include <time.h>

namespace Chal
{
    class IStream
    {
    public:
        virtual ~IStream() {}

        virtual bool Init() = 0;
        virtual bool DeInit() = 0;
        virtual bool IsInitalized() = 0;

        virtual bool Read(unsigned char *out, size_t size) = 0;
        virtual size_t GetReadCount() const = 0;

        //Set EoF if Read method returned false;
        virtual bool IsEndOfFile() const = 0; 
        virtual bool IsError() const = 0;
        virtual void ClearErrors() = 0;
    };

    class IHal
    {
    public:
        virtual ~IHal() {}

        virtual clock_t GetClock() = 0;
        virtual time_t GetTime() = 0;

        virtual IStream * GetStream(const char *) = 0;
    };

    void SetHal(IHal *);
    IHal * GetHal();
}