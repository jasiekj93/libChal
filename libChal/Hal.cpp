#include "Hal.hpp"
#include "CircularBuffer.hpp"

static Chal::CircularBuffer<unsigned char, Chal::ReceiveBufferSize> buffer;
static Chal::IHal *pointer = nullptr;

void Chal::SetHal(IHal *hal)
{
    pointer = hal;
}

Chal::IHal * Chal::GetHal()
{
    return pointer;
}

void Chal::ReceiveCallback(const unsigned char *in, size_t size)
{
    auto i = 0;

    while((i < size) && (buffer.IsFull() == false))
        buffer.Put(in[i++]);
}

size_t Chal::ReadReceivedData(unsigned char *out, size_t max)
{
    GetHal()->DisableInterrupts();

    size_t result = 0;

    while((result < max) && (buffer.IsEmpty() == false))
        out[result++] = buffer.Get();

    GetHal()->EnableInterrupts();
    return result;
}

size_t Chal::ReadString(unsigned char *out, size_t max)
{
    GetHal()->DisableInterrupts();

    size_t end = 0;
    auto count = buffer.Count();

    while((end < count) &&
        (end < max) &&
        (buffer[end] != '\0'))
        end++;

    if(end == count)
        return 0;

    if(end == max)
        return 0;

   return ReadReceivedData(out, end + 1);
}