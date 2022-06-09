#pragma once

/**
 * @file MockStream.hpp
 * @author Adrian Szczepanski
 * @date 09-06-2022
 * @brief 
 * @details
 */

#include <libChal/Hal.hpp>
#include <string.h>

namespace Mock
{
    class Stream : public Chal::IStream
    {
    public: 
        bool Init() override 
        { 
            if(Result == false)
                return false;

            InitalizeStatus = true;
            return true;
        }
        bool DeInit() override 
        {
            if(Result == false)
                return false;

            InitalizeStatus = false;
            return true;
        }

        bool IsInitalized() override { return InitalizeStatus; }

        bool Read(unsigned char *out, size_t size) override
        {
            if(ReadResult == false)
                return false;

            if(size > sizeof(Buffer))
                return false;

            memcpy(out, Buffer, size);    
            return true;
        } 

        size_t GetReadCount() const { return ReadCount; }

        bool IsEndOfFile() const override { return EndOfFile; }
        bool IsError() const override { return Error; }
        void ClearErrors() override { EndOfFile = Error = false; }

        bool Result = true;
        bool InitalizeStatus = false;
        bool Error = false;
        bool EndOfFile = false;
        bool ReadResult = true;
        unsigned char Buffer[1024];
        size_t ReadCount = 0;
    };
}
