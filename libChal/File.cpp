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
    Chal::Stream *stream = nullptr;
    auto result = false;
    auto hal = Chal::GetHal();

    if(hal != nullptr)
    {
        stream = hal->GetStream(filename);

        if(stream != nullptr)
            result = stream->Open();
    }

    if(result == false)
        errno = ENOENT;

    return (FILE *)stream;
}

int fclose(FILE * stream)
{
    if(stream == nullptr)
        return EOF;

    auto pointer = (Chal::Stream *)stream;

    if(pointer->Close() == true)
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

void setbuf(FILE *pointer, char *buffer)
{
    setvbuf(pointer, buffer, 0, BUFSIZ);
}

int setvbuf(FILE *pointer, char *buffer, int mode, size_t size)
{
    if(pointer == nullptr)
        return -1;

    auto stream = (Chal::Stream *)pointer;
    stream->SetBuffer(buffer, size);
    return 0;
}

size_t fread(void *out, size_t size, size_t count, FILE *pointer)
{
    if(pointer == nullptr || out == nullptr)
        return 0;

    auto stream = (Chal::Stream *)pointer;
    auto result = stream->Read((unsigned char *)out, size * count);

    return (result ? count : 0);
}

size_t fwrite(const void *data, size_t size, size_t count, FILE *pointer)
{
    if(pointer == nullptr || data == nullptr)
        return 0;

    auto stream = (Chal::Stream *)pointer;
    auto result = stream->Write((const unsigned char *)data, size * count);

    return (result ? count : 0);
}