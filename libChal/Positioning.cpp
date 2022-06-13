/**
 * @file Positioning.cpp
 * @author Adrian Szczepanski
 * @date 13-06-2022
 * @brief 
 * @details
 */

#include "Stdio.hpp"
#include <errno.h>

int Chal::fgetpos(FILE *stream, fpos_t *out)
{
    if(stream == nullptr || out == nullptr)
    {
        errno = EBADF;
        return -1;
    }

    *out = stream->Offset;
    return 0;
}

int Chal::fseek(FILE *stream, long int offset, int origin)
{
    if(stream == nullptr)
        return -1;

    if(origin == SEEK_SET)
    {
        stream->Offset = offset;
        return 0;
    }
    else if(origin == SEEK_CUR)
    {
        stream->Offset += offset;
        return 0;
    }
    else
        return -1;
}

int Chal::fsetpos(FILE *stream, const fpos_t *in)
{
    if(stream == nullptr || in == nullptr)
    {
        errno = EBADF;
        return -1;
    }

    stream->Offset = *in;
    return 0;
}

long int Chal::ftell(FILE *stream)
{
    if(stream == nullptr)
    {
        errno = EBADF;
        return -1;
    }
    else
        return stream->Offset;
}

void Chal::rewind(FILE *stream)
{
    if(stream == nullptr)
        return;

    stream->Offset = 0;
    stream->ClearErrors();
}