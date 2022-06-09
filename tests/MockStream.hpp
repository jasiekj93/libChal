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
    class Stream : public Chal::SerialStream
    {
    public: 
        Stream(size_t size) : Chal::SerialStream(size)
        {
            WriteBuffer = new unsigned char[size];
        }

        ~Stream()
        {
            delete[] WriteBuffer;
        }

        bool Open() override 
        { 
            if(Result == false)
                return false;

            InitalizeStatus = true;
            return true;
        }
        bool Close() override 
        {
            if(Result == false)
                return false;

            InitalizeStatus = false;
            return true;
        }

        bool Write(const unsigned char *data, size_t size) override
        {
            if(Result == false)
                return false;

            if(size > _buffer.Size)
                return false;

            memcpy(WriteBuffer, data, size);
            return true;
        }

        auto & GetBuffer() { return _buffer; }
        
        bool Result = true;
        bool InitalizeStatus = false;
        unsigned char *WriteBuffer;
    };
}
