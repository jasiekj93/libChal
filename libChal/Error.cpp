/**
 * @file Error.cpp
 * @author Adrian Szczepanski
 * @date 09-06-2022
 * @brief 
 * @details
 */

#include "Stdio.hpp"
#include "Hal.hpp"
#include <string.h>

int Chal::ferror(FILE *stream)
{
    if(stream == nullptr)
        return 0;
    
    auto result = stream->Error();

    return (result ? 1 : 0);
}

int Chal::feof(FILE * stream)
{
    if(stream == nullptr)
        return 0;
    
    auto result = stream->EndOfFile();

    return (result ? 1 : 0);
}

void Chal::clearerr(FILE * stream)
{
    if(stream == nullptr)
        return;

    stream->ClearErrors();
}

void Chal::perror(const char *message)
{
    auto hal = Chal::GetHal();

    if(hal == nullptr)
        return;

    auto stream = hal->GetStderr();

    if(stream == nullptr)
        return;

    stream->Write((const unsigned char *)message, strlen(message));
}