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

    //Formatted
    int vfprintf(FILE *pointer, const char *format, va_list args);
    int fprintf(FILE *pointer, const char *format, ...);
    int vprintf(const char *format, va_list args);
    int printf(const char *format, ...);
    int vfscanf(FILE *pointer, const char *format, va_list args);
    int fscanf(FILE *pointer, const char *format, ...);
    int vscanf(const char *format, va_list args);
    int scanf(const char *format, ...);
    int snprintf( char * s, size_t n, const char * format, ...);
    int sprintf( char * str, const char * format, ...);
    int sscanf( const char * s, const char * format, ...);
    int vsnprintf(char * s, size_t n, const char * format, va_list arg);
    int vsprintf(char * s, const char * format, va_list arg);
    int vsscanf( const char * s, const char * format, va_list arg);

    //Character
    int fputc(int, FILE *);
    int putc(int, FILE *);
    int putchar(int);
    int fputs(const char *, FILE *);
    int puts(const char *);
    int fgetc(FILE *);
    int getc();
    int ungetc(int, FILE *);
    char *fgets(char *, int, FILE *);
    char *gets(char *);
}