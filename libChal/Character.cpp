/**
 * @file Character.cpp
 * @author Adrian Szczepanski
 * @date 10-06-2022
 * @brief 
 * @details
 */

#include "Stdio.hpp"
#include "Hal.hpp"
#include <string.h>

static const char newLine[] = "\r\n";
static const size_t newLineLength = 2;

int Chal::fputc(int character, FILE *pointer)
{
    if(pointer == nullptr)
        return EOF;

    auto stream = (Chal::Stream *)pointer;
    auto result = stream->Write((const unsigned char *)&character, 1);

    return (result ? character : EOF);
}

int Chal::putc(int character, FILE *pointer)
{
    return fputc(character, pointer);
}

int Chal::putchar(int character)
{
    auto hal = Chal::GetHal();

    if(hal == nullptr)
        return EOF;

    auto stream = hal->GetStout();
    return Chal::putc(character, stream);
}

int Chal::fputs(const char * str, FILE *stream)
{
    if(stream == nullptr)
        return EOF;

    auto length = strlen(str);
    auto result = stream->Write((const unsigned char *)str, length);
    
    return (result ? length : EOF);
}

int Chal::puts(const char * str)
{
    auto hal = Chal::GetHal();

    if(hal == nullptr)
        return EOF;

    auto stream = hal->GetStout();
    auto count = fputs(str,stream);

    if(count == EOF)
        return EOF;

    auto result = stream->Write((const unsigned char *)newLine, newLineLength);
    return (result ? (count + newLineLength) : EOF);
}