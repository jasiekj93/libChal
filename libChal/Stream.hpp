#pragma once

#include <libChal/CircularBuffer.hpp>

namespace Chal
{
    class Stream
    {
    public:
        Stream(size_t);
        ~Stream();

        virtual bool Open() = 0;
        virtual bool Close() = 0;
        virtual void Flush() {}

        bool Write(const unsigned char *, size_t);
        bool Read(unsigned char *, size_t);
        size_t ReadUpTo(unsigned char *, size_t max);

        inline auto EndOfFile() const { return _endOfFile; }
        inline auto Error() const { return _error; }
        void ClearErrors();

        inline char * Buffer() { return _buffer; }
        size_t Size() const { return _size; }
        void SetBuffer(char *, size_t);

    protected:
        virtual bool _Write(const unsigned char *, size_t) = 0;
        virtual bool _Read(unsigned char *, size_t) = 0;
        virtual size_t _ReadUpTo(unsigned char *, size_t max) = 0;

        size_t _writeAddress;
        size_t _readAddress;
        bool _endOfFile;
        bool _error;
        char *_buffer;
        size_t _size;
        bool _isBufferToDelete;
    };

    class SerialStream : public Stream
    {
    public:
        SerialStream(size_t, size_t);

        // bool ReadString(unsigned char *out, size_t max);

        inline const auto & ReadBuffer() const { return _readBuffer; };
        inline void Flush() override { _readBuffer.Clear(); }

    protected:
        bool _Read(unsigned char *out, size_t) override;
        size_t _ReadUpTo(unsigned char *out, size_t max) override;

        bool _ReceivedDataCallback(const unsigned char *data, size_t size);

    private:
        CircularBuffer<unsigned char> _readBuffer;
        bool _bufferLock;
    };
}