#include "Stream.hpp"
#include <string.h>

using namespace Chal;

Stream::Stream(size_t size)
    : _endOfFile(false)
    , _error(false)
    , _readAddress(0)
    , _writeAddress(0)
    , _size(size)
    , _buffer(new char[size])
    , _isBufferToDelete(true)
{   
}

Stream::~Stream()
{
    if(_isBufferToDelete)
        delete[] _buffer;
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

void Stream::SetBuffer(char *pointer, size_t size)
{
    if(pointer == nullptr)
    {
        if(_isBufferToDelete)
            delete[] _buffer;

        _buffer == new char[size];
        _isBufferToDelete = true;
    }
    else
    {
       if(_isBufferToDelete) 
       {
           delete[] _buffer;
           _isBufferToDelete = false;
       }

       _buffer = pointer;
    }

    _size = size;
}


SerialStream::SerialStream(size_t bufferSize, size_t readSize)
    : Stream(bufferSize)
    , _readBuffer(readSize)
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

    if(size > _readBuffer.Count())
    {
        _endOfFile = true;
        _bufferLock = false;
        return false;
    }

    for(auto i = 0; i < size; i++)
        out[i] = _readBuffer.Get();

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

    while((result < max) && (_readBuffer.IsEmpty() == false))
        out[result++] = _readBuffer.Get();

    _bufferLock = false;
    return result;
}

bool SerialStream::_ReceivedDataCallback(const unsigned char *data, size_t size)
{
    if(_bufferLock == true)
        return false;

    _readBuffer.Put(data, size);
    return true;
}