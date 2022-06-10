#include "Stream.hpp"
#include <string.h>

using namespace Chal;

Stream::Stream()
    : _endOfFile(false)
    , _error(false)
{   
}

bool Stream::Write(const unsigned char *data, size_t size)
{
    auto result = _Write(data, size);

    if(result == true)
        _writeAddress += size;
    else
        _endOfFile = true;

    return result;
}

bool Stream::Read(unsigned char *data, size_t size)
{
    auto result = _Read(data, size);

    if(result == true)
        _readAddress += size;
    else
        _endOfFile = true;
    
    return result;
}

size_t Stream::ReadUpTo(unsigned char *data, size_t size)
{
    auto result = _ReadUpTo(data, size);

    _readAddress += result;

    if(result < size)
        _endOfFile = true;

    return result;
}

void Stream::ClearErrors()
{
    _error = false;
    _endOfFile = false;
}

SerialStream::SerialStream(size_t size)
    : Stream()
    , _buffer(size)
    , _bufferLock(false)
{
}

bool SerialStream::_Read(unsigned char *out, size_t size)
{
    if(out == nullptr)
    {
        _error = true;
        return false;
    }
    
    _bufferLock = true;

    if(size > _buffer.Count())
    {
        _endOfFile = true;
        _bufferLock = false;
        return false;
    }

    for(auto i = 0; i < size; i++)
        out[i] = _buffer.Get();

    _bufferLock = false;
    return true;
}

size_t SerialStream::_ReadUpTo(unsigned char *out, size_t max)
{
    if(out == nullptr)
    {
        _error = true;
        return 0;
    }
    
    _bufferLock = true;

    size_t result = 0;

    while((result < max) && (_buffer.IsEmpty() == false))
        out[result++] = _buffer.Get();

    _bufferLock = false;
    return result;
}

bool SerialStream::_ReceivedDataCallback(const unsigned char *data, size_t size)
{
    if(_bufferLock == true)
        return false;

    _buffer.Put(data, size);
    return true;
}