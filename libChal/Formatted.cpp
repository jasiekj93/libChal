/**
 * @file Formatted.cpp
 * @author Adrian Szczepanski
 * @date 09-06-2022
 * @brief 
 * @details
 */
#include "Stdio.hpp" 
#include <stdarg.h>
#include "Hal.hpp"

int Chal::vfprintf(FILE *pointer, const char *format, va_list args)
{
    if(pointer == nullptr)
        return -1;

    auto stream = (Chal::Stream *)pointer;

    auto size = ::vsnprintf(stream->Buffer(), stream->Size(), format, args);

    if(size > stream->Size() || size < 0)
        return -1;
    
    auto result = stream->Write((const unsigned char *)stream->Buffer(), size + 1);

    return (result ? size : -1);
}

int Chal::fprintf(FILE *pointer, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    auto result = vfprintf(pointer, format, args);
    va_end(args);

    return result;
}

int Chal::vprintf(const char *format, va_list args)
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

int Chal::printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    auto result = vprintf(format, args);
    va_end(args);

    return result;
}

int Chal::vfscanf(FILE *pointer, const char *format, va_list args)
{
    if(pointer == nullptr)
        return EOF;

    auto stream = (Chal::Stream *)pointer;
    auto buffer = stream->Buffer();
    auto size = stream->ReadUpTo((unsigned char *)buffer, stream->Size() -1);
    buffer[size] = '\0';

    auto result = ::vsscanf(buffer, format, args);
    return result;
}

int Chal::fscanf(FILE *pointer, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    auto result = vfscanf(pointer, format, args);
    va_end(args);

    return result;
}

int Chal::vscanf(const char *format, va_list args)
{
    auto hal = Chal::GetHal();
    if(hal == nullptr)
        return -1;

    auto stream = hal->GetStdin();
    if(stream == nullptr)
        return -1;

    auto result = vfscanf(stream, format, args);

    return result;
}

int Chal::scanf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    auto result = vscanf(format, args);
    va_end(args);

    return result;
}

int Chal::snprintf( char * s, size_t n, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    auto result = ::vsnprintf(s, n, format, args);
    va_end(args);

    return result;
}

int Chal::sprintf( char * str, const char * format, ...)
{
    va_list args;
    va_start(args, format);

    auto result = ::vsprintf(str, format, args);
    va_end(args);

    return result;
}

int Chal::sscanf( const char *str, const char * format, ...)
{
    va_list args;
    va_start(args, format);

    auto result = ::vsscanf(str, format, args);
    va_end(args);

    return result;
}

int Chal::vsnprintf(char *s, size_t n, const char *format, va_list args)
{
     return ::vsnprintf(s, n, format, args);
}

int Chal::vsprintf(char *s, const char *format, va_list args)
{
    return ::vsprintf(s, format, args);
}

int Chal::vsscanf( const char *s, const char *format, va_list args)
{
    return ::vsscanf(s, format, args);
}