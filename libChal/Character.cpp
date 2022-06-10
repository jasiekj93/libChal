
#include "Stdio.hpp"
#include "Hal.hpp"

int Chal::putc(int character, FILE *pointer)
{
    if(pointer == nullptr)
        return EOF;

    auto stream = (Chal::Stream *)pointer;
    auto result = stream->Write((const unsigned char *)&character, 1);

    return (result ? character : EOF);
}

int Chal::putchar(int character)
{
    auto hal = Chal::GetHal();

    if(hal == nullptr)
        return EOF;

    auto stream = hal->GetStout();
    return Chal::putc(character, stream);
}