/**
 * @file Error.cpp
 * @author Adrian Szczepanski
 * @date 09-06-2022
 * @brief 
 * @details
 */

#include <stdio.h>
#include "Hal.hpp"

int ferror(FILE *stream)
{
    if(stream == nullptr)
        return 0;
    
    auto result = ((Chal::Stream *)stream)->Error();

    return (result ? 1 : 0);
}

int feof (FILE * stream)
{
    if(stream == nullptr)
        return 0;
    
    auto result = ((Chal::Stream *)stream)->EndOfFile();

    return (result ? 1 : 0);
}

void clearerr (FILE * stream)
{
    if(stream == nullptr)
        return;

    ((Chal::Stream *)stream)->ClearErrors();
}