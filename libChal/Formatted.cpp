/**
 * @file Formatted.cpp
 * @author Adrian Szczepanski
 * @date 09-06-2022
 * @brief 
 * @details
 */
#include <stdio.h>
#include <stdarg.h>
#include "Hal.hpp"

static char buffer[1024];
static size_t bufferSize = 1024;

int vfprintf(FILE *pointer, const char *format, va_list args)
{
    if(pointer == nullptr)
        return -1;

    auto stream = (Chal::Stream *)pointer;

    auto size = vsnprintf(buffer, bufferSize, format, args);

    if(size > bufferSize || size < 0)
        return -1;
    
    auto result = stream->Write((const unsigned char *)buffer, size + 1);

    return (result ? size : -1);
}

int fprintf(FILE *pointer, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    auto result = vfprintf(pointer, format, args);
    va_end(args);

    return result;
}

int vprintf(const char *format, va_list args)
{
    auto hal = Chal::GetHal();
    if(hal == nullptr)
        return -1;

    auto stream = hal->GetStout();
    if(stream == nullptr)
        return -1;

    auto result = vfprintf((FILE *)stream, format, args);

    return result;
}

int printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    auto result = vprintf(format, args);
    va_end(args);

    return result;
}

int vfscanf(FILE *pointer, const char *format, va_list args)
{
    if(pointer == nullptr)
        return EOF;

    auto stream = (Chal::Stream *)pointer;
    auto size = stream->ReadUpTo((unsigned char *)buffer, bufferSize -1);
    buffer[size] = '\0';

    auto result = vsscanf(buffer, format, args);
    return result;
}

int fscanf(FILE *pointer, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    auto result = vfscanf(pointer, format, args);
    va_end(args);

    return result;
}

int vscanf(const char *format, va_list args)
{
    auto hal = Chal::GetHal();
    if(hal == nullptr)
        return -1;

    auto stream = hal->GetStdin();
    if(stream == nullptr)
        return -1;

    auto result = vfscanf((FILE *)stream, format, args);

    return result;
}

int scanf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    auto result = vscanf(format, args);
    va_end(args);

    return result;
}