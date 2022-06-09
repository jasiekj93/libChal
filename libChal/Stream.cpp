#include "Stream.hpp"
#include <string.h>

using namespace Chal;

Stream::Stream()
    : _endOfFile(false)
    , _error(false)
{   
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

bool SerialStream::Read(unsigned char *out, size_t size)
{
    if(out == nullptr)
    {
        _error = true;
        return false;
    }
    
    _bufferLock = true;

    if(size > Count())
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

