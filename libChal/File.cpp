/**
 * @file File.cpp
 * @author Adrian Szczepanski
 * @date 09-06-2022
 * @brief 
 * @details
 */
#include "Stdio.hpp"
#include "Errno.hpp"
#include "Hal.hpp"

Chal::FILE * Chal::fopen(const char *filename, const char *mode)
{
    Chal::FILE *stream = nullptr;
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

    return stream;
}

int Chal::fclose(FILE * stream)
{
    if(stream == nullptr)
        return EOF;

    if(stream->Close() == true)
        return 0;
    else
        return EOF;
}

int Chal::fflush(FILE * pointer)
{
    if(pointer == nullptr)
        return EOF;

    pointer->Flush();
    return 0;
}

Chal::FILE * Chal::freopen(const char *filename, const char *mode, FILE *stream)
{
    if(stream != nullptr)
        fclose(stream);
    
    return fopen(filename, mode);
}

void Chal::setbuf(FILE *pointer, char *buffer)
{
    setvbuf(pointer, buffer, 0, BUFSIZ);
}

int Chal::setvbuf(FILE *pointer, char *buffer, int mode, size_t size)
{
    if(pointer == nullptr)
        return -1;

    pointer->SetBuffer(buffer, size);
    return 0;
}

size_t Chal::fread(void *out, size_t size, size_t count, FILE *pointer)
{
    if(pointer == nullptr || out == nullptr)
        return 0;

    auto result = pointer->Read((unsigned char *)out, size * count);

    return (result ? count : 0);
}

size_t Chal::fwrite(const void *data, size_t size, size_t count, FILE *pointer)
{
    if(pointer == nullptr || data == nullptr)
        return 0;

    auto result = pointer->Write((const unsigned char *)data, size * count);

    return (result ? count : 0);
}