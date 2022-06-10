
#include <stdio.h>
#include <cstdio>
#include "Hal.hpp"

int putc(int character, FILE *pointer)
{
    if(pointer == nullptr)
        return EOF;

    auto stream = (Chal::Stream *)pointer;
    auto result = stream->Write((const unsigned char *)&character, 1);

    return (result ? character : EOF);
}

int putchar(int character)
{
    auto hal = Chal::GetHal();

    if(hal == nullptr)
        return EOF;

    auto stream = hal->GetStout();
    // return putc(character, (FILE *)stream);
    return putc(character, stdout);
}