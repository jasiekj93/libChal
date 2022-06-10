#include "Hal.hpp"
#include "CircularBuffer.hpp"

static Chal::IHal *pointer = nullptr;

void Chal::SetHal(IHal *hal)
{
    pointer = hal;

    if(hal == nullptr)
    {
        
    }
}

Chal::IHal * Chal::GetHal()
{
    return pointer;
}
