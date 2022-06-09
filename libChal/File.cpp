/**
 * @file File.cpp
 * @author Adrian Szczepanski
 * @date 09-06-2022
 * @brief 
 * @details
 */
#include <stdio.h>
#include <errno.h>
#include "Hal.hpp"

FILE * fopen(const char *filename, const char *mode)
{
    Chal::IStream *stream = nullptr;
    auto result = false;
    auto hal = Chal::GetHal();

    if(hal != nullptr)
    {
        stream = hal->GetStream(filename);

        if(stream != nullptr)
            result = stream->Init();
    }

    if(result == false)
        errno = ENOENT;

    return (FILE *)stream;
}

int fclose(FILE * stream)
{
    if(stream == nullptr)
        return EOF;

    auto pointer = (Chal::IStream *)stream;

    if(pointer->DeInit() == true)
        return 0;
    else
        return EOF;
}

int fflush(FILE * stream)
{
    return 0;
}

FILE * freopen(const char *filename, const char *mode, FILE *stream)
{
    if(stream != nullptr)
        fclose(stream);
    
    return fopen(filename, mode);
}

void setbuf(FILE *stream, char *buffer)
{
}

int setvbuf(FILE *stream, char *buffer, int mode, size_t size)
{
    return 1;
}

size_t fread(void *out, size_t size, size_t count, FILE *pointer)
{
    if(pointer == nullptr || out == nullptr)
        return 0;

    auto stream = (Chal::IStream *)pointer;
    auto result = stream->Read((unsigned char *)out, size * count);

    return (result ? count : 0);
}

size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream)
{
    return 0;
}