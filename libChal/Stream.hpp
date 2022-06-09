#pragma once

#include <libChal/CircularBuffer.hpp>

namespace Chal
{
    class Stream
    {
    public:
        Stream();

        virtual bool Open() = 0;
        virtual bool Close() = 0;

        virtual bool Write(const unsigned char *, size_t) = 0;
        virtual bool Read(unsigned char *out, size_t) = 0;
        // bool ReadString(unsigned char *out, size_t max);

        inline auto EndOfFile() const { return _endOfFile; }
        inline auto Error() const { return _error; }
        void ClearErrors();

    protected:
        bool _endOfFile;
        bool _error;
    };

    class SerialStream : public Stream
    {
    public:
        SerialStream(size_t);

        bool Read(unsigned char *out, size_t) override;
        // bool ReadString(unsigned char *out, size_t max);

        inline auto Count() const { return _buffer.Count(); }

    protected:
        CircularBuffer<unsigned char> _buffer;
        bool _bufferLock;
    };
}