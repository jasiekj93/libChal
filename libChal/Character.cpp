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
    auto result = stream->Write((const unsigned char *)&character, sizeof(unsigned char));

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

    if(stream == nullptr)
        return EOF;

    auto count = fputs(str,stream);

    if(count == EOF)
        return EOF;

    auto result = stream->Write((const unsigned char *)newLine, newLineLength);
    return (result ? (count + newLineLength) : EOF);
}

int Chal::fgetc(FILE *stream)
{
    if(stream == nullptr)
        return EOF;

    char result; 
    auto status = stream->Read((unsigned char *)&result, sizeof(char));

    return (status ? result : EOF);
}

int Chal::getc()
{
    auto hal = Chal::GetHal();

    if(hal == nullptr) 
        return EOF;
    
    auto stream = hal->GetStdin();

    if(stream == nullptr)
        return EOF;
    else
        return fgetc(stream);
}

int Chal::ungetc(int, FILE *)
{
    return EOF;
}

char * Chal::fgets(char *out, int max, FILE *stream)
{
    if(stream == nullptr)
        return nullptr;

    auto count = stream->ReadLine((unsigned char*)out, max - 1);

    if(stream->Error() || count == 0)
        return nullptr;
    
    out[count] = '\0';

    return out;
}

char * Chal::gets(char *out)
{
    auto hal = Chal::GetHal();

    if(hal == nullptr) 
        return nullptr;
    
    auto stream = hal->GetStdin();

    if(stream == nullptr)
        return nullptr;
    
    auto count = stream->ReadLine((unsigned char*)out, stream->Size() - 1);

    if(stream->Error() || count == 0)
        return nullptr;

    if(out[count - 1] == '\n')
        out[count - 1] = '\0';
    else
        out[count] == '\0';

    return out;
}