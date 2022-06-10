#pragma once

/**
 * @file Stdio.hpp
 * @author Adrian Szczepanski
 * @date 10-06-2022
 * @brief 
 * @details
 */

#include <libChal/Stream.hpp>
#include <stdio.h>
#include <stdarg.h>

namespace Chal
{
    using FILE = Stream;

    //Error
    int ferror(FILE *);
    int feof (FILE *);
    void clearerr (FILE *);
    void perror(const char *);

    //File
    FILE * fopen(const char *, const char *);
    int fclose(FILE * );
    int fflush(FILE * );
    FILE * freopen(const char *, const char *, FILE *);
    void setbuf(FILE *, char *);
    int setvbuf(FILE *, char *, int, size_t );
    size_t fread(void *, size_t, size_t, FILE *);
    size_t fwrite(const void *, size_t, size_t, FILE *);
    int snprintf ( char * s, size_t n, const char * format, ...);
    int sprintf ( char * str, const char * format, ...);
    int sscanf ( const char * s, const char * format, ...);
    int vsnprintf (char * s, size_t n, const char * format, va_list arg);
    int vsprintf (char * s, const char * format, va_list arg);
    int vsscanf ( const char * s, const char * format, va_list arg);
}